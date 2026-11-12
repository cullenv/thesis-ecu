#include "hal_pwm.h"
#include <stdint.h>
#include "stm32g4xx.h" 

#define PWM_PERIOD_TICKS 17000U 

void PWM_HardwareInit(void) {
   
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 

    
    TIM1->PSC = 0; 
    TIM1->ARR = PWM_PERIOD_TICKS - 1; // 16999 

    
    TIM1->CR1 |= TIM1_CR1_CEN; 
}

void PWM_SetDutyCycle(float duty_cycle_percent){
    if (duty_cycle_percent > 100.0f){
        duty_cycle_percent = 100.0f;
    } else if ( duty_cycle_percent < 0.0f ) {
        duty_cycle_percent = 0.0f;
    }

    TIM1->CCR1 = (uint16_t)((duty_cycle_percent / 100.0f) * PWM_PERIOD_TICKS); 
}