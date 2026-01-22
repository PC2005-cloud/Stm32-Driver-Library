//
// Created by pc on 2026/1/21.
//

#ifndef T_LCD_STR_H
#define T_LCD_STR_H

#include "stm32f1xx_hal.h"

#define LCD1206 12
#define LCD1608 16
#define LCD2412 24

void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint8_t font);

void LCD_ShowString(uint16_t x, uint16_t y, uint8_t* str, uint16_t color, uint8_t font);

void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color, uint8_t size);

void LCD_ShowDouble(uint16_t x, uint16_t y, double num, uint8_t zLen, uint8_t fLen, uint16_t color, uint8_t font);
#endif //T_LCD_STR_H
