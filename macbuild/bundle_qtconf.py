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

    # 1) LW + MacPorts Qt5 (print-only)
    try:
        text = generate_qtconf(
            mode="lw",
            lw_stack="macports",
            lw_qt_major=5,
        )
        print(text)
    except QtConfError as e:
        print(f"Failed: {e}")

    # 2) LW + Homebrew Qt6 (write into app)
    try:
        text = generate_qtconf(
            app_path="dist/klayout.app",
            mode="lw",
            lw_stack="homebrew",
            lw_qt_major=6,
            arch_hint="arm64",  # "x86_64" for Intel; "auto" works too
        )
        print(text)
    except QtConfError as e:
        print(f"Failed: {e}")

    # 3) LW + Anaconda (Automator-safe: pass explicit prefix if needed)
    try:
        text = generate_qtconf(
            app_path=Path("dist/klayout.app"),
            mode="lw",
            lw_stack="anaconda",
            # If Automator does not inherit CONDA_PREFIX, pass it explicitly:
            conda_prefix="/opt/anaconda3",  # or any detected path on your build host
        )
        print(text)
    except QtConfError as e:
        print(f"Failed: {e}")

    # 4) ST/HW (Qt embedded in the bundle)
    try:
        text = generate_qtconf(
            app_path="dist/klayout.app",
            mode="st",  # or "hw"
            embedded_plugins_src="/opt/local/libexec/qt5/plugins",
            validate=True,
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
from typing import Iterable, Optional, Tuple, List, Union


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


def _is_executable(p: Path) -> bool:
    try:
        return p.is_file() and os.access(str(p), os.X_OK)
    except Exception:
        return False


def _expand_candidates_with_glob(candidates: List[Path]) -> List[Path]:
    expanded: List[Path] = []
    for c in candidates:
        s = str(c)
        if "*" in s or "?" in s or "[" in s:
            try:
                expanded.extend(Path(x) for x in sorted(map(str, c.parent.glob(c.name))))
            except Exception:
                pass
        else:
            expanded.append(c)
    return expanded


def _first_existing_platforms_dir(candidates: List[Path]) -> Optional[Path]:
    for c in _expand_candidates_with_glob(candidates):
        if (c / "platforms").is_dir():
            return c
    return None


def _home_dir() -> Path:
    # Automator/launchd may set HOME; fallback to Path.home() if not.
    try:
        h = os.environ.get("HOME")
        if h:
            return Path(h)
    except Exception:
        pass
    return Path.home()


# -----------------------------------------------------------------------------
# LW plugin dir resolvers (MacPorts / Homebrew / Anaconda)
# -----------------------------------------------------------------------------
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
        p = Path("/opt/local/libexec/qt{}/plugins".format(lw_qt_major))
        return p

    if stack == "homebrew":
        if lw_qt_major not in (5, 6):
            raise QtConfError("Homebrew requires lw_qt_major to be 5 or 6.")
        hb = choose_homebrew_root(arch_hint)

        # 0) Try qtpaths from qt and qtbase (most reliable, esp. for Qt6 split formula)
        for formula in ("qt", "qtbase"):
            qtpaths_bin = hb / "opt" / formula / "bin" / "qtpaths"
            if _is_executable(qtpaths_bin):
                try:
                    out = subprocess.check_output([str(qtpaths_bin), "--plugin-dir"], text=True).strip()
                    p = Path(out)
                    if (p / "platforms").is_dir():
                        return p
                except Exception:
                    pass  # fall through if qtpaths not available or fails

        candidates: List[Path] = []
        if lw_qt_major == 6:
            # Qt6 on Homebrew: often under share/qt/plugins nowadays (qtbase keg)
            candidates += [
                hb / "opt" / "qt" / "share" / "qt" / "plugins",
                hb / "opt" / "qtbase" / "share" / "qt" / "plugins",
                hb / "Cellar" / "qt" / "*" / "share" / "qt" / "plugins",
                hb / "Cellar" / "qtbase" / "*" / "share" / "qt" / "plugins",
                # legacy/symlink fallbacks:
                hb / "opt" / "qt" / "lib" / "qt6" / "plugins",
                hb / "opt" / "qt" / "plugins",
            ]
        else:
            # Qt5 on Homebrew: classic keg
            candidates += [
                hb / "opt" / "qt@5" / "plugins",
                hb / "opt" / "qt@5" / "lib" / "qt5" / "plugins",
                hb / "Cellar" / "qt@5" / "*" / "plugins",
                hb / "Cellar" / "qt@5" / "*" / "lib" / "qt5" / "plugins",
            ]

        found = _first_existing_platforms_dir(candidates)
        if found:
            return found

        raise QtConfError(
            "Homebrew Qt{} plugins not found under {}. Checked: {}".format(
                lw_qt_major, hb, ", ".join(str(p) for p in _expand_candidates_with_glob(candidates))
            )
        )

    if stack == "anaconda":
        # Priority:
        # 1) If conda_prefix points to an ENV, use it directly.
        # 2) If conda_prefix points to BASE, prefer well-known env names per Qt major:
        #       Qt5 -> envs/klayout-qt5/plugins
        #       Qt6 -> envs/klayout-qt6/lib/qt6/plugins
        #    and then scan all envs under BASE for the expected layout.
        # 3) If neither is set, probe common BASE roots (/opt, /usr/local, $HOME, forge flavors)
        #    and repeat the same env-first then full scan strategy.
        #
        # This is Automator-safe (no CONDA_PREFIX needed) and conda-forge friendly.

        def _env_plugins_candidates(env_root, qt_major):
            # env_root: .../envs/<envname>
            if qt_major == 6:
                return [Path(env_root) / "lib" / "qt6" / "plugins"]
            else:
                return [Path(env_root) / "plugins"]

        def _base_preferred_envs(base_root, qt_major):
            # preferred env names used in your setup
            names = ["klayout-qt6"] if qt_major == 6 else ["klayout-qt5"]
            env_roots = [Path(base_root) / "envs" / n for n in names]
            cands = []
            for er in env_roots:
                cands.extend(_env_plugins_candidates(er, qt_major))
            return cands

        def _scan_all_envs(base_root, qt_major):
            cands = []
            envs_dir = Path(base_root) / "envs"
            if envs_dir.is_dir():
                for er in sorted(envs_dir.iterdir()):
                    if not er.is_dir():
                        continue
                    # Favor env names that mention qt major (e.g., *qt6*), but include all as fallback
                    if qt_major == 6 and "qt6" in er.name.lower():
                        cands.extend(_env_plugins_candidates(er, 6))
                    elif qt_major == 5 and "qt5" in er.name.lower():
                        cands.extend(_env_plugins_candidates(er, 5))
                # full fallback: every env regardless of name
                for er in sorted(envs_dir.iterdir()):
                    if er.is_dir():
                        cands.extend(_env_plugins_candidates(er, qt_major))
            return cands

        def _base_generic_candidates(base_root):
            # Rare layouts (not env-specific); keep as very last resort
            return [
                Path(base_root) / "plugins",
                Path(base_root) / "lib" / "qt" / "plugins",
                Path(base_root) / "lib" / "qt5" / "plugins",
                Path(base_root) / "lib" / "qt6" / "plugins",
            ]

        qt_major = lw_qt_major or 6  # default bias to Qt6 if not specified

        # Collect possible BASE roots in priority order
        roots = []
        # 1) explicit conda_prefix (could be ENV or BASE)
        if conda_prefix:
            roots.append(Path(conda_prefix))

        # 2) environment (may be absent under Automator)
        env_prefix = os.environ.get("CONDA_PREFIX", "")
        if env_prefix:
            roots.append(Path(env_prefix))

        # 3) common base installs (system & user; includes forge flavors)
        home = _home_dir()
        roots += [
            Path("/opt/anaconda3"),
            Path("/usr/local/anaconda3"),
            home / "opt" / "anaconda3",
            home / "anaconda3",
            Path("/opt/miniconda3"),
            Path("/usr/local/miniconda3"),
            home / "miniconda3",
            Path("/opt/mambaforge"),
            home / "mambaforge",
            Path("/opt/miniforge3"),
            home / "miniforge3",
        ]

        # Build plugin-directory candidates in descending priority
        plugin_candidates = []

        # Case A: conda_prefix points directly to an ENV (has 'conda-meta' and not 'envs')
        # → honor it strictly
        if conda_prefix:
            cp = Path(conda_prefix)
            if (cp / "conda-meta").is_dir() and not (cp / "envs").is_dir():
                plugin_candidates.extend(_env_plugins_candidates(cp, qt_major))

        # Case B: roots treated as BASE → prefer known env names, then scan all envs
        for base in roots:
            b = Path(base)
            try:
                b = b.resolve()
            except Exception:
                pass
            # Prefer well-known env names (klayout-qt5 / klayout-qt6)
            plugin_candidates.extend(_base_preferred_envs(b, qt_major))
            # Then scan every env under this base
            plugin_candidates.extend(_scan_all_envs(b, qt_major))
            # Finally, generic non-env locations under base
            plugin_candidates.extend(_base_generic_candidates(b))

        found = _first_existing_platforms_dir(plugin_candidates)
        if found:
            return found

        raise QtConfError(
            "Anaconda plugins not found. Checked: {}".format(
                ", ".join(str(p) for p in _expand_candidates_with_glob(plugin_candidates))
            )
        )

    raise QtConfError("Unknown lw_stack: {}".format(lw_stack))


def _validate_libqcocoa(plugins_dir: Path) -> None:
    """Ensure libqcocoa.dylib exists under <plugins_dir>/platforms."""
    lib = plugins_dir / "platforms" / "libqcocoa.dylib"
    if not lib.is_file():
        raise QtConfError("libqcocoa.dylib not found: {}".format(lib))


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
            raise QtConfError("Missing plugin subdir at source: {}".format(src))
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
    return "[Paths]\nPlugins={}\n".format(plugins_dir)


def generate_qtconf(
    app_path: Optional[Union[str, Path]] = None,
    *,
    mode: str,
    embedded_plugins_src: Optional[Union[str, Path]] = None,
    lw_stack: Optional[str] = None,
    lw_qt_major: Optional[int] = None,
    arch_hint: str = "auto",
    conda_prefix: Optional[Union[str, Path]] = None,
    validate: bool = True,
) -> str:
    """
    Generate qt.conf content (optionally write to app if app_path is given).

    Returns the generated qt.conf text.
    """
    app_path_p: Optional[Path] = Path(app_path).resolve() if app_path else None
    qtconf_text: str

    if mode in ("st", "hw"):
        qtconf_text = make_qtconf_text_relative()

        if app_path_p:
            resources, plugins, _macos = _app_paths(app_path_p)
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
        if app_path_p:
            resources, _, _ = _app_paths(app_path_p)
            _ensure_dir(resources)
            (resources / "qt.conf").write_text(qtconf_text, encoding="utf-8")

    else:
        raise QtConfError("Unknown mode: {}".format(mode))

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
            validate=not args.no-validate if hasattr(args, "no-validate") else True,  # defensive
        )
        if args.app:
            print("[OK] qt.conf written to bundle: {}".format(args.app))
        print("----- qt.conf content -----")
        print(qtconf_text.strip())
        print("---------------------------")
    except QtConfError as e:
        print("[ERROR] {}".format(e))
        raise SystemExit(1)


if __name__ == "__main__":
    main()
