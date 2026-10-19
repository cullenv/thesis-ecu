#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdint.h>

// Remember your function prototypes here is where they are going to come into play
void PWM_Init(void);

void PWM_SetDutyCycle(uint8_t duty_percent);

void PWM_EmergencyStop(void);

#endif // HAL_PWM_Hd