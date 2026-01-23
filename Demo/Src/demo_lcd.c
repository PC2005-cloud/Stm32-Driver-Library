//
// Created by pc on 2026/1/22.
//

#include "demo_lcd.h"
#include "lcd_str.h"
#include "lcd_graphics.h"
#include "picture.h"
#include "lcd_cmd.h"
#include "LCD_Box.h"
#include "LCD_Draw.h"
#include "OLED.h"

static void demo01() {

    LCD_ShowChar(0, 0, 'A', 0x1234, LCD1608);

    LCD_ShowString(0, 20, "开心乐儿哈Hello World", 0x1234, LCD1206);
    LCD_ShowDouble(0, 100, -2.36, 5, 6, 0x1234, LCD1206);

    LCD_Picture(0, 200, 100, 100, (uint16_t *) gImage_1);//图片显示

}

static void demo02() {
    LCD_Rectangle(100, 100, 200, 200, 0x1234);
    LCD_RectangleWithRadius(20, 20, 80, 80, 20, 0x1234);
    LCD_RectangularBorder(200, 200, 250, 250, 5, 0x1234);
    LCD_RectangularBorderWithRadius(10, 10, 150, 150, 5, 20, 0x1234);
    LCD_Line(220, 220, 0, 0, 0x0000);
    LCD_Circle(120, 120, 50, 0x6606);
    LCD_Arc(40, 120, 1, 0x6606, 1, 2);
    LCD_CircleBorder(150, 50, 10, 2, 0x6606);
    LCD_CircleBorder(30, 250, 2, 100, 0x6606);
    LCD_CircleBorder(100, 250, 10, 10, 0x6606);
    LCD_Triangle(10, 10, 200, 200, 50, 120, 0xFF00);
    LCD_Fill_Triangle(10, 320, 40, 280, 200, 319, 0x07FB);
}

static void demo03() {
    LCD_ShowChar(0, 0, 'A', 0x1234, LCD1608);
    LCD_ShowString(0, 20, "Hello World", 0x1234, LCD1608);
    LCD_ShowNum(220, 280, 123456789, 10, 0x0000, LCD1608);
}



static void demo04() {
    LCD_Clear(0x0000);
    LCD_Clear(0xFFFF);
    LCD_Clear(0x1234);
    LCD_Clear(0xABCD);

    for (int y = 0; y < 320; y++) {
        for (int x = 0; x < 240; x++) {
            // 根据x位置计算颜色
            uint16_t color = x * 273;  // 273 = 65535/240
            LCD_Point(x, y, color);
        }
    }

}

static void demo05() {
    uint16_t x = 0;
    while (1) {
        LCD_Box box = {1, 20 + x, 20, 100, 100, 4, 0xCCCC, 0x000, 5, 10};
        LCD_InitBox(&box);
        LCD_DrawComponent(&box);

        LCD_Box box01 = {1, 20, 200, 100, 100, 10, 0xCCCC, 0x000, 5, 10};
        LCD_InitBox(&box01);
        LCD_DrawComponent(&box01);
    }
}

void demo_lcd() {
    OLED_Init();
    LCD_Init();
    demo05();
}

