//
// Created by pc on 2026/1/22.
//

#ifndef STM32_DRIVER_LIBRARY_LCD_BOX_H
#define STM32_DRIVER_LIBRARY_LCD_BOX_H
#include "stm32f1xx_hal.h"

// Box组件结构体
typedef struct {
    uint16_t typeId;

    // 位置和尺寸
    uint16_t x;            // X坐标
    uint16_t y;            // Y坐标
    uint16_t width;        // 宽度（建议用width/height替代radius）
    uint16_t height;       // 高度
    uint16_t corner_radius; // 圆角半径（0表示直角）

    // 颜色
    uint16_t background;   // 背景色
    uint16_t border_color; // 边框颜色

    // 边框
    uint8_t border_width;  // 边框宽度（0表示无边框）
    uint16_t padding;      // 内边距（文字距离边框）
} LCD_Box;

void LCD_InitBox(LCD_Box *box);

void LCD_DrawBox(LCD_Box *box);

#endif //STM32_DRIVER_LIBRARY_LCD_BOX_H
