//
// Created by pc on 2026/3/6.
//

#ifndef STM32_DRIVER_LIBRARY_SD_H
#define STM32_DRIVER_LIBRARY_SD_H
#include "stm32f1xx_hal.h"

uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc);

uint8_t SD_Init(void);
#endif //STM32_DRIVER_LIBRARY_SD_H
