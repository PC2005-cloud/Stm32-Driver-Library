//
// Created by pc on 2026/3/5.
//

// 4足机器人工具文件

#ifndef STM32_DRIVER_LIBRARY_SPIDER4_H
#define STM32_DRIVER_LIBRARY_SPIDER4_H
#include "Servo.h"

//机器人腿与引脚对应枚举（前后/左右/腿脚）
#define Spider4_FL_Leg   PWM_A3
#define Spider4_FL_Foot  PWM_A6
#define Spider4_FR_Leg   PWM_B7
#define Spider4_FR_Foot  PWM_A1
#define Spider4_BL_Leg   PWM_A2
#define Spider4_BL_Foot  PWM_A0
#define Spider4_BR_Leg   PWM_B6
#define Spider4_BR_Foot  PWM_A7

void Spider4_Init();

// 测试引脚顺序
void Spider4_Test();

void Spider4_FootAll(uint8_t  degree);

void Spider4_LegAll(uint8_t  degree);

#endif //STM32_DRIVER_LIBRARY_SPIDER4_H
