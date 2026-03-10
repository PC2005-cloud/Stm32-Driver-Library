//
// Created by pc on 2026/3/10.
//

#ifndef STM32_DRIVER_LIBRARY_BSP_GPIO_H
#define STM32_DRIVER_LIBRARY_BSP_GPIO_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"
#define True true
#define False false

void GPIO_Init(GPIO_TypeDef *GPIOx, uint32_t pin, bool isOutOrIn);
#endif //STM32_DRIVER_LIBRARY_BSP_GPIO_H
