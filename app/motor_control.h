#ifndef APP_MOTOR_CONTROL_H
#define APP_MOTOR_CONTROL_H

void App_MotorControl_Init(void);

void App_MotorControl_SetTargetSpeed(float speed_rpm);

void App_MotorControl_Task(void);

#endif