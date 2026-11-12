# Defect and Learning Log

| Defect ID | Layer / Module | Detection Phase | Description | Root Cause & Resolution |
|---|---|---|---|---|
| BUG-001 | Application / `motor_control.c` | Unit Testing | PWM clamping logic incorrectly allowed 100.0f% duty cycle. | **Cause:** Hardcoded saturation bounds mismatched REQ-005.<br>**Fix:** Updated `MOTOR_PWM_MAX_DUTY` to 95.0f and updated CppUTest assertions to match. |
| BUG-002 | Application / `com_manager.c` | Unit Testing | CAN transmission sent via ID `0x105` instead of `0x101`. | **Cause:** Magic number typo in frame setup.<br>**Fix:** Corrected CAN ID to `0x101` in C implementation and test assertion per REQ-011. |
| BUG-003 | HAL / Mocks | Linker | `undefined reference to Encoder_GetSpeed` during host compilation. | **Cause:** Data type and naming mismatch; mock defined `Encoder_GetSpeedRPM` (float) while header defined `Encoder_GetSpeed` (int16_t).<br>**Fix:** Aligned mock signatures to match `hal_encoder.h`. |
| BUG-004 | MCAL / `mcal_pwm.c` | Compiler | Fatal error: `main.h: No such file or directory`. | **Cause:** STM32CubeIDE boilerplate heavily coupled MCAL to application headers.<br>**Fix:** Removed `main.h`, included `stm32g4xx.h`, and created mock register maps for x86 host compilation. |
| BUG-005 | Architecture / HAL | Static Analysis / IDE | Header collision and redundancy between `pwm.h` and `hal_pwm.h`. | **Cause:** Artifacts from legacy codebase migration.<br>**Fix:** Deleted redundant `pwm.h`, standardized all includes to `hal_pwm.h` to enforce strict 4-layer architecture. |
| BUG-006 | Application / `motor_control.c` | Unit Testing | `MockPWM_GetLastDutyCycle()` returned 0.0f during nominal testing. | **Cause:** Calculated `control_effort` was never actually dispatched to the hardware API.<br>**Fix:** Added `PWM_SetDutyCycle(control_effort);` to the end of the motor control task. |

Current Govcor is 70% NOT GOOD!!!!