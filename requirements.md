# System Requirements Specification (SRS)
**Project:** ECU Firmware & HIL Simulator Thesis  
**Author:** Cullen Veasley
**Last Updated:** 2026-08-18  

## Overview
This document defines the strict, testable software and hardware requirements for the ECU motor control system that I am building. Every requirement listed here *must* trace to an automated test in either the PC-based unit testing suite or the Python-based HIL test harness. I want to have these tests to challenge my understanding of physics constraints as well as safe and strong coding practices.

### Verification Methods
*   **UT (Unit Test):** Verified in C via CppUTest/Ceedling on the PC.
*   **HIL (Hardware-in-the-Loop):** Verified via Python test script interacting with the board over CAN.
*   **SA (Static Analysis):** Verified via MISRA/clang-tidy checks.

---

## 1. System & Scheduling
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-001** | The scheduler shall execute the Motor Control Task every 1 ms (± 0.1 ms). | Scheduler | UT | ⬜ Not Started |
| **REQ-002** | The scheduler shall execute the CAN Transmit Task every 10 ms (± 1 ms). | Scheduler | UT | ⬜ Not Started |
| **REQ-003** | The scheduler shall execute the Diagnostic Monitor Task every 100 ms (± 5 ms). | Scheduler | UT | ⬜ Not Started |

<center><sub>Why did I pick these requirements: I wanted to learn on why it was important and the standard to have the motor control task polling faster than the diagnostic task. Understanding how to why saving CPU cycles whenever possible</sub></center>

## 2. Hardware Interfaces (HAL & MCAL)
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-004** | The ECU shall command a 0% PWM duty cycle to the motor driver upon system initialization. | HAL | HIL | ⬜ Not Started |
| **REQ-005** | The ECU shall limit the maximum commanded PWM duty cycle to 95% to protect the motor driver hardware. | HAL | UT | ⬜ Not Started |
| **REQ-006** | The ECU shall read the hardware quadrature encoder to calculate the motor speed in RPM every 1 ms. | HAL | HIL | ⬜ Not Started |

<center><sub>Generating a ramp is essential for DC motors as it acts as a short circuit at 0 RPM so if you were commanding 0 to 5000 RPM you would have an in-rush of current, which has a multitude of differing problems.</sub></center>

## 3. Control Logic (Application Layer)
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-007** | The ECU shall implement a PI controller to minimize the error between Target Speed and Current Speed. | App/PI | UT | ⬜ Not Started |
| **REQ-008** | The ECU shall limit the rate of change of the Target Speed to a maximum of 1000 RPM per second. | App/PI | UT | ⬜ Not Started |
| **REQ-009** | If the PI controller output exceeds 95% duty cycle, the ECU shall freeze the integral accumulator. | App/PI | UT | ⬜ Not Started |

<center><sub>Why: Learning more about PWM, higher duty cycles for our PWM will allow our motor to run faster, but there is a limit and typically should not exceed 95%. If we were at 100% our bootstrap capacitor on our PWM module would overheat and blow up.</sub></center>

## 4. CAN Communications
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-010** | The ECU shall accept a Target Speed command via CAN message ID `0x100`. | HAL/CAN | HIL | ⬜ Not Started |
| **REQ-011** | The ECU shall transmit Current Speed and Fault Status via CAN message ID `0x101` every 10 ms. | HAL/CAN | HIL | ⬜ Not Started |
| **REQ-012** | If a Target Speed CAN message is not received for 500 ms, the ECU shall set the Target Speed to 0 RPM. | App/Comm | HIL | ⬜ Not Started |

## 5. Diagnostics & Faults
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-013** | If calculated RPM is 0 while commanded PWM > 50% for 100 ms, set "Stalled Rotor" fault (DTC `0x9101`). | App/Diag | UT / HIL | ⬜ Not Started |
| **REQ-014** | If the encoder hardware reports an error flag, set "Encoder Loss" fault (DTC `0x9102`). | App/Diag | UT / HIL | ⬜ Not Started |
| **REQ-015** | Upon active DTC, the ECU shall force 0% PWM and ignore CAN Target Speed commands until cleared. | App/Diag | UT / HIL | ⬜ Not Started |


