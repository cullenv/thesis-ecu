#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "hal/adc.h"
}

void ADC_Init(void) {
    mock().actualCall("ADC_Init");
}

void ADC_CurrentRead(uint16_t *value) {
    mock().actualCall("ADC_CurrentRead")
          .withOutputParameter("value", value);
}