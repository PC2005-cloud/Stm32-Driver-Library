//
// Created by pc on 2026/1/22.
//

#ifndef T_LCD_DMA_H
#define T_LCD_DMA_H

#include "stm32f1xx_hal.h"
#include "lcd_cmd.h"



void LCD_DMAInit();

void LCD_SetData2Dma(uint16_t x, uint16_t y, uint16_t color);

#endif //T_LCD_DMA_H
