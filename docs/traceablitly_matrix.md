# Software Traceability Matrix

| Requirement ID | Description | Test Group / Name | Status |
|---|---|---|---|
| REQ-001 | The system shall operate a 1ms scheduler tick. | `TEST(Scheduler, OneMillisecondTick)` | 🔴 Unwritten |
| REQ-016 | If ADC current > 5A for 10ms, trigger fault. | `TEST(Faults, OvercurrentTripsAt5Amps)` | 🔴 Unwritten |
| REQ-010 | The ECU shall receive Target Speed via CAN 0x100. | `TEST(CAN, ReceiveTargetSpeed)` | 🔴 Unwritten |
| REQ-006 | The ECU shall read the hardware quadrature encoder to calculate the motor speed in RPM every 1 ms. | `TEST(Encoder, CalculatedSpeed)` | 🔴 Unwritten |