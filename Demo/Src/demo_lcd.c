//
// Created by pc on 2026/1/22.
//

#include "demo_lcd.h"
#include "lcd_str.h"
#include "lcd_graphics.h"
#include "picture.h"
#include "lcd_cmd.h"

void demo01() {

    LCD_ShowChar(0, 0, 'A', 0x1234, LCD1608);

    LCD_ShowString(0, 20,  "开心乐儿哈Hello World",0x1234, LCD1206);
    LCD_ShowDouble(0, 100,  -2.36, 5, 6,0x1234, LCD1206);

    LCD_Picture(0, 200, 100, 100, (uint16_t *) gImage_1);//图片显示

}

void demo02() {
    LCD_Rectangle(100, 100, 300, 300, 0x1234);
    LCD_Line(220, 220, 0, 0, 0x0000);
    LCD_Circle(120, 120, 5, 5, 0x6606);
    LCD_Triangle(10, 10, 200, 200, 50, 120, 0xFF00);
    LCD_Fill_Triangle(10, 320, 40, 280, 200, 319, 0x07FB);
}

void demo03() {
    LCD_ShowChar(0, 0, 'A', 0x1234, LCD1608);
    LCD_ShowString(0, 20,  "Hello World",0x1234, LCD1608);
    LCD_ShowNum(220, 280, 123456789, 10, 0x0000, LCD1608);
}

void demo04() {
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

void demo_lcd(int n) {
    LCD_Init();
    switch (n) {
        case 1:
            demo01();
            break;
        case 2:
            demo02();
            break;
        default:
            break;

    }
}

