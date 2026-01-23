//
// Created by pc on 2026/1/23.
//

#ifndef TT_WS2812_H
#define TT_WS2812_H
#include "stm32f1xx_hal.h"



void WS2812_Init();
void WS2812_SetColor(uint16_t y, uint16_t x, uint32_t color);

void WS2812_Update();

#endif //TT_WS2812_H
