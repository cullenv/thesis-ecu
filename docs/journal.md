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
