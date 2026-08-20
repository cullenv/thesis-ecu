# Engineering Journal 

## [YYYY-MM-DD] - [One-line summary of the day]
<sub>Template (Real Journals are below)</sub>

### 🎯 Objective

- [ ] Example: 

### 🧠 Decisions & Discoveries

- **Decision:** 
- **Why:** 
  
- **Decision:** 
- **Why:** 

### 🐛 Bug Tracker / Roadblocks

- **Error:** 
- **Fix:** 

- **Error:** 
- **Fix:** 

### 🍞 Breadcrumb for Tomorrow

- **Status:** 
- **Next Action:** 

---

## [2026-08-18] - [CMake files and First 15 Requirements"]

### 🎯 Objective

- [ ] Draft up requirements 1-15 Understand why these requirements are important and testable. Remove opinions from testable requirements. Added CMake and Main.c files

### 🧠 Decisions & Discoveries

- **Discovery:** Understood the separation of concerns in the C build pipeline. 
- **Concept:** CMake is a build system generator, not a compiler. It reads `CMakeLists.txt` and automatically generates a  `Makefile`  to my  system. The `make` command then executes that blueprint, calling the actual `GCC` compiler under the hood with all the correct flags and paths. 
- **Why this matters:** This abstracts away the  GCC compiler arguments. As the architecture scales across `app/`, `hal/`, and `services/`, CMake will automatically handle the complex linking between directories, making the build reproducible both similar to what and IDE will do for you

- **Discovery:** Understood out-of-source builds and Linux directory navigation.
- **Concept:** `CMakeLists.txt` is a hardcoded filename that the CMake executable automatically looks for. By running `cmake ..` from inside the `build/` directory, the `..` tells CMake to look one level up (the project root) for the blueprint, but generate all the makefiles and binaries inside the current `build/` directory.
- **Why this matters:** This keeps all generated build files into a single folder. It keeps the architecture (`app/`, `services/`, etc.)  clean and means I can completely reset my build environment just by deleting the `build/` folder, without accidentally deleting my source code.

### 🐛 Bug Tracker / Roadblocks

- **Error:** My previous days journal was not present!
- **Fix:** DO NOT FORGET TO COMMIT CHANGES TO YOUR MARKDOWN FILE ONLINE and use a git pull request to grab that online file and bring it to your structure

- **Error:** GCC is the thing that takes our program and turns it to 1s and 0s (if you remeber about a month ago you had write out the entire gcc string to compile it using the rules that we set, we automated this with a CMake file and allowed it to create an executable)
- **Fix:** Instead of writing all of these rules we can use the make file

### 🍞 Breadcrumb for Tomorrow

- **Status:** CMake files are made and ready to go.
- **Next Action:** Draft out the next 15 requirements looking for 30 test in total

---

## [2026-08-19] - ["Last 15 Requirements"]

### 🎯 Objective

- [ ] Draft up requirements 16-30 Ensure that these are objective and testable

### 🧠 Decisions & Discoveries

- **Discovery:** Learned about the concept of cosmic rays and how it could happen to a vehicles ECU and the importance of safe guarding it
- **Concept:** If a cosmic ray flips a bit in a vehicle's ECU, it can   malfunction like unintended acceleration or sudden engine stalls while driving. Factoring in error states ensures the computer instantly detects these random glitches and safely shifts the car into a backup "limp mode" rather than crashing the system entirely.

- **Discovery:** UDS and its importance
- **Concept:** OBD2 ports use the UDS langugae to pull and understand the stored fault codes in the NVM portion.
- **Why this matters:** Having a clean UDS report is essential for the lifecycle of you vehicles as a car going to the mechanic is a unavoidable situation.

### 🐛 Bug Tracker / Roadblocks

- **Error:** N/A
- **Fix:** N/A

### 🍞 Breadcrumb for Tomorrow

- **Status:** 
- **Next Action:** Understanding CppUTest or Ceedling and its importance

---

## [2026-08-19] - ["Understand and Intergrate the testing framework into our"]

### 🎯 Objective

- [ ] Use CppUTest as our testing frame work and set it up

### 🧠 Decisions & Discoveries

- **Decision:** Integrated CppUTest and configured CMake to build two separate executables: `ecu_firmware` and `run_tests`. 
- **Concept (Hardware Independence):** Professional embedded code is decoupled from the hardware. By using CppUTest, I am compiling my logic for my native x86 machine (my PC) rather than the ARM microcontroller. 
- **Why this matters:** When I write the PI controller math later, I can verify it calculates the correct duty cycles purely in software, running tests in 0.001 seconds on my PC, without ever needing to flash the physical STM32 board. This proves my logic is flawless before hardware variables are introduced.

### 🐛 Bug Tracker / Roadblocks

- **Error:** Linker failed with `cannot find -lcpputest` when compiling `run_tests`.
- **Root Cause:** GCC linker on Linux is case-sensitive. The library is installed as `libCppUTest.a`, but CMake requested `cpputest`.
- **Fix:** Changed `target_link_libraries(run_tests cpputest)` to `target_link_libraries(run_tests CppUTest CppUTestExt)` in `CMakeLists.txt`.

### 🍞 Breadcrumb for Tomorrow

- **Status:** Prove the test framework catches bugs by deliberately making a test fail (Red-Green-Refactor loop).
- **Next Action:** Change `CHECK_EQUAL(1, 1)` to `CHECK_EQUAL(1, 2)` in `tests/test_dummy.cpp`. Run `make && ./run_tests` and watch it fail. Change it back to verify the test harness is truly evaluating logic.
