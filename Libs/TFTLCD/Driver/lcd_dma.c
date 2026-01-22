//
// Created by pc on 2026/1/22.
//

#include "lcd_dma.h"

#define LCD_PageNum 8

uint16_t LCD_WindowData[LCD_H / LCD_PageNum][LCD_W] = {0};
uint8_t LCD_Page = 0;

void LCD_DMAInit() {

}

void LCD_SetData2Dma(uint16_t x, uint16_t y, uint16_t color) {
    //  每个page的个数
    static uint16_t n = LCD_H / LCD_PageNum;



    LCD_Page = y / n;
    y = y % n;

    LCD_WindowData[y][x] = color;
}
