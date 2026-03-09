//
// Created by pc on 2026/3/8.
//

#ifndef STM32_DRIVER_LIBRARY_DOG_H
#define STM32_DRIVER_LIBRARY_DOG_H
#include "stm32f1xx_hal.h"

#define Dog_LegFL  PWM_A1
#define Dog_LegBL  PWM_A0
#define Dog_LegFR  PWM_A3
#define Dog_LegBR  PWM_A2
#define Dog_Tail  PWM_A6

void Dog_Init();

// 测试引脚顺序
void Dog_Test();


void Dog_Walk(uint16_t steps, uint32_t delay_ms, uint16_t degree); // 行走

void Dog_Turn(uint16_t steps, uint32_t delay_ms, uint16_t degree); // 旋转
void Dog_ForwardSync(uint8_t degree);   // 同步前进
void Dog_BackwardSync(uint8_t degree);  // 同步后退
void Dog_TailMove(uint8_t  from, uint8_t  to, uint32_t delay_ms); // 尾巴
void Dog_MoveTrot(uint8_t  degree); // 4腿同时运动（前后同侧）
void Dog_MovePace(uint8_t  degree); // 4腿同时运动（前后不同侧）



#endif //STM32_DRIVER_LIBRARY_DOG_H
