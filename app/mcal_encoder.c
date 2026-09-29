#include "hal_encoder.h"
#include <stdint.h>
#include "stm32g474xx.h"


void Encoder_HardwareInit(void){

    RCC->APB1ENR1 |= (1U << 0); //This is timer 2

    TIM2->SMCR = 3U;

    TIM2->CR1 |= (1U << 0);

}

int16_t Encoder_GetSpeed(void){

    return (int16_t)(TIM2->CNT);

}