# ArenaSystem

Wrapper for ArenaSDK.

---

## Table of contents

1. [ Overview ](#overview)
2. [ Dependencies ](#dependencies)
3. [ Installation ](#installation)
4. [ Usage ](#usage)
5. [ Tests ](#tests)
6. [ Release History ](#release)
7. [ Contributing ](#contributing)
8. [ Support ](#support)
9. [ FAQ ](#faq)

---

<a name="overview"></a>
## 1. Overview

**ArenaSystem** is the library designed for to control the operation of the ArenaSDK. It is developed based on C++17.</br>

Note:</br>
* If you change the network parameters in the config, the application will find the device with the specified serial number and change its network parameters to new ones from the group [network].

---

<a name="dependencies"></a>
## 2. Dependencies

Basic:<br>

- [build-essential](https://packages.debian.org/ru/sid/build-essential)
- [C++17 (GCC-8, G++-8)](https://en.cppreference.com/w/cpp/17)
- [CMake (> 3.10)](https://cmake.org)
- [Make (> 4.2)](https://en.wikipedia.org/wiki/Make_(software))
- [LCov (> 1.14)](http://ltp.sourceforge.net/coverage/lcov.php)
- [GCov (> 9.3)](https://linux.die.net/man/1/gcov)
- [CLang-Tidy (> 10.0)](https://clang.llvm.org/extra/clang-tidy/)
- [Ninja (> 1.10)](https://ninja-build.org)
- [Valgrind (> 3.15)](https://valgrind.org)

Third-party (for visualization):<br>

- [Doxygen (> 1.8)](https://www.doxygen.nl/index.html)
- [Graphviz](https://graphviz.org)
- [Latex](https://www.latex-project.org/get/)
- [Tree](https://pingvinus.ru/note/tree)

Compatible versions:<br>

- Firmware: 1.65.0.0
- ArenaSDK: 0.1.3

---

<a name="installation"></a>
## 3. [Installation](./doc/INSTALL.md)

The installation procedures in Linux Ubuntu 16.04/14.04 32-bit LTS or Linux Mint 19.* /20. * 64-bit are shown [here](./doc/INSTALL.md) as examples.

---

<a name="usage"></a>
## 4. Usage

Include as submodule to ./external and:

| № | Type                                                       |
|---|------------------------------------------------------------|
| 1 | CMakeLists.txt (as shared library)                         |
| 2 | src.cmake (as cmake-script)                          |

- Shared library

```
set( ARENA_SYSTEM_DIR ${CMAKE_CURRENT_LIST_DIR}/external/zcm_types )
set( ARENA_SYSTEM_LIB ${PROJECT_NAME}_static )

add_subdirectory( ${ARENA_SYSTEM_DIR} )

target_link_libraries( ${PROJECT_NAME} ${ARENA_LIBS} )
```

- All types from cmake script

```
include( ${CMAKE_CURRENT_LIST_DIR}/external/ArenaSystem/src/src.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/external/ArenaSystem/external/ArenaSDK/sdk.cmake )
```

---

<a name="tests"></a>
## 5. [Tests](./tests/README.md)

---

<a name="release"></a>
## 6. [Release History](./doc/HISTORY.md)

---

<a name="contributing"></a>
## 7. Contributing

1. Fork it (<http://bb.niias/projects/TOOL/repos/camera_lucid/browse>).
2. Read [Readme](./README.md), [License](./doc/LICENSE.md), [Code of Conduct](./doc/CODE_OF_CONDUCT.md) and [Condributing Guidelines][contributing].
3. Create your fix or feature branch (`git checkout -b feature/name`).
4. Make changes according to [Condributing Guidelines][contributing].
5. Make unit tests.
6. Build repo and tests.
7. Correct Readmes for whole directories.
8. Ensure that it is likely to be merged.
9. Commit your changes (```git add . & git commit -m "Feature. Add wrapper class WrapperClass."```).
10. Push to the branch (```git push origin feature/new-wrapper-class```)
11. Create a new Pull Request to `develop`

---

<a name="support"></a>
## 8. Support

Reach out to me at one of the following places!

- Telegram at - <a href="http://https://telegram.org" target="_blank">`@DLeliuhin`</a>
- Email at - dleliuhin@gmail.com.

---

<a name="faq"></a>
## 9. [FAQ](doc/FAQ.md)

---

**JSC NIIAS**
