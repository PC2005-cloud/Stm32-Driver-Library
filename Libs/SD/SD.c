//
// Created by pc on 2026/3/6.
//

#include "SD.h"
#include "SPI.h"


#define CMD0    0x40  // 复位命令
#define CMD8    0x48  // 电压检测
#define ACMD41  0x60  // 初始化命令
uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc) {
    uint8_t r1;

    SPI_Start();
    SPI_SwapByte(cmd | 0x40);
    SPI_SwapByte((arg >> 24)  & 0xFF);
    SPI_SwapByte((arg >> 16)  & 0xFF);
    SPI_SwapByte((arg >> 8) & 0xFF);
    SPI_SwapByte(arg  & 0xFF);
    SPI_SwapByte(crc);

    for(int i=0; i<1000; i++) {
        r1 = SPI_SwapByte(0xFF);
        if((r1 & 0x80) == 0) break;
    }

    return r1;
}

uint8_t SD_Init(void) {
    uint8_t r1;
    uint16_t retry;

    // 发送74+时钟脉冲
    for(retry=0; retry<10; retry++) {
        SPI_SwapByte(0xFF);
    }

    // 进入SPI模式
    r1 = SD_SendCommand(CMD0, 0, 0x95);
    if(r1 != 0x01) return 1;  // 复位失败

    // 检测SD卡版本
    r1 = SD_SendCommand(CMD8, 0x1AA, 0x87);
    if(r1 != 0x01) return 2;  // 不支持CMD8

    // 初始化SD卡
    for(retry=0; retry<2000; retry++) {
        r1 = SD_SendCommand(ACMD41, 0x40000000, 0x01);
        if(r1 == 0x00) break;
        HAL_Delay(1);
    }
    if(retry >= 2000) return 3;  // 初始化超时

    return 0;  // 成功
}

