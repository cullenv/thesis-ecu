#ifndef HAL_ENCODER_H
#define HAL_ENCODER_H

#include <stdint.h>

void Encoder_Init(void);

void Encoder_GetCount(int32_t *count);


#endif // HAL_ENCODER_H