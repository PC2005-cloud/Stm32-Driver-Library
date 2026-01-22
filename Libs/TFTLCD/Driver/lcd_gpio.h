//
// Created by pc on 2026/1/21.
//

#ifndef T_LCD_GPIO_H
#define T_LCD_GPIO_H
#include "stm32f1xx_hal.h"


void LCD_GPIOInit(void);

void LCD_Close();

void LCD_Open();

void LCD_DataMode();

void LCD_CmdMode();

void LCD_RESET(void);

void LCD_WriteCmd(uint8_t data);

void LCD_WriteData8(uint8_t data);

void Lcd_WriteData16(uint16_t Data);

void LCD_WriteReg(uint8_t LCD_Reg, uint8_t LCD_RegValue);

#endif //T_LCD_GPIO_H
