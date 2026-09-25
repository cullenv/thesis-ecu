#ifndef APP_HAL_PWM_H
#define APP_HAL_PWM_H

void PWM_SetDutyCycle(float duty_cycle_percent);

void PWM_HardwareInit(void); // Tell the hardware to wake up

#endif // APP_HAL_PWM_H