# Scripts

Scripts for app manipulating.

---

- [update_submodules.sh](update_submodules.sh)

    Allow to update dependent submodules. After updating build them.

---

- [install.sh](install.sh)

    Installs all basic dependencies for the basic functioning of the application without visualization or documentation.

---

- [install-third-party.sh](install-third-party.sh)

    Installs all basic dependencies for the all functioning of the application with data and code-coverage visualization, documentation.

---

- [build.sh](build.sh)

    Builds the application without visualization together with updated submodules. The output is a binary file in the *build* subdirectory.

---

- [sanalyze.sh](sanalyze.sh)

    Performs static analysis of the project code using CLang-Tidy.

    See CLang-Tidy static analyzer [option list](https://clang.llvm.org/extra/clang-tidy/checks/list.html).

---

- [test.sh](test.sh)

    Starts Unit testing of the service code with code coverage.

---

- [coverage.sh](coverage.sh)

    Starts code coverage by unit tests. Two arguments need.

*Example:* ```./scripts/coverage.sh tests/build_tests ../../doc/coverage```

| Argument| Description                       | Example            |
|---------|-----------------------------------|--------------------|
| №1      | Path to tests build directory     | tests/build_tests  |
| №2      | Path to output coverage directory | ../../doc/coverage |

---

- [codestyle.sh](codestyle.sh)

    Checks code based on [readability* group](https://clang.llvm.org/extra/clang-tidy/checks/list.html) code style.

*Example:* ```./scripts/codestyle.sh```

More [info](http://bb.niias/projects/TOOL/repos/cpp_codestyle/browse).

---

- [doc.sh](doc.sh)

    Carries out auto-documenting of code according to Doxygen tags. For visualization, you can use any browser by first opening: <br/>

```your-browser ./doc/doxygen/html/index.html```

---

- [danalyze.sh](danalyze.sh)

    Performs dynamic code analysis using Valgrind modules - memcheck, cachegrind, massif. Provides detection of memory leaks, and other errors associated with improper work with memory areas, reading or writing outside the allocated regions. Analyzes code execution by collecting (mis) cache hits and branch points (when the processor mispredicts a branch). Allows you to analyze the allocation of memory by different parts of the program.

---

- [refresh.sh](refresh.sh)

    Clears all temporary IDE files.

---

- [rename.sh](rename.sh)

    Renames all lines with camera_lucid in the whole project to the new project naming according to the script input argument.

*Example:* <br>

```./scripts/rename.sh camera_lucid new_service preview``` - preview change files and lines.

```./scripts/rename.sh camera_lucid new_service``` - recursively replace first argument to second in all files.

| Argument      | Description                        | Example            |
|---------------|------------------------------------|--------------------|
| №1            | The name to be replaced            | camera_lucid  |
| №2            | New service naming                 | new_service        |
| №3 (optional) | File display mode for modification | --preview          |

---

- [rename.sh](class.sh)

    Create a new directory with template files:

| Argument      | Description                        | Example  |
|---------------|------------------------------------|----------|
| №1            | The class new name to be created   | NewClass |
| №2            | Output directory path              | ./src    |

After running: ```./scripts/class.sh NewClass ./src```

```
new_class/
├── new_class.cmake
├── new_class.cpp
├── new_class.h
└── README.md

0 directories, 4 files

```

---

- [setup-hooks.sh](setup-hooks.sh)

    Substitutes client hooks to .git/hooks

---

- [hooks/check-debug.sh](hooks/check-debug.sh)

    Script which find functions left in the code during debugging such as:  

-- vdeb<br>
-- vdebug<br>
-- VDEB<br>
-- printf<br>

---

- [hooks/check-commit-msg.sh](hooks/check-commit-msg.sh)

    Check commit message title and description by pattern from following names:

-- REBASE/Rebase/rebase<br>
-- FIX/Fix/fix<br>
-- HOTFIX/HotFix/Hotfix/hotfix<br>
-- FEATURE/Feature/feature<br>
-- TEST/Test/test<br>
-- BUGFIX/BugFix/Bugfix/bugfix<br>

---
