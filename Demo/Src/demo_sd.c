//
// Created by pc on 2026/3/6.
//

#include "demo_sd.h"
#include "SPI.h"
#include "stm32f1xx_hal.h"
#include "OLED.h"
#include "SD.h"

#define CMD0    0x40  // 复位命令
#define CMD8    0x48    // 电压检测
#define ACMD41  0x60  // 初始化命令

void demo_sd01() {
    uint8_t r1;
    uint16_t retry;

    SPI_Init();
    OLED_Init();

    SPI_Stop();

    for(retry=0; retry<10; retry++) {
        SPI_SwapByte(0xFF);
    }

    r1 = SD_SendCommand(CMD0, 0, 0x95);

    OLED_Clear();
    OLED_ShowNum(0, 0, r1, 5, OLED_8X16);
    OLED_Update();


    r1 = SD_SendCommand(CMD8, 0x1AA, 0x87);
    OLED_ShowNum(0, 16, r1, 5, OLED_8X16);
    OLED_Update();

    for(retry=0; retry<2000; retry++) {
        SD_SendCommand(55, 0x00000000, 0x01);
        r1 = SD_SendCommand(ACMD41, 0x40000000, 0x01);
        OLED_ShowNum(0, 32, r1, 5, OLED_8X16);
        OLED_Update();
        HAL_Delay(1);
        if(r1 == 0x00) break;
    }

    OLED_ShowNum(0, 48, retry, 5, OLED_8X16);
    OLED_Update();







}

void demo_sd() {
    demo_sd01();

}