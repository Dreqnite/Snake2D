[![Build Status](https://travis-ci.org/Dreqnite/Snake2D.svg?branch=develop)](https://travis-ci.org/Dreqnite/Snake2D)
[![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
# Snake2D
A simple Snake2D game written with usage of C++ and SFML
## General information
Snake2D is:
1. Created for the purpose of studying C++ and SFML, so I can not give any guarantees regarding its stability. It's not recommended to use this project in a production!
2. Released under the Affero General Public License (AGPL-3.0).
3. Written with usage of [Simple and Fast Multi-Media Library (SFML)](https://github.com/SFML/SFML). It's [license](https://github.com/SFML/SFML/blob/master/license.md).
## Needed software
The following software needs to be installed before Snake2D can be built:
1. [Git](https://git-scm.com/) (Version Control System)
2. [CMake](https://cmake.org/download/) (Build System)
3. [SFML](https://github.com/SFML/SFML) (Simple and Fast Multi-Media Library). You can either clone and build library manually or install package manager to do it for you. Package managers allow easier maintanence of project dependencies. I use Visual Studio 2017 with [vcpkg](https://github.com/Microsoft/vcpkg) packet manager. vcpkg does all the "magic" work for you - you do not even need to specify paths for include/lib in the Solution Properties. When you write `#include <SFML/Graphics.hpp` and start building process - all needed dlls appear in the executable folder, so I highly recommend to use that package manager if you like VS. Other options can be: [Conan](https://conan.io/), [Hunter](https://github.com/ruslo/hunter), [Buckaroo](https://buckaroo.pm/). As of vcpkg, here is a list of useful links:
   * [Prerequisites and Quick Start](https://github.com/Microsoft/vcpkg/blob/master/README.md);
   * [Installing and Using](https://github.com/Microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md).
### vcpkg installation guide (unofficial)
You can find an official installation guide in the second link ("Installing and Using").
* Open `git-bash.exe` or `git-cmd.exe`. Note: If you prefer to work with a native CMD, you will have to add `git.exe` path to the `PATH` environment variable, so you can execute Git commands everywhere.
* Navigate to the folder where you want to store vcpkg: `cd <path/to/vcpkg/>`.
* Clone vcpkg: `git clone https://github.com/Microsoft/vcpkg.git`.
* Move to the vcpkg's root directory: `cd vcpkg`.
* Build vcpkg: `./bootstrap-vcpkg.bat`.
* Apply user-wide integration for this vcpkg root: `./vcpkg integrate install`.
* Note the line after completion: `CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=<path>/vcpkg/scripts/buildsystems/vcpkg.cmake"`.
### SFML installation
*Using vcpkg:*
* Open command line and execute `vcpkg install sfml:<platform>`. Instead of `<platform>` put `x86-windows` for 32-bit and `x64-windows` for 64-bit system respectively.
* Check installed packages: `vcpkg list`. Dependencies of SFML will be also installed (because SFML depends on OpenGL and some other libs).

*Using Git and CMake:*
* Navigate to the folder where you want to store SFML: `cd <path/to/vcpkg/>`.
* Clone SFML: `git clone https://github.com/SFML/SFML.git`.
* Build SFML:
  * [Building on Linux](https://www.sfml-dev.org/tutorials/2.5/start-linux.php);
  * [Building on Windows](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)
## Building Snake2D
This game requires a modern C++ compiler that supports C++14!
* Go to the project root: `cd <path>/Snake2D`.
* Make a directory to build in: `mkdir build`.
* Navigate to that directory: `cd build`.
* Execute CMake command with needed values of the following options:
  * `-G` - generator type. Here is the list of supported [generators](https://cmake.org/cmake/help/v3.0/manual/cmake-generators.7.html). If SFML has x86 build, Snake2D should be built with x86 too. Specify `ARD` for x86 or `Win64` for x64 platform respectively. 
  * `-DCMAKE_BUILD_TYPE:STRING` - cmake build type: `"Debug"` or `"Release"`.
  * `-DSFML_DIR:PATH` - path to the `SFMLConfig.cmake`. If you use vcpkg, it will be in the following location: `<path>/vcpkg/installed/<platform>-windows/share/sfml`, where `<platform>` is `x86` or `x64`.
Example:
```
cmake -G "Visual Studio 15 2017 Win64"
	  -DCMAKE_BUILD_TYPE:STRING="Debug"
	  -DSFML_DIR:PATH="D:/vcpkg/installed/x64-windows/share/sfml" ..
```
* Compile: `cmake --build .`.
