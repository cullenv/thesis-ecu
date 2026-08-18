# Engineering Journal Template (Real Journals are below)

## [YYYY-MM-DD] - [One-line summary of the day, e.g., "Setting up Git and WSL"]

### 🎯 Objective
*What is the single goal for today's session?*
- [ ] Example: Get the code folders on GitHub and set up my workflow.

### 🧠 Decisions & Discoveries
*The most important section for your final thesis. Why did you do it this way?*
- **Decision:** Chose to use WSL2 and CMake instead of STM32CubeIDE.
- **Why:** CMake makes automated testing in the cloud possible, which is a core requirement of my thesis. IDEs hide too much of the build process and will help me learn and take away more information at the end
  
- **Decision:** 
- **Why:*

### 🐛 Bug Tracker / Roadblocks
*Don't just say "it broke." Paste the error and the fix so you never solve the same bug twice.*
- **Error:** Git wasn't pushing empty folders. 
- **Fix:** Learned that Git only tracks files. Added `.gitkeep` files to `app`, `services`, etc., to force Git to track the structure.

- **Error:**
- **Fix:**

### 🍞 Breadcrumb for Tomorrow
*Be incredibly specific. Leave a note for your future self so you can start working immediately without thinking.*
- **Status:** Folders are pushed to GitHub. WSL is fully configured. 
- **Next Action:** Open `requirements.md` and write the first 5 "shall-statements" for the motor timing. 

---

## [2026-08-18] - [One-line summary of the day, e.g., "Setting up Git and WSL"]

### 🎯 Objective

- [ ] Draft up requirements 1-15 Understand why these requirements are important and testable. Remove opinions from testable requiremenst

### 🧠 Decisions & Discoveries

- **Decision:** Chose to use WSL2 and CMake instead of STM32CubeIDE.
- **Why:** CMake makes automated testing in the cloud possible, which is a core requirement of my thesis. IDEs hide too much of the build process.

### 🐛 Bug Tracker / Roadblocks

- **Error:** Journal.md did not hold all of the information that I put for 08/17/26 
- **Fix:**DO NOT FORGET TO COMMIT CHANGES TO YOUR MARKDOWN FILE ONLINE and use a git pull request to grab that online file and bring it to your structure

### 🍞 Breadcrumb for Tomorrow

- **Status:** Folders are pushed to GitHub. WSL is fully configured. 
- **Next Action:** Open `requirements.md` and write the first 5 "shall-statements" for the motor timing. 

---
