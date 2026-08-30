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

## [2026-08-22] - Saturday: Continuous Integration (The Crucible)

### 🎯 Objective
- [x] Write `.github/workflows/build.yml`.
- [x] Provision the Ubuntu runner with GCC, CMake, CppUTest, and Clang tools.
- [x] Establish the automated pipeline: Generate -> Lint -> Compile -> Test.

### 🧠 Decisions & Discoveries
- **Decision:** Ran native Linux GCC on the GitHub `ubuntu-latest` runner instead of `arm-none-eabi-gcc`.
- **Why:** This achieves hardware independence. By compiling the test executable for x86, the cloud runner can execute the C logic tests natively in milliseconds to prove the math works before ARM hardware is ever involved.
- **Decision:** Placed the Clang-Tidy step *before* the Make compilation step.
- **Why:** "Fail fast" principle. If the static analyzer detects a MISRA violation or memory leak, the pipeline halts immediately, saving cloud compute time and preventing bad code from compiling.

### 🍞 Breadcrumb for Monday (Week 2)
- **Status:** CI pipeline is live and green. Week 1 is officially complete. 
- **Next Action:** Begin Week 2 by integrating `gcov` and `gcovr` into `CMakeLists.txt` to measure exactly how much of our code the tests are actually checking.

## [2026-08-27] - Week 2, Monday (Thursday got pretty sick) : Test Coverage Tooling

### 🎯 Objective
- [x] Inject GCC coverage tracking flags into the CMake test build.
- [x] Generate execution data (`.gcno` and `.gcda`).
- [x] Use `gcovr` to generate a local HTML coverage dashboard.

### 🧠 Decisions & Discoveries
- **Decision:** Applied `--coverage` strictly to the `run_tests` executable, NOT `ecu_firmware`.
- **Why:** The test executable runs on a PC with a file system, allowing GCC to dump `.gcda` execution logs to the hard drive. If deployed to the bare-metal STM32, it would consume precious RAM and have nowhere to save the files.
- **Discovery:** `gcovr` reports 0% coverage because the dummy test (`1 == 1`) does not invoke any application logic. Coverage metrics prove not just that tests pass, but that they actively stimulate the production code paths.

- **Industry Standard (ISO 26262 ASIL-D):** In automotive safety-critical systems, it is a legal requirement to prove that 100% of the logic was executed by a test. We use GCC's built-in `gcov` tool to mathematically prove this execution.
- **Hardware Constraint:** We strictly apply `--coverage` tracking *only* to the `run_tests` executable running on the PC. We absolutely do not want coverage tracking in our `ecu_firmware` build because the hidden integer counters consume precious RAM and CPU cycles on the physical microcontroller.

### 🍞 Breadcrumb for Tuesday
- **Status:** Local coverage dashboard generation is working. 
- **Next Action:** Enforce coverage rules in the cloud by modifying the GitHub Actions CI pipeline to fail if coverage drops below 90%.

## [2026-08-26] - Week 2, Wednesday: The Hardware Abstraction Headers

### 🎯 Objective
- [x] Write the MCAL/HAL header files (`adc.h`, `pwm.h`, `encoder.h`, `can.h`).
- [x] Define function prototypes without implementing the hardware-specific C files.

### 🧠 Decisions & Discoveries
- **Decision:** Utilized Contract-Driven Development. 
- **Why:** By defining the hardware interfaces as standard C headers first, the core Application logic (PI controller, state machine) can be written and tested completely independent of the STM32 datasheet. If the physical microcontroller changes, only the underlying `.c` files need to be rewritten; the logic remains untouched.
- **Decision:** Used `uint16_t` (milliamps) instead of `float` (Amps) for the ADC current reading.
- **Why:** Fixed-point math avoids the massive overhead of floating-point libraries on bare-metal processors, saving flash memory and execution cycles.

## [2026-08-27] - Week 2, Thursday: Generating Hardware Mocks 30th

### 📚 Core Concepts Learned
- **Concept: What is a Mock? (The Stunt Double):** A mock is a fake C function used to test application logic without physical hardware. If my application tries to write to the physical STM32 chip, my PC will crash. The mock acts as a stunt double to safely absorb that function call.
- **Mental Model: The "Spy with a Notebook":** 
  - **Outputs (PWM):** The mock acts as a spy recording actions. When my code calls `PWM_SetDutyCycle(50)`, the Spy writes down: *"The app asked for 50% power."* My tests can then check the Spy's notebook to verify my math is right.
  - **Inputs (ADC):** The Spy can also inject fake data. I can tell the Spy: *"When the app asks for motor current, hand them the number 6000 (6 Amps)."* This lets me safely test catastrophic faults like an engine fire.

### 🛠️ Syntax & Compiler Traps
- **Trap 1: The Semicolon Chain-Breaker:** In C++, `mock().actualCall().withParameter()` is a single continuous command called *method chaining*. Putting a semicolon after the first parenthesis breaks the chain and causes a compiler error.
- **Trap 2: The Double Pointer Accident:** When a function argument is already a pointer (e.g., `uint16_t *value`), passing `&value` to the mock creates a double pointer (`**`). The mock just needs the original address to know where to write the fake data.

### 🍞 Breadcrumb for Friday
- **Status:** Hardware mocks are successfully compiling into the PC test framework.
- **Next Action:** Architecture Review. Map the requirements to the tests to ensure we haven't missed any physical inputs/outputs.