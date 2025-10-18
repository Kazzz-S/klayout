#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
File: "macbuild/bundle_qtconf.py"

Author: ChatGPT + Kazzz-S

Utilities to generate and embed a proper qt.conf into a macOS .app bundle
for KLayout (or any Qt-based app), supporting two strategies:

- ST/HW (Qt embedded in the bundle): relative qt.conf (Prefix=.., Plugins=PlugIns)
- LW (use system-wide Qt): absolute qt.conf (Plugins=<absolute path>)

Policy:
- The bundle creator ("macbuild/build4mac.py") decides the target stack at build time.
- The distributed app contains exactly ONE qt.conf (no scripts post-distribution).

Command-line test usage:
    python bundle_qtconf.py --mode lw --stack macports --qt 5
    python bundle_qtconf.py --app ./dist/klayout.app --mode st --plugins /opt/local/libexec/qt5/plugins

Typical usage:
    from pathlib import Path
    from bundle_qtconf import generate_qtconf, QtConfError

    # 1) LW + MacPorts Qt5 (print-only; do not write into app)
    try:
        text = generate_qtconf(
            mode="lw",
            lw_stack="macports",
            lw_qt_major=5,
        )
        print(text)  # -> "[Paths]\nPlugins=/opt/local/libexec/qt5/plugins\n"
    except QtConfError as e:
        print(f"Failed: {e}")

    # 2) LW + Homebrew Qt6 on Apple Silicon (write into app)
    try:
        qtconf = generate_qtconf(
            app_path="dist/klayout.app",
            mode="lw",
            lw_stack="homebrew",
            lw_qt_major=6,
            arch_hint="arm64",   # "x86_64" for Intel; "auto" also works
        )
        print("qt.conf written to app; content:")
        print(qtconf)
    except QtConfError as e:
        print(f"Failed: {e}")

    # 3) LW + Anaconda (explicit environment; write into app)
    try:
        text = generate_qtconf(
            app_path=Path("dist/klayout.app"),
            mode="lw",
            lw_stack="anaconda",
            conda_prefix="/opt/anaconda3/envs/klayout",  # or rely on CONDA_PREFIX
        )
        print(text)
    except QtConfError as e:
        print(f"Failed: {e}")

    # 4) ST/HW (Qt embedded in the bundle; copy plugins + write relative qt.conf)
    try:
        text = generate_qtconf(
            app_path="dist/klayout.app",
            mode="st",  # or "hw"
            embedded_plugins_src="/opt/local/libexec/qt5/plugins",
            # You can narrow/extend what to copy inside copy_embedded_plugins() if needed.
            validate=True,  # ensures PlugIns/platforms/libqcocoa.dylib exists after copy
        )
        print(text)
    except QtConfError as e:
        print(f"Failed: {e}")
"""

from __future__ import annotations

import os
import shutil
import subprocess
import argparse
from pathlib import Path
from typing import Iterable, Optional, Tuple


class QtConfError(RuntimeError):
    """Raised when qt.conf generation or validation fails."""


# -----------------------------------------------------------------------------
# Utility helpers
# -----------------------------------------------------------------------------
def _app_paths(app_path: Path) -> Tuple[Path, Path, Path]:
    """Return (Resources, PlugIns, MacOS) directories for the .app bundle."""
    app_path = app_path.resolve()
    contents = app_path / "Contents"
    resources = contents / "Resources"
    plugins = contents / "PlugIns"
    macos = contents / "MacOS"
    return resources, plugins, macos


def _ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)


def choose_homebrew_root(arch_hint: str = "auto") -> Path:
    """Choose Homebrew prefix based on architecture hint."""
    if arch_hint == "arm64" or (arch_hint == "auto" and Path("/opt/homebrew").is_dir()):
        return Path("/opt/homebrew")
    return Path("/usr/local")


def find_plugins_dir_lw(
    lw_stack: str,
    lw_qt_major: Optional[int] = None,
    arch_hint: str = "auto",
    conda_prefix: Optional[Path] = None,
) -> Path:
    """Resolve the absolute Qt plugins directory for LW mode."""
    stack = lw_stack.lower().strip()

    if stack == "macports":
        if lw_qt_major not in (5, 6):
            raise QtConfError("MacPorts requires lw_qt_major to be 5 or 6.")
        return Path(f"/opt/local/libexec/qt{lw_qt_major}/plugins")

    if stack == "homebrew":
        if lw_qt_major not in (5, 6):
            raise QtConfError("Homebrew requires lw_qt_major to be 5 or 6.")
        hb = choose_homebrew_root(arch_hint)

        # 0) Try qtpaths from qt and qtbase (most reliable for Qt6)
        for formula in ("qt", "qtbase"):
            qtpaths_bin = hb / "opt" / formula / "bin" / "qtpaths"
            if qtpaths_bin.is_file() and os.access(qtpaths_bin, os.X_OK):
                try:
                    out = subprocess.check_output([str(qtpaths_bin), "--plugin-dir"], text=True).strip()
                    p = Path(out)
                    if (p / "platforms").is_dir():
                        return p
                except Exception:
                    pass  # fall through

        candidates: list[Path] = []

        if lw_qt_major == 6:
            # Qt6 on Homebrew: plugins are typically under share/qt/plugins (qtbase keg).
            candidates += [
                hb / "opt" / "qt" / "share" / "qt" / "plugins",
                hb / "opt" / "qtbase" / "share" / "qt" / "plugins",
                hb / "Cellar" / "qt" / "*" / "share" / "qt" / "plugins",
                hb / "Cellar" / "qtbase" / "*" / "share" / "qt" / "plugins",
                # Some setups also expose legacy locations/symlinks:
                hb / "opt" / "qt" / "lib" / "qt6" / "plugins",
                hb / "opt" / "qt" / "plugins",
            ]
        else:
            # Qt5 on Homebrew: classic keg layout
            candidates += [
                hb / "opt" / "qt@5" / "plugins",
                hb / "opt" / "qt@5" / "lib" / "qt5" / "plugins",
                hb / "Cellar" / "qt@5" / "*" / "plugins",
                hb / "Cellar" / "qt@5" / "*" / "lib" / "qt5" / "plugins",
            ]

        # Expand any globs (Cellar/*) and validate
        expanded: list[Path] = []
        for c in candidates:
            if "*" in str(c):
                expanded.extend(Path(p) for p in sorted(map(str, c.parent.glob(c.name))))
            else:
                expanded.append(c)

        for c in expanded:
            if (c / "platforms").is_dir():
                return c

        raise QtConfError(
            "Homebrew Qt{} plugins not found under {}. Checked: {}".format(
                lw_qt_major, hb, ", ".join(str(p) for p in expanded)
            )
        )

    if stack == "anaconda":
        prefix = Path(os.environ.get("CONDA_PREFIX", "")) if conda_prefix is None else Path(conda_prefix)
        if not prefix:
            raise QtConfError("Anaconda stack requires CONDA_PREFIX or conda_prefix argument.")
        for c in (prefix / "plugins", prefix / "lib" / "qt" / "plugins"):
            if (c / "platforms").is_dir():
                return c
        raise QtConfError(f"Anaconda plugins not found under {prefix}")

    raise QtConfError(f"Unknown lw_stack: {lw_stack}")


def _validate_libqcocoa(plugins_dir: Path) -> None:
    """Ensure libqcocoa.dylib exists under <plugins_dir>/platforms."""
    lib = plugins_dir / "platforms" / "libqcocoa.dylib"
    if not lib.is_file():
        raise QtConfError(f"libqcocoa.dylib not found: {lib}")


def copy_embedded_plugins(
    embedded_plugins_src: Path,
    bundle_plugins_dir: Path,
    subdirs: Iterable[str] = ("platforms",),
    overwrite: bool = True,
) -> None:
    """Copy selected plugin subdirectories into the bundle."""
    embedded_plugins_src = embedded_plugins_src.resolve()
    bundle_plugins_dir = bundle_plugins_dir.resolve()
    _ensure_dir(bundle_plugins_dir)

    for d in subdirs:
        src = embedded_plugins_src / d
        dst = bundle_plugins_dir / d
        if not src.is_dir():
            raise QtConfError(f"Missing plugin subdir at source: {src}")
        if dst.exists() and overwrite:
            shutil.rmtree(dst)
        shutil.copytree(src, dst)


# -----------------------------------------------------------------------------
# Core functions
# -----------------------------------------------------------------------------
def make_qtconf_text_relative() -> str:
    """Return relative qt.conf text for ST/HW bundles."""
    return (
        "[Paths]\n"
        "Prefix=..\n"
        "Plugins=PlugIns\n"
        "Imports=Resources/qml\n"
        "Qml2Imports=Resources/qml\n"
    )


def make_qtconf_text_absolute(plugins_dir: Path) -> str:
    """Return absolute qt.conf text for LW bundles."""
    return f"[Paths]\nPlugins={plugins_dir}\n"


def generate_qtconf(
    app_path: Optional[str | Path] = None,
    *,
    mode: str,
    embedded_plugins_src: Optional[str | Path] = None,
    lw_stack: Optional[str] = None,
    lw_qt_major: Optional[int] = None,
    arch_hint: str = "auto",
    conda_prefix: Optional[str | Path] = None,
    validate: bool = True,
) -> str:
    """
    Generate qt.conf content (optionally write to app if app_path is given).

    Returns the generated qt.conf text.
    """
    app_path = Path(app_path).resolve() if app_path else None
    qtconf_text: str

    if mode in ("st", "hw"):
        qtconf_text = make_qtconf_text_relative()

        if app_path:
            resources, plugins, _macos = _app_paths(app_path)
            _ensure_dir(resources)
            if embedded_plugins_src:
                copy_embedded_plugins(Path(embedded_plugins_src), plugins)
                if validate:
                    _validate_libqcocoa(plugins)
            (resources / "qt.conf").write_text(qtconf_text, encoding="utf-8")

    elif mode == "lw":
        if lw_stack is None:
            raise QtConfError("lw_stack is required for LW mode (macports|homebrew|anaconda).")

        plugins_dir = find_plugins_dir_lw(
            lw_stack=lw_stack,
            lw_qt_major=lw_qt_major,
            arch_hint=arch_hint,
            conda_prefix=Path(conda_prefix) if conda_prefix else None,
        )
        if validate:
            _validate_libqcocoa(plugins_dir)

        qtconf_text = make_qtconf_text_absolute(plugins_dir)
        if app_path:
            resources, _, _ = _app_paths(app_path)
            _ensure_dir(resources)
            (resources / "qt.conf").write_text(qtconf_text, encoding="utf-8")

    else:
        raise QtConfError(f"Unknown mode: {mode}")

    return qtconf_text


# -----------------------------------------------------------------------------
# CLI for testing
# -----------------------------------------------------------------------------
def main() -> None:
    """Simple CLI for standalone testing or dry-run output."""
    parser = argparse.ArgumentParser(description="Generate qt.conf or print its content.")
    parser.add_argument("--app", help="Path to the .app bundle (optional; if omitted, only print the content)")
    parser.add_argument("--mode", choices=["st", "hw", "lw"], required=True, help="Bundle mode")
    parser.add_argument("--stack", choices=["macports", "homebrew", "anaconda"], help="LW: Qt stack type")
    parser.add_argument("--qt", type=int, choices=[5, 6], help="LW: Qt major version (5 or 6)")
    parser.add_argument("--arch", default="auto", choices=["auto", "arm64", "x86_64"], help="LW: arch hint for Homebrew")
    parser.add_argument("--plugins", help="ST/HW: source path of Qt plugins")
    parser.add_argument("--no-validate", action="store_true", help="Skip validation of libqcocoa.dylib existence")
    parser.add_argument("--conda-prefix", help="LW(Anaconda) only: explicit CONDA_PREFIX to use")

    args = parser.parse_args()

    try:
        qtconf_text = generate_qtconf(
            app_path=args.app,
            mode=args.mode,
            embedded_plugins_src=args.plugins,
            lw_stack=args.stack,
            lw_qt_major=args.qt,
            arch_hint=args.arch,
            conda_prefix=args.conda_prefix,
            validate=not args.no_validate,
        )
        if args.app:
            print(f"[OK] qt.conf written to bundle: {args.app}")
        print("----- qt.conf content -----")
        print(qtconf_text.strip())
        print("---------------------------")
    except QtConfError as e:
        print(f"[ERROR] {e}")
        exit(1)


if __name__ == "__main__":
    main()
