#ifndef MOCK_STM32G4XX_H
#define MOCK_STM32G4XX_H
#include <stdint.h>

/* Mock the RCC Register Struct */
typedef struct {
    uint32_t APB2ENR;
    uint32_t APB1ENR;
} RCC_TypeDef;

/* Mock the TIM Register Struct */
typedef struct {
    uint32_t CR1;
    uint32_t PSC;
    uint32_t ARR;
    uint32_t CCR1;
    uint32_t SMCR;
    uint32_t CNT;
} TIM_TypeDef;

/* Define memory-mapped pointers (extern so tests can inspect them) */
extern RCC_TypeDef MockRCC;
extern TIM_TypeDef MockTIM1;
extern TIM_TypeDef MockTIM2;

#define RCC  ((RCC_TypeDef *)&MockRCC)
#define TIM1 ((TIM_TypeDef *)&MockTIM1)
#define TIM2 ((TIM_TypeDef *)&MockTIM2)

/* Define the bit flags used in MCAL */
#define RCC_APB2ENR_TIM1EN (1U << 11)
#define TIM1_CR1_CEN       (1U << 0)

#endif