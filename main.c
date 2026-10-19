
#include "com_manager.h"
#include <stdint.h>

//for testing purposes
void delay_ms(uint32_t ms) {
    // assuming ~170MHz clock 
    for (volatile uint32_t i = 0; i < ms * 10000; i++); 
}

int main(void) {
    // (In a full build, we would call MCU_Init() and CAN_HardwareInit() here)

    float test_speed_rpm = 1500.0f;

    while (1) {
        // Send the float to the CANable
        COM_SendMotorSpeed(test_speed_rpm);
        
        // Increment the speed so we can see dynamic data on the PC
        test_speed_rpm += 5.5f; 

        // Wait ~100ms before transmitting again
        delay_ms(100); 
    }
}
