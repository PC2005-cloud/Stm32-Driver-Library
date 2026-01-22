//
// Created by pc on 2026/1/21.
//

#include "lcd_str.h"
#include "lcd_cmd.h"
#include "font.h"
#include "lcd_graphics.h"
#include <string.h>
#include <stdio.h>

void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t c, uint16_t color, uint8_t font) {
    uint8_t temp;
    uint8_t pos, t;

    c = c - ' ';//得到偏移后的值
    LCD_SetWindows(x, y, x + font / 2 - 1, y + font - 1);//设置单个文字显示窗口
    for (pos = 0; pos < font; pos++) {
        if (font == LCD1206)temp = asc2_1206[c][pos];//调用1206字体
        else if (font == LCD1608) temp = asc2_1608[c][pos];         //调用1608字体
        else return;                                //没有的字库

        for (t = 0; t < font / 2; t++) {
            if (temp & 0x01)LCD_Point(x + t, y + pos, color);//画一个点
            temp >>= 1;
        }
    }
}

uint32_t mypow(uint8_t m, uint8_t n) {
    uint32_t result = 1;
    while (n--)result *= m;
    return result;
}

void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color, uint8_t size) {
    uint8_t t, temp;

    for (t = 0; t < len; t++) {
        temp = (num / mypow(10, len - t - 1)) % 10;
        LCD_ShowChar(x + (size / 2) * t, y, color, temp + '0', size);
    }
}

void LCD_ShowCharacter(uint16_t x, uint16_t y, uint8_t *str, uint16_t color, uint8_t size, uint8_t len) {
    uint8_t temp;
    uint16_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * size;        //得到字体一个字符对应点阵集所占的字节数
    int num = -1;
    //只定定义了16，12 ,24号字体，没有生名其他字体
    if (size == LCD1206) {
        while (1) {
            num++;
            if (strcmp(character1212[num].Index, "") == 0) break;

            if (strncmp(character1212[num].Index, (char *) str, len) == 0) break;
        }
    } else if (size == LCD1608) {
        while (1) {
            num++;

            char *s = character1616[num].Index;
            if (strncmp(character1616[num].Index, "", 1) == 0) break;
            if (strncmp(character1616[num].Index, (char *) str, len) == 0) break;
        }
    } else if (size == LCD2412) {
        while (1) {
            num++;
            if (strcmp(character2424[num].Index, "") == 0) break;

            if (strncmp(character2424[num].Index, (char *) str, len) == 0) break;
        }
    }


    for (uint8_t t = 0; t < csize; t++) {

        //只定定义了16，12 ,24号字体，没有生名其他字体
        if (size == LCD1206) {
            temp = character1212[num].Data[t];
        }        //调用1206字体
        else if (size == LCD1608) {
            temp = character1616[num].Data[t];
        }   //调用1608字体
        else if (size == LCD2412) {
            temp = character2424[num].Data[t];
        }   //调用2412字体
        else return;                                //没有的字库
        for (uint8_t t1 = 0; t1 < 8; t1++) {
            if (temp & 0x80)LCD_Point(x, y, color);
            temp <<= 1;
            y++;
            if ((y - y0) == size) {
                y = y0;
                x++;
                break;
            }
        }
    }
}


void LCD_ShowString(uint16_t x, uint16_t y, uint8_t *str, uint16_t color, uint8_t font) {
    while (*str != '\0') {
        uint8_t char_len;
        if ((*str & 0x80) == 0x00) {
            // ASCII字符 (1字节)
            char_len = 1;
        } else if ((*str & 0xE0) == 0xC0) {
            // 2字节UTF-8
            char_len = 2;
        } else if ((*str & 0xF0) == 0xE0) {
            // 3字节UTF-8（通常是中文）
            char_len = 3;
        } else if ((*str & 0xF8) == 0xF0) {
            // 4字节UTF-8
            char_len = 4;
        } else {
            return;
        }

        if (char_len == 1) {
            LCD_ShowChar(x, y, *str, color, font);
            x += font / 2;
        } else {
            LCD_ShowCharacter(x, y, str, color, font, char_len);
            x += font;
        }

        str += char_len;

    }

}

void LCD_ShowDouble(uint16_t x, uint16_t y, double num, uint8_t zLen, uint8_t fLen, uint16_t color, uint8_t font) {
    char formatStr[16];

    // 构建格式字符串：%[总宽度].[小数位数]f
    // 例如：zLen=5, fLen=2 → "%5.2f"
    snprintf(formatStr, sizeof(formatStr), "%%0%d.%df", zLen + fLen + 1 + (num < 0), fLen);

    // 然后使用 formatStr 格式化显示
    // 示例代码（需要根据实际LCD驱动函数调整）：
    char buffer[32];

    snprintf(buffer, sizeof(buffer), formatStr, num);
    LCD_ShowString(x, y, buffer, color, font);
}