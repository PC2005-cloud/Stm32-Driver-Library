//
// Created by pc on 2026/3/10.
//

#ifndef STM32_DRIVER_LIBRARY_HCSR04_H
#define STM32_DRIVER_LIBRARY_HCSR04_H
#include "stm32f1xx_hal.h"

void HCSR04_Init();

uint16_t HCSR04_Measure();

#endif //STM32_DRIVER_LIBRARY_HCSR04_H
