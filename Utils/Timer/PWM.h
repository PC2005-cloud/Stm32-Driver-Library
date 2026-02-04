//
// Created by pc on 2026/2/4.
//

#ifndef STM32_DRIVER_LIBRARY_PWM_H
#define STM32_DRIVER_LIBRARY_PWM_H
#include "stm32f1xx_hal.h"

void PWM_TIM2_Init(uint16_t  prescaler, uint16_t  period);
void PWM_TIM3_Init(uint16_t  prescaler, uint16_t  period);
void PWM_TIM4_Init(uint16_t  prescaler, uint16_t  period);

void PWM_Init_TIM2_1CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM2_2CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM2_3CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM2_4CH(uint16_t  prescaler, uint16_t  period);

void PWM_Init_TIM3_1CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM3_2CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM3_3CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM3_4CH(uint16_t  prescaler, uint16_t  period);

void PWM_Init_TIM4_1CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM4_2CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM4_3CH(uint16_t  prescaler, uint16_t  period);
void PWM_Init_TIM4_4CH(uint16_t  prescaler, uint16_t  period);

void PWM_Set_COMPARE(TIM_TypeDef *tim, uint32_t channel, uint32_t compare);

#endif //STM32_DRIVER_LIBRARY_PWM_H
