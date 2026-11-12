#include "MockHalAndServices.h"

// Static variable to hold the state during tests
static float last_duty_cycle = -999.0f;

// Called by CppUTest setup() before every test
void MockPWM_Init(void) {
    last_duty_cycle = 0.0f;
}

// Called by CppUTest assertions to check the result
float MockPWM_GetLastDutyCycle(void) {
    return last_duty_cycle;
}

// C-linkage so your application C code can link to it during testing
extern "C" {
    void PWM_SetDutyCycle(float duty_cycle_percent) {
        last_duty_cycle = duty_cycle_percent;
    }
}