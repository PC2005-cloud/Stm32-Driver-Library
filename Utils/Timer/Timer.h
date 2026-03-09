//
// Created by pc on 2025/12/21.
//

#ifndef GUARDIANELF_TIMER_H
#define GUARDIANELF_TIMER_H
#include "stm32f1xx_hal.h"

// 计时器数据结构体
struct Timer_Config {
    TIM_TypeDef *tim;
    IRQn_Type irq;
    TIM_HandleTypeDef *htim;
    uint32_t count;
};

// 定时器初始化
void Timer_Init(TIM_TypeDef *tim, uint32_t prescaler, uint32_t period);

// 获取定时器配置
struct Timer_Config *Timer_GetConfig(TIM_TypeDef *tim);

// 开启计时器
void Timer_Start(TIM_TypeDef *tim, uint16_t n);

// 获取计时器值
uint16_t Timer_Get_Value(TIM_TypeDef *tim);

// 暂停计时器
void Timer_Pause(TIM_TypeDef *tim);

// 重置计时器
void Timer_Reset(TIM_TypeDef *tim);

void Timer_Interrupt_2(void);
void Timer_Interrupt_3(void);
void Timer_Interrupt_4(void);

#endif //GUARDIANELF_TIMER_H
