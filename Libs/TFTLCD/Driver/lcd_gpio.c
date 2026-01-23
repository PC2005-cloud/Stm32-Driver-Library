//
// Created by pc on 2026/1/21.
//

#include "lcd_gpio.h"
#include "Delay.h"
#include "SPI1.h"

// 引脚定义
#define LCD_Port GPIOB
#define HAL_RCC_GPIOx_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_DC_Pin GPIO_PIN_4
#define LCD_RST_Pin GPIO_PIN_5
#define LCD_BLK_Pin GPIO_PIN_3

void LCD_GPIOInit(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0}; // 初始化结构体清零，HAL库推荐写法

    // 1. 使能GPIOB时钟（HAL库标准宏）
    HAL_RCC_GPIOx_CLK_ENABLE();

    // 2. 配置PB9/10/11/12/13/15为推挽输出模式（与原代码一致）
    GPIO_InitStructure.Pin = LCD_RST_Pin | LCD_DC_Pin | LCD_BLK_Pin;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;  // 对应原GPIO_Speed_50MHz
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;     // 推挽输出（对应原GPIO_Mode_Out_PP）
    GPIO_InitStructure.Pull = GPIO_NOPULL;             // 无上下拉（原标准库默认）
    HAL_GPIO_Init(LCD_Port, &GPIO_InitStructure);

    // 3. 将推挽输出引脚置高（替换原GPIO_SetBits）
    HAL_GPIO_WritePin(LCD_Port, LCD_RST_Pin | LCD_DC_Pin | LCD_BLK_Pin, GPIO_PIN_SET);

}

void LCD_Close() {
    LCD_Port->BRR = LCD_BLK_Pin;  // 直接复位寄存器，更快
}

void LCD_Open() {
    LCD_Port->BSRR = LCD_BLK_Pin;  // 置位寄存器
}

void LCD_DataMode() {
    LCD_Port->BSRR = LCD_DC_Pin;  // DC=1
}

void LCD_CmdMode() {
    LCD_Port->BRR = LCD_DC_Pin;  // DC=0
}

void LCD_RESET(void) {
    HAL_GPIO_WritePin(LCD_Port, LCD_RST_Pin, (GPIO_PinState) 0);
    Delay_ms(20);
    HAL_GPIO_WritePin(LCD_Port, LCD_RST_Pin, (GPIO_PinState) 1);
    Delay_ms(20);
}

void LCD_WriteCmd(uint8_t cmd) {
    LCD_CmdMode();
    SPI1_SwapByte1(cmd);
}

void LCD_WriteData8(uint8_t data) {
    LCD_DataMode();
    SPI1_SwapByte1(data);
}


void Lcd_WriteData16(uint16_t Data) {
    LCD_DataMode();
    SPI1_SwapByte2(Data);
}

void LCD_WriteReg(uint8_t LCD_Reg, uint8_t LCD_RegValue) {
    LCD_WriteCmd(LCD_Reg);
    LCD_WriteData8(LCD_RegValue);
}


