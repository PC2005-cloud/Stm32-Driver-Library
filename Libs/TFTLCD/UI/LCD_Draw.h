//
// Created by pc on 2026/1/23.
//

#ifndef STM32_DRIVER_LIBRARY_LCD_DRAW_H
#define STM32_DRIVER_LIBRARY_LCD_DRAW_H
#include "LCD_Draw.h"
#include "stm32f1xx_hal.h"

//通用组件结构体
typedef struct LCD_Base{
    uint16_t typeId;
} LCD_Base;

void LCD_DrawComponent(LCD_Base * component);

#endif //STM32_DRIVER_LIBRARY_LCD_DRAW_H
