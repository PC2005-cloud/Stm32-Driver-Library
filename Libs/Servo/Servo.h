//
// Created by pc on 2026/2/28.
//

#ifndef STM32_DRIVER_LIBRARY_SERVO_H
#define STM32_DRIVER_LIBRARY_SERVO_H

#include "PWM.h"


void Servo_Init(TIM_TypeDef *tim);

// 360度舵机移动
void Servo360_Move(enum PWMPin ePin, int8_t speed);

// 180度舵机转动角度
void Servo180_Move(enum PWMPin ePin, uint8_t degree);

#endif //STM32_DRIVER_LIBRARY_SERVO_H

