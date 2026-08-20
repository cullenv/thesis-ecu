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

## 6. Advanced Hardware Faults
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-016** | If the ADC reads a motor current exceeding 5 Amps for 10 ms, the ECU shall trigger an "Overcurrent" fault (DTC `0x9103`). | App/Diag | HIL | ⬜ Not Started |
| **REQ-017** | If the calculated acceleration exceeds physical limits (> 10,000 RPM/s), the ECU shall trigger a "Sensor Plausibility" fault (DTC `0x9104`). | App/Diag | UT | ⬜ Not Started |
| **REQ-018** | If the hardware CAN controller triggers a "Bus-Off" interrupt (too many physical wire errors), the ECU shall trigger DTC `0xC001` and suspend CAN transmissions. | HAL/CAN | UT/HIL | ⬜ Not Started |

<center><sub>Why: For REQ-016, and REQ-017 taking what I have learned in my automotive sensors class we understand that sensors do not always tell the truth and could glitch/mess up so we need to account for that in REQ-017 We also need to protect the motor as the MCU is the brains of the motor while the motor just spins.  For REQ-018, what happens when a cat chews threw the wire or get severed? We need to have protection for that. </sub></center>

## 7. Fault Management & Memory (NVM)
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-019** | A fault condition must remain continuously true for its defined "Debounce Time" (e.g., 50 ms) before its DTC status transitions from "Pending" to "Confirmed." | App/Diag | UT | ⬜ Not Started |
| **REQ-020** | Once a severity-1 fault (Stall, Overcurrent) is Confirmed, it shall remain Latched (active) even if the physical condition resolves, until explicitly cleared via CAN. | App/Diag | UT | ⬜ Not Started |
| **REQ-021** | The Fault Manager shall write all Confirmed DTCs to Non-Volatile Memory (NVM) so they persist across system power cycles. | Services/NVM | UT | ⬜ Not Started |
| **REQ-022** | Upon system initialization, the ECU shall read the NVM and restore any previously latched DTCs before enabling the motor driver. | Services/NVM | UT | ⬜ Not Started |

<center><sub>Why: We need to have and keep error states in our NVM for our mechanic and have debounce safe guards to protect ourselves from any nuance faults </sub></center>

## 8. UDS Diagnostics (ISO 14229)
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-023** | The ECU shall accept UDS requests on CAN ID `0x7E0` and transmit UDS responses on CAN ID `0x7E8`. | HAL/CAN | HIL | ⬜ Not Started |
| **REQ-024** | **Read DTC (0x19):** Upon receiving UDS Service `0x19 0x02 0x09`, the ECU shall transmit all Confirmed DTCs. | App/UDS | HIL | ⬜ Not Started |
| **REQ-025** | **Clear DTC (0x14):** Upon receiving UDS Service `0x14 0xFF 0xFF 0xFF`, the ECU shall clear all active/logged DTCs and wipe the NVM fault sector. | App/UDS | HIL | ⬜ Not Started |
| **REQ-026** | **Read Data (0x22):** Upon receiving UDS Service `0x22 0x01 0x01`, the ECU shall return the current PI controller Proportional (P) gain value. | App/UDS | HIL | ⬜ Not Started |
| **REQ-027** | **Write Data (0x2E):** Upon receiving UDS Service `0x2E 0x01 0x01 [Data]`, the ECU shall update the PI controller's P gain in memory and recalculate the loop. | App/UDS | HIL | ⬜ Not Started |
| **REQ-028** | **Negative Response (0x7F):** If a UDS request asks for an unsupported Service or Data ID, the ECU shall reply with a Negative Response Code (NRC `0x7F`). | App/UDS | HIL | ⬜ Not Started |

<center><sub>Why: Keeping the mechanic (me in this instance :) ) in mind, these set of requirements will make it easy for them to see the codes that the motor/we have stored into the ECU so that the mechanic doesn't have to open the source code.  </sub></center>

## 9. System Integrity
| ID | Description | Component | Verification | Status |
| :--- | :--- | :--- | :--- | :--- |
| **REQ-029** | The 10ms System Task shall reset (kick) the hardware Watchdog Timer. Failure to kick the watchdog within 20ms shall cause a hard system reset. | MCAL | HIL | ⬜ Not Started |
| **REQ-030** | Upon entering a FATAL software state (e.g., failed NVM read, RAM corruption), the software shall rigidly lock the PWM to 0% and execute an infinite while-loop (safe hang). | App | UT | ⬜ Not Started |

<center><sub>Why: I learned about cosmic rays and complete failure states, so it seems to be important to have a safe hang if one of these incidents happen and creating two saftey nets to catch them </sub></center>


