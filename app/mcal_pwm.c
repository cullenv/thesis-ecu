#include "hal_pwm.h"
#include <stdint.h>
#include "stm32g474xx.h"

#define TIMER_MAX_TICKS 8000U

void PWM_HardwareInit(void) {

}

void PWM_SetDutyCycle(float duty_cycle_percent){

    if (duty_cycle_percent > 100.0f){
        duty_cycle_percent = 100.0f;
    } else if ( duty_cycle_percent < 0.0f ) {
        duty_cycle_percent = 0.0f;
    }

    TIM1->CCR1 = (uint16_t)((duty_cycle_percent/100.0f) * TIMER_MAX_TICKS); //dmmy_hardware_register will turn into the actual ardware register going straight to our mcu
    
}
