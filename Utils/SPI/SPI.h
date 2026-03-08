#ifndef __SPI_H
#define __SPI_H

#include "stm32f1xx_hal.h"
void SPI_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
uint8_t SPI_SwapByte(uint8_t ByteSend);

#endif
