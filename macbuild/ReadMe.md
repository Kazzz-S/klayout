Relevant KLayout version: 0.30.2<br>
Author: Kazzz-S<br>
Last modified: 2025-05-30<br>

# 1. Introduction
This directory **`macbuild`** contains various files required for building KLayout (http://www.klayout.de/) version 0.30.2 or later for different 64-bit macOS, including:
* Sequoia     (15.x)    : the primary development environment
* Sonoma      (14.x)    : experimental
* Ventura     (13.x)    : -- ditto --

Building KLayout for the previous operating systems listed below has been discontinued.<br>
Pre-built DMG packages are also not provided.<br>
* Monterey    (12.7.6; the build is still possible, but Homebrew stopped supporting this OS in September 2024)
* Big Sur     (11.7.10)
* Catalina    (10.15.7)
* Mojave      (10.14)
* High Sierra (10.13)
* Sierra      (10.12)
* El Capitan  (10.11)

Throughout this document, the primary target machine is **Intel x86_64** with **macOS Sequoia**.<br>
All Apple (M1|M2|M3|M4) chips are still untested, as the author does not own an (M1|M2|M3|M4) Mac.<br>
However, some kind volunteers told me they successfully built on an Apple silicon machine.<br>

# 2. Qt Frameworks

The default Qt framework is "Qt5" from **MacPorts** (https://www.macports.org/), which is usually located under:
```
/opt/local/libexec/qt5/
```

If you prefer "Qt6" from **Homebrew** (https://brew.sh/), which is usually located under:
```
/usr/local/opt/qt@6/
```

You can also choose "Qt5" from Anaconda3 (https://www.anaconda.com/), which is usually located under:
```
$HOME/opt/anaconda3/pkgs/qt-{version}
```
If you have installed Anaconda3 under $HOME/opt/anaconda3/, make a symbolic link:
```
/Applications/anaconda3/ ---> $HOME/opt/anaconda3/
```

The migration work to "Qt6" is ongoing. You can try to use it; however, you might encounter some build or runtime errors.<br>
If you use **Homebrew** to build KLayout >= 0.29.0, you need "Qt6" to address [the compilation issue](https://github.com/KLayout/klayout/issues/1599).<br>
I have also tried migrating to "Python 3.12.x" (earlier, Python 3.11.x) in this version.

# 3. Script language support: Ruby and Python

The build script **`build4mac.py`** provides several possible combinations of Qt, Ruby, and Python modules to suit the user's needs and preferences.<br>
Some typical use cases are described in Section 6.

# 4. Prerequisites
You need to have the followings:
* The latest Xcode and command-line tool kit compliant with each OS
  * https://developer.apple.com/xcode/resources/
  * https://mac.install.guide/commandlinetools/4
* Qt5 package from MacPorts or Anaconda3. Qt6, from Homebrew.
* libgit2 form MacPorts, Homebrew,or Anaconda3.
* Optionally, Ruby and Python packages from MacPorts, Homebrew, or Anaconda3
#### For matching versions of Ruby and Python, please also refer to `build4mac_env.py`.

# 5. Command-line options of **`build4mac.py`**

**`build4mac.py`** is the top level Python script for building KLayout for a macOS.
The operating system type is detected automatically.

```
-----------------------------------------------------------------------------------------------------------
<< Usage of 'build4mac.py' >>
       for building KLayout 0.30.2 or later on different Apple macOS platforms.

$ [python] ./build4mac.py
   option & argument    : descriptions (refer to 'macbuild/build4mac_env.py' for details)  | default value
   ----------------------------------------------------------------------------------------+---------------
   [-q|--qt <type>]     : case-insensitive type=['Qt5MacPorts', 'Qt5Brew', 'Qt5Ana3',      | qt5macports
                        :                        'Qt6MacPorts', 'Qt6Brew']                 |
                        :   Qt5MacPorts: use Qt5 from MacPorts                             |
                        :       Qt5Brew: use Qt5 from Homebrew                             |
                        :       Qt5Ana3: use Qt5 from Anaconda3                            |
                        :   Qt6MacPorts: use Qt6 from MacPorts (*)                         |
                        :       Qt6Brew: use Qt6 from Homebrew (*)                         |
                        :                        (*) migration to Qt6 is ongoing           |
   [-r|--ruby <type>]   : case-insensitive type=['nil', 'Sys', 'MP33', 'HB34', 'Ana3']     | sys
                        :    nil: don't bind Ruby                                          |
                        :    Sys: use [Sequoia|Sonoma|Ventura|Monterey]-bundled Ruby 2.6   |
                        :   MP33: use Ruby 3.3 from MacPorts                               |
                        :   HB34: use Ruby 3.4 from Homebrew                               |
                        :   Ana3: use Ruby 3.2 from Anaconda3                              |
   [-p|--python <type>] : case-insensitive type=['nil', 'Sys', 'MP312', 'HB312', 'Ana3',   | sys
                        :                        'MP311', 'HB311', 'HBAuto']               |
                        :    nil: don't bind Python                                        |
                        :    Sys: use [Sequoia|Sonoma|Ventura|Monterey]-bundled Python 3.9 |
                        :  MP312: use Python 3.12 from MacPorts                            |
                        :  HB312: use Python 3.12 from Homebrew                            |
                        :   Ana3: use Python 3.12 from Anaconda3                           |
                        :  MP311: use Python 3.11 from MacPorts                            |
                        :  HB311: use Python 3.11 from Homebrew (+)                        |
                        :               (+) required to provide the legacy pip in HW-*.dmg |
                        : HBAuto: use the latest Python 3.x auto-detected from Homebrew    |
   [-P|--buildPymod]    : build and deploy Pymod (*.whl) for LW-*.dmg                      | disabled
   [-n|--noqtbinding]   : don't create Qt bindings for ruby scripts                        | disabled
   [-u|--noqtuitools]   : don't include uitools in Qt binding                              | disabled
   [-g|--nolibgit2]     : don't include libgit2 for Git package support                    | disabled
   [-m|--make <option>] : option passed to 'make'                                          | '--jobs=4'
   [-d|--debug]         : enable debug mode build; AddressSanitizer (ASAN) is linked       | disabled
   [-c|--checkcom]      : check command-line and exit without building                     | disabled
   [-y|--deploy]        : deploy executables and dylibs, including Qt's Frameworks         | disabled
   [-Y|--DEPLOY]        : deploy executables and dylibs for those who built KLayout        | disabled
                        : from the source code and use the tools in the same machine       |
                        : ! After confirmation of the successful build of 'klayout.app',   |
                        :   rerun this script with BOTH:                                   |
                        :     1) the same options used for building AND                    |
                        :     2) <-y|--deploy> OR <-Y|--DEPLOY>                            |
                        :   optionally with [-v|--verbose <0-3>]                           |
   [-v|--verbose <0-3>] : verbose level of `macdeployqt' (effective with -y only)          | 1
                        : 0 = no output, 1 = error/warning (default),                      |
                        : 2 = normal,    3 = debug                                         |
   [-?|--?]             : print this usage and exit; in zsh, quote like '-?' or '--?'      | disabled
-------------------------------------------------------------------------------------------+---------------
```

# 6. Use-cases
In this section, the actual file and directory names are those obtained on macOS Sequoia.<br>
On different OS, those names differ accordingly.

### 6A. Standard build using the OS-bundled Ruby and Python with MacPorts Qt5
0. Install MacPorts, then install Qt5 and libgit2 by
```
$ sudo port install coreutils
$ sudo port install findutils
$ sudo port install qt5
$ sudo port install libgit2
```

Confirm that you have:
```
/Library/Developer/CommandLineTools/Library/Frameworks/Python3.framework/*
```
  As of this writing, the provided Python version is `3.9.6`.

1. Invoke **`build4mac.py`** with the following options: **((Notes))** These options are the default values for Sequoia, Sonoma, and Ventura.
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt5macports -r sys -p sys
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-y" to deploy executables and libraries under **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.<br>

```
$ ./build4mac.py -q qt5macports -r sys -p sys -y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`ST-qt5MP.pkg.macos-Sequoia-release-RsysPsys`** directory, where
* "ST-"        means this is a standard package.
* "qt5MP"      means that Qt5 from MacPorts is used.
* "RsysPsys"   means that Ruby is 2.6 provided by OS; Python is 3.9 provided by OS.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.

### 6B. Fully MacPorts-flavored build with MacPorts Ruby 3.3 and MacPorts Python 3.12
0. Install MacPorts, then install Qt5, Ruby 3.3, Python 3.12, and libgit2 by
```
$ sudo port install coreutils
$ sudo port install findutils
$ sudo port install qt5
$ sudo port install ruby33
$ sudo port install python312
$ sudo port install py312-pip
$ sudo port install libgit2
```
1. Invoke **`build4mac.py`** with the following options:
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt5macports -r mp33 -p mp312
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-Y" to deploy executables and libraries under **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.<br>
   If you use `--buildPymod` option in Step-1 and Step-3, the KLayout Standalone Python Package (\*.whl) will be built and deployed under **klayout.app/Contents/pymod-dist/**.

```
$ ./build4mac.py -q qt5macports -r mp33 -p mp312 -Y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`LW-qt5MP.pkg.macos-Sequoia-release-Rmp33Pmp312`** directory, where
* "LW-"        means this is a lightweight package.
* "qt5MP"      means that Qt5 from MacPorts is used.
* "Rmp33Pmp312" means that Ruby is 3.3 from MacPorts; Python is 3.12 from MacPorts.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.

### 6C. Fully Homebrew-flavored build with Homebrew Ruby 3.3 and Homebrew Python 3.12
> [!IMPORTANT]
> To build KLayout >= 0.29.0, you need "Qt6" >= 6.7.0 to address [the compilation issue](https://github.com/KLayout/klayout/issues/1599).<br>

0. Install Homebrew, then install Qt6, Ruby 3.4, Python 3.12, and libgit2 by
```
$ brew install qt@6
$ brew install ruby@3.4
$ brew install python@3.12
$ brew install libgit2
$ cd /where/'build.sh'/exists
$ cd macbuild
$ ./python3HB.py -v 3.12
```
1. Invoke **`build4mac.py`** with the following options:
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt6brew -r hb34 -p hb312
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-Y" to deploy executables and libraries under **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.<br>

```
$ ./build4mac.py -q qt6brew -r hb34 -p hb312 -Y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`LW-qt6Brew.pkg.macos-Sequoia-release-Rhb34Phb312`** directory, where
* "LW-"        means this is a lightweight package.
* "qt6Brew"    means that Qt6 from Homebrew is used.
* "Rhb34Phb312" means that Ruby is 3.4 from Homebrew; Python is 3.12 from Homebrew.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.

> [!WARNING]
> We can no longer use the legacy **pip** command with Homebew Python@3.12, and we will get,
> ```
> error: externally-managed-environment
> ```
> To avoid this error, use a virtual environment, as Homebrew suggests.<br>
> See `HomebrewUser-ReadMeFirst.txt` in `Resources/script-bundle-B.zip` for details.

### 6D. Partially Homebrew-flavored build with System Ruby and Homebrew Python 3.11
> [!IMPORTANT]
> To build KLayout >= 0.29.0, you need "Qt6" >= 6.7.0 to address [the compilation issue](https://github.com/KLayout/klayout/issues/1599).<br>

0. Install Homebrew, then install Qt6, Python 3.11, and libgit2 by
```
$ brew install qt@6
$ brew install python@3.11
$ brew install libgit2
$ cd /where/'build.sh'/exists
$ cd macbuild
$ ./python3HB.py -v 3.11
```
1. Invoke **`build4mac.py`** with the following options:
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt6brew -r sys -p hb311
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-y" to deploy executables and libraries (including Qt and Python frameworks) under the **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.

```
$ ./build4mac.py -q qt6brew -r sys -p hb311 -y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`HW-qt6Brew.pkg.macos-Sequoia-release-RsysPhb311`** directory, where
* "HW-"        means this is a heavyweight package because both Qt6 and Python Frameworks are deployed.
* "qt6Brew"    means that Qt6 from Homebrew is used.
* "RsysPhb311"  means that Ruby is OS-bundled; Python is 3.11 from Homebrew.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.
> [!IMPORTANT]
> So far, the deployment of Homebrew Ruby is not supported.<br>
> Therefore, if you intend to use the "-y" option for deployment, you need to use the "-r sys" option for building.

### 6E. Heterogeneous combination of MacPorts Qt5, System Ruby, and Homebrew Python 3.11
> [!IMPORTANT]
> This is another practical solution for building a popular HW*.dmg package.

0. Install MacPorts, then install Qt5 and libgit2 by
```
$ sudo port install coreutils
$ sudo port install findutils
$ sudo port install qt5
$ sudo port install libgit2
```

Then, install Homebrew, then install Python 3.11 by
```
$ brew install python@3.11
$ cd /where/'build.sh'/exists
$ cd macbuild
$ ./python3HB.py -v 3.11
```

1. Invoke **`build4mac.py`** with the following options:
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt5macports -r sys -p hb311
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-y" to deploy executables and libraries under **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.<br>

```
$ ./build4mac.py -q qt5macports -r sys -p hb311 -y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`HW-qt5MP.pkg.macos-Sequoia-release-RsysPhb311`** directory, where
* "HW-"        means this is a heavyweight package because both Qt5 and Python Frameworks are deployed.
* "qt5MP"      means that Qt5 from MacPorts is used.
* "RsysPhb311" means that Ruby is OS-bundled; Python is 3.11 from Homebrew.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.

### 6F. Fully Anaconda3-flavored build with Anaconda3 Ruby 3.2 and Anaconda3 Python 3.12
0. Install Anaconda3 (Anaconda3-2024.10-1-MacOSX-x86_64.pkg), then install Ruby 3.2 and libgit2 by
```
$ conda install ruby=3.2.2
$ conda install libgit2=1.6.4
```

1. Invoke **`build4mac.py`** with the following options:
```
$ cd /where/'build.sh'/exists
$ ./build4mac.py -q qt5ana3 -r ana3 -p ana3
```
2. Confirm successful build (it will take about one hour, depending on your machine spec).
3. Rerun **`build4mac.py`** with the same options used in 1. PLUS "-Y" to deploy executables and libraries under **`klayout.app`** bundle.<br>
   The buddy command-line tools (strm*) will also be deployed under **klayout.app/Contents/Buddy/** in this step.<br>
   If you use `--buildPymod` option in Step-1 and Step-3, the KLayout Standalone Python Package (\*.whl) will be built and deployed under **klayout.app/Contents/pymod-dist/**.

```
$ ./build4mac.py -q qt5ana3 -r ana3 -p ana3 -Y
```
  The application bundle **`klayout.app`** is located under:<br>
  **`LW-qt5Ana3.pkg.macos-Sequoia-release-Rana3Pana3`** directory, where
* "LW-"        means this is a lightweight package.
* "qt5Ana3"    means that Qt5 from Anaconda3 is used.
* "Rana3Pana3" means that Ruby (3.2) is from Anaconda3; Python (3.12) is from Anaconda3.
4. Copy/move the generated application bundle **`klayout.app`** to your **`/Applications`** directory for installation.
5. You may have to set the `PYTHONHOME` environment variable like:
```
export PYTHONHOME=$HOME/opt/anaconda3
```

### 6G. Other combinations
Logically, several module combinations other than 6A through 6F are possible, including `nil` choice.<br>
The resultant package directory name will begin with **`EX-`** (exceptional) if you choose such a combination.

### 6H. Using the git-based Salt Package Manager through a proxy server
If you use the git-based Salt Package Manager through a proxy server, you need to set the `KLAYOUT_GIT_HTTP_PROXY` environment variable. For example,
```
$ export KLAYOUT_GIT_HTTP_PROXY="http://111.222.333.444:5678"
```
Ask your system administrator for the actual IP address and port number of your proxy server.

It is highly recommended that this setting is included in a launching service script bundle.<br>
A sample content (`*.app.Bash`) of the script bundle can be found in `Resources/script-bundle-[A|B|H|P|S].zip`.

----

# 7. QA Tests
You can optionally conduct QA tests using the `ut_runner` executable.<br>
[This forum post](https://www.klayout.de/forum/discussion/comment/11012/#Comment_11012) provides information on the unit tests, mainly for Linux.
In the macOS environment, the QA test working directory is `[ST|LW|HB]-build_directory.macQAT`, where you will find `macQAT.py`, a wrapper script for the `ut_runner` executable.<br>
Some required environment variables including `TESTSRC`, `TESTTMP`, and `DYLD_LIBRARY_PATH` are set by `macQAT.py`.<br>

1. Change directory to `[ST|LW|HB]-build_directory.macQAT`
```
cd [ST|LW|HB]-build_directory.macQAT
```

2. To print usage of `ut_runner`, run `macQAT.py` with '-u'
```
./macQAT.py -u
```

3. To start the KLayout main GUI window, run `macQAT.py` with '-k'
```
./macQAT.py -k
```

4. To normally run `ut_runner`, invoke `macQAT.py` with '-r'
```
./macQAT.py -r
```

If required, you can use the `-x <test>` option to skip some erroneous tests.

----

# 8. Making a DMG installer
You can make a DMG installer using another Python script **`makeDMG4mac.py`**.<br>
This script requires a directory generated by **`build4mac.py`** with the [-y|-Y] option (refer to 6A through 6F).

1. Make a symbolic link (if it does not exist) from the parent directory (where **`build.sh`** exists) to **`makeDMG4mac.py`**, that is,
```
makeDMG4mac.py -> macbuild/makeDMG4mac.py
```
2. Invoke **`makeDMG4mac.py`** with -p and -m options, for example,
```
$ cd /where/'build.sh'/exists
$ ./makeDMG4mac.py -p LW-qt5MP.pkg.macos-Sequoia-release-Rmp33Pmp312 -m
```
This command will generate the two files below:<br>
* **`LW-klayout-0.30.2-macOS-Sequoia-1-qt5MP-Rmp33Pmp312.dmg`**      ---(1) the main DMG file
* **`LW-klayout-0.30.2-macOS-Sequoia-1-qt5MP-Rmp33Pmp312.dmg.md5`**  ---(2) MD5-value text file

# Known issues
Because we assume some specific versions of non-OS-standard Ruby and Python, updating Homebrew, MacPorts, or Anaconda3 may cause build- and link errors.<br>
In such cases, you need to update the dictionary contents of **`build4mac_env.py`**.

# Final comments
No need to say KLayout is a great tool!<br>
With the object-oriented script language (both Ruby and Python) support, our error-prone layout jobs can be significantly simplified and sped up.<br>
Building KLayout from its source code is not difficult. Try it with your favorite environment!

[End of File]
