// tests/test_motor_control.cpp
#include "CppUTest/TestHarness.h"
#include "mocks/MockHalAndServices.h"

extern "C" {
#include "motor_control.h"
}

TEST_GROUP(MotorControlGroup) {
    void setup() override {
        MockPWM_Init();
        MockDiag_Init();
        MockEncoder_Init(); // Ensure encoder starts at 0 RPM for every test
        App_MotorControl_Init();
    }

    void teardown() override {}
};

TEST(MotorControlGroup, NominalTargetSpeedCommandsPositivePWM) {
    App_MotorControl_SetTargetSpeed(50.0f);
    App_MotorControl_Task();

    float pwm = MockPWM_GetLastDutyCycle();
    CHECK_TRUE(pwm > 0.0f);
    CHECK_TRUE(pwm <= 95.0f); // Updated to 95%
}
 
TEST(MotorControlGroup, HighTargetSaturatesAtUpperLimit) {
    App_MotorControl_SetTargetSpeed(5000.0f);
    for (int i = 0; i < 200; i++) {
        App_MotorControl_Task();
    }
    // Updated assertion to strictly test REQ-005
    DOUBLES_EQUAL(95.0f, MockPWM_GetLastDutyCycle(), 0.01f); 
}

TEST(MotorControlGroup, NegativeTargetSaturatesAtLowerLimit) {
    App_MotorControl_SetTargetSpeed(-5000.0f);
    for (int i = 0; i < 200; i++) {
        App_MotorControl_Task();
    }
    // Updated assertion to strictly test REQ-005
    DOUBLES_EQUAL(-95.0f, MockPWM_GetLastDutyCycle(), 0.01f);
}

TEST(MotorControlGroup, EncoderLossFaultForcesZeroPWM) {
    App_MotorControl_SetTargetSpeed(500.0f);
    App_MotorControl_Task();
    CHECK_TRUE(MockPWM_GetLastDutyCycle() > 0.0f);

    MockDiag_SetFaultStatus(DTC_ENCODER_LOSS, STATUS_ACTIVE);
    App_MotorControl_Task();

    DOUBLES_EQUAL(0.0f, MockPWM_GetLastDutyCycle(), 0.001f);
}