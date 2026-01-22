/*
                   LCD模块                STM32单片机				   
	 本程序使用的是模拟SPI接口驱动
     可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
	 
       VCC         接          3.3V/5V      //电源
       GND         接          GND          //电源地
       SDA/DIN     接          PB15         //液晶屏SPI总线数据写信号
       BLK         接          PB9          //液晶屏背光控制信号，如果不需要控制，接3.3V
       SCL/SCK     接          PB13         //液晶屏SPI总线时钟信号
       DC          接          PB10         //液晶屏数据/命令控制信号
       RES         接          PB12         //液晶屏复位控制信号
       CS          接          PB11         //液晶屏片选控制信号
*/

#ifndef __LCD_H
#define __LCD_H
#include "stm32f1xx_hal.h"
#include "lcd_dma.h"



//LCD重要参数集
typedef struct {
    uint16_t width;            //LCD 宽度
    uint16_t height;            //LCD 高度
    uint8_t xoffset;
    uint8_t yoffset;
} _lcd_dev;

//LCD参数
extern _lcd_dev lcddev;    //管理LCD重要参数

#define USE_HORIZONTAL     0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//定义LCD的尺寸
#define LCD_W 240
#define LCD_H 320




//画笔颜色
#define WHITE       0xFFFF
#define BLACK        0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED                0XFFE0
#define GBLUE                0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN            0XBC40 //棕色
#define BRRED            0XFC07 //棕红色
#define GRAY            0X8430 //灰色
#define GRAY0       0xEF7D
#define GRAY1       0x8410        //灰色1      00000 000000 00000
#define GRAY2       0x4208
//GUI颜色

#define DARKBLUE         0X01CF    //深蓝色
#define LIGHTBLUE         0X7D7C    //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色 

#define LIGHTGREEN        0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY                    0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

void LCD_Init(void);//初始化	
void LCD_Direction(uint8_t direction);

void LCD_Clear(uint16_t Color);

void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

void LCD_Draw(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd, uint16_t data);

void LCD_Update();

void LCD_ChangeColor(uint16_t * color);
#endif  
	 
