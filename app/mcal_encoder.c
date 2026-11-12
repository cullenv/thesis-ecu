#include "hal_encoder.h"
#include <stdint.h>
#include "stm32g4xx.h"

void Encoder_HardwareInit(void) {
    RCC->APB1ENR |= (1U << 0);
}

float Encoder_GetSpeed(void) {
    return 0.0f; 
}