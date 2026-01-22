#ifndef __SPI_H
#define __SPI_H

// 基本函数
void SPI1_Init(void);

void SPI1_Start(void);

void SPI1_Stop(void);

uint8_t SPI1_SwapByte(uint8_t ByteSend);

// 交换1个字节
void SPI1_SwapByte1(uint8_t ByteSend);

// 交换2个字节
void SPI1_SwapByte2(uint16_t ByteSend);

#endif
