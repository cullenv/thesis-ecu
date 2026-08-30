#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void ADC_Init(void);

void ADC_CurrentRead(uint16_t *value); // Since current will most likely be in decimal format we can just assume 4500 read is 4.5 Amps or vice versa however our thing reads

#endif // HAL_ADC_H