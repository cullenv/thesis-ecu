# Software Traceability Matrix

| Requirement ID | Description | Test Group / Name | Status |
|---|---|---|---|
| REQ-001 | The system shall operate a 1ms scheduler tick. | `TEST(Scheduler, OneMillisecondTick)` | 🔴 Unwritten |
| REQ-005 | The motor control PWM shall be strictly clamped between -95.0% and 95.0% duty cycle. | `TEST(MotorControlGroup, HighTargetSaturatesAtUpperLimit)`<br>`TEST(MotorControlGroup, NegativeTargetSaturatesAtLowerLimit)` | 🟢 Passing (UT) |
| REQ-006 | The ECU shall read the hardware quadrature encoder to calculate the motor speed in RPM every 1 ms. | `TEST(Encoder, CalculatedSpeed)` | 🔴 Unwritten |
| REQ-008 | The rate limiter shall restrict target speed changes to a maximum of 1000 RPM/sec. | `TEST(RampGroup, ...)` | 🟢 Passing (UT) |
| REQ-010 | The ECU shall receive Target Speed via CAN 0x100. | `TEST(CAN, ReceiveTargetSpeed)` | 🔴 Unwritten |
| REQ-011 | The ECU shall transmit current Motor Speed via CAN ID 0x101 (DLC 4, Big-Endian IEEE-754). | `TEST(ComManagerGroup, SendMotorSpeedSerializesFloatBigEndian)` | 🟢 Passing (UT) |
| REQ-015 | The motor control loop shall force a 0.0% PWM output and ignore CAN commands if the Encoder Loss fault is active. | `TEST(MotorControlGroup, EncoderLossFaultForcesZeroPWM)` | 🟢 Passing (UT) |
| REQ-016 | If ADC current > 5A for 10ms, trigger fault. | `TEST(Faults, OvercurrentTripsAt5Amps)` | 🔴 Unwritten |