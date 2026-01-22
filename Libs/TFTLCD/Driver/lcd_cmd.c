#include "lcd_cmd.h"
#include "SPI1.h"
#include "lcd_gpio.h"



//默认为竖屏
_lcd_dev lcddev;

void LCD_Init(void) {
    SPI1_Init();
    LCD_GPIOInit();//LCD GPIO初始化
    LCD_RESET(); //LCD 复位
//************* ST7789初始化**********//
    LCD_WriteCmd(0x36);
    LCD_WriteData8(0x00);

    LCD_WriteCmd(0x3A);
    LCD_WriteData8(0x05);

    LCD_WriteCmd(0xB2);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x00);
    LCD_WriteData8(0x33);
    LCD_WriteData8(0x33);

    LCD_WriteCmd(0xB7);
    LCD_WriteData8(0x35);

    LCD_WriteCmd(0xBB);
    LCD_WriteData8(0x19);

    LCD_WriteCmd(0xC0);
    LCD_WriteData8(0x2C);

    LCD_WriteCmd(0xC2);
    LCD_WriteData8(0x01);

    LCD_WriteCmd(0xC3);
    LCD_WriteData8(0x12);

    LCD_WriteCmd(0xC4);
    LCD_WriteData8(0x20);

    LCD_WriteCmd(0xC6);
    LCD_WriteData8(0x0F);

    LCD_WriteCmd(0xD0);
    LCD_WriteData8(0xA4);
    LCD_WriteData8(0xA1);

    LCD_WriteCmd(0xE0);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2B);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x54);
    LCD_WriteData8(0x4C);
    LCD_WriteData8(0x18);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x0B);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x23);

    LCD_WriteCmd(0xE1);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2C);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x44);
    LCD_WriteData8(0x51);
    LCD_WriteData8(0x2F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x20);
    LCD_WriteData8(0x23);

    LCD_WriteCmd(0x21);

    LCD_WriteCmd(0x11);
    //Delay (120);

    LCD_WriteCmd(0x29);
    LCD_Direction(USE_HORIZONTAL);//设置LCD显示方向
    LCD_Open(); //点亮背光
    LCD_Clear(WHITE);//清全屏白色
}

void LCD_Direction(uint8_t direction) {
    switch (direction) {
        case 0:
            lcddev.width = LCD_W;
            lcddev.height = LCD_H;
            lcddev.xoffset = 0;
            lcddev.yoffset = 0;
            LCD_WriteReg(0x36, (1 << 3));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 1:
            lcddev.width = LCD_H;
            lcddev.height = LCD_W;
            lcddev.xoffset = 0;
            lcddev.yoffset = 0;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 5));//BGR==1,MY==1,MX==0,MV==1
            break;
        case 2:
            lcddev.width = LCD_W;
            lcddev.height = LCD_H;
            lcddev.xoffset = 0;
            lcddev.yoffset = 0;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 6) | (1 << 7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 3:
            lcddev.width = LCD_H;
            lcddev.height = LCD_W;
            lcddev.xoffset = 80;
            lcddev.yoffset = 0;
            LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 5));//BGR==1,MY==1,MX==0,MV==1
            break;
        default:
            break;
    }
}


void LCD_Clear(uint16_t Color) {
    LCD_Draw(0, 0, lcddev.width - 1, lcddev.height - 1, Color);
}


void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd) {
    LCD_WriteCmd(0x2A);
    LCD_WriteData8((xStar + lcddev.xoffset) >> 8);
    LCD_WriteData8(xStar + lcddev.xoffset);
    LCD_WriteData8((xEnd + lcddev.xoffset) >> 8);
    LCD_WriteData8(xEnd + lcddev.xoffset);

    LCD_WriteCmd(0x2B);
    LCD_WriteData8((yStar + lcddev.yoffset) >> 8);
    LCD_WriteData8(yStar + lcddev.yoffset);
    LCD_WriteData8((yEnd + lcddev.yoffset) >> 8);
    LCD_WriteData8(yEnd + lcddev.yoffset);

    LCD_WriteCmd(0x2C);
}


void LCD_Draw(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd,uint16_t color) {
    LCD_ChangeColor(&color);
    LCD_SetWindows(xStar, yStar, xEnd, yEnd);
    unsigned int i, m;
    LCD_DataMode();
    SPI1_Start();
    for (i = yStar; i < yEnd + 1; i++) {
        for (m = xStar; m < xEnd + 1; m++) {
            SPI1_SwapByte(color >> 8);
            SPI1_SwapByte(color);
        }
    }
    SPI1_Stop();
}

void LCD_Update() {
//    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
//    LCD_DataMode();
//    SPI_Start();
//    unsigned int i, m;
//    for (i = 0; i < lcddev.width + 1; i++) {
//        for (m = 0; m < lcddev.height + 1; m++) {
//            SPI_SwapByte( LCD_WindowData[m][i] >> 8);
//            SPI_SwapByte( LCD_WindowData[m][i]);
//        }
//    }
//    SPI_Stop();
}

// 零时辅助函数（修正颜色）
void LCD_ChangeColor(uint16_t * color) {
    *color = ~ *color;
}

