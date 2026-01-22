//
// Created by pc on 2026/1/21.
//

#ifndef T_LCD_GRAPHICS_H
#define T_LCD_GRAPHICS_H
#include "stm32f1xx_hal.h"
#include <stdbool.h>


// 画点
void LCD_Point(uint16_t x, uint16_t y, uint16_t color);
// 画矩形
void LCD_Rectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
// 画线
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
// 画圆
void LCD_Circle(uint16_t xc, uint16_t yc, uint16_t c, uint16_t r, bool fill);
// 画三角形
void LCD_Triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
// 填充三角形
void LCD_Fill_Triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void LCD_Picture(uint16_t x, uint16_t y, uint16_t column, uint16_t row, uint16_t *pic);

#endif //T_LCD_GRAPHICS_H
