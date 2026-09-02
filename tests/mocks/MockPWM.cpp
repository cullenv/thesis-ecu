#include "CppUTestExt/MockSupport.h"

// We must tell the C++ compiler that these headers are written in standard C
extern "C" {
    #include "hal/pwm.h"
}

void PWM_Init(void) {
    mock().actualCall("PWM_Init");
}

void PWM_SetDutyCycle(uint8_t duty_percent) {
    mock().actualCall("PWM_SetDutyCycle")
          .withParameter("duty_percent", duty_percent);
}

void PWM_EmergencyStop(void) {
    mock().actualCall("PWM_EmergencyStop");
}