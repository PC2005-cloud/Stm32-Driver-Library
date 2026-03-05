//
// Created by pc on 2026/2/4.
//

#ifndef STM32_DRIVER_LIBRARY_PWM_H
#define STM32_DRIVER_LIBRARY_PWM_H

#include "stm32f1xx_hal.h"


// pwm引脚枚举（只是索引）
enum PWMPin {
    PWM_A0,  // 0
    PWM_A1,  // 1
    PWM_A2,  // 2
    PWM_A3,  // 3
    PWM_A6,  // 4
    PWM_A7,  // 5
    PWM_B0,  // 6
    PWM_B1,  // 7
    PWM_B6,  // 8
    PWM_B7,  // 9
    PWM_B8,  // 10
    PWM_B9,  // 11
    PIN_COUNT
};


void PWM_Init(enum PWMPin ePin, uint16_t prescaler, uint16_t period);

void PWM_Init_TIM(TIM_TypeDef *tim, uint16_t prescaler, uint16_t period);

void PWM_Set_COMPARE(enum PWMPin ePin, uint32_t compare);

#endif //STM32_DRIVER_LIBRARY_PWM_H
