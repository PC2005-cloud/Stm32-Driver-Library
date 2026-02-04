//
// Created by pc on 2026/2/4.
//

#include "PWM.h"

static TIM_HandleTypeDef htim2;
static TIM_HandleTypeDef htim3;
static TIM_HandleTypeDef htim4;

static void PWM_Init(TIM_HandleTypeDef *htim,
                     TIM_TypeDef *tim, uint32_t channel,
                     GPIO_TypeDef  *GPIOx, uint32_t pin,
                     uint16_t  prescaler, uint16_t  period) {
    // 1. 启用相关外设时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();


    htim->Instance = tim;
    htim->Init.Prescaler = prescaler - 1;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = period - 1;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(htim);

    HAL_TIM_PWM_Init(htim);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

    HAL_TIM_PWM_Start(htim, channel);
}


void PWM_Init_TIM2_1CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim2, TIM2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_0, prescaler, period);
}
void PWM_Init_TIM2_2CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim2, TIM2, TIM_CHANNEL_2, GPIOA, GPIO_PIN_1, prescaler, period);
}
void PWM_Init_TIM2_3CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim2, TIM2, TIM_CHANNEL_3, GPIOA, GPIO_PIN_2, prescaler, period);
}
void PWM_Init_TIM2_4CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim2, TIM2, TIM_CHANNEL_4, GPIOA, GPIO_PIN_3, prescaler, period);
}

void PWM_Init_TIM3_1CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim3, TIM3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_6, prescaler, period);
}
void PWM_Init_TIM3_2CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim3, TIM3, TIM_CHANNEL_2, GPIOA, GPIO_PIN_7, prescaler, period);
}
void PWM_Init_TIM3_3CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim3, TIM3, TIM_CHANNEL_3, GPIOB, GPIO_PIN_0, prescaler, period);
}
void PWM_Init_TIM3_4CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim3, TIM3, TIM_CHANNEL_4, GPIOB, GPIO_PIN_1, prescaler, period);
}

void PWM_Init_TIM4_1CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim4, TIM4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_6, prescaler, period);
}
void PWM_Init_TIM4_2CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim4, TIM4, TIM_CHANNEL_2, GPIOB, GPIO_PIN_7, prescaler, period);
}
void PWM_Init_TIM4_3CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim4, TIM4, TIM_CHANNEL_3, GPIOB, GPIO_PIN_8, prescaler, period);
}
void PWM_Init_TIM4_4CH(uint16_t prescaler, uint16_t period) {
    PWM_Init(&htim4, TIM4, TIM_CHANNEL_4, GPIOB, GPIO_PIN_9, prescaler, period);
}

void PWM_TIM2_Init(uint16_t  prescaler, uint16_t  period) {
    PWM_Init_TIM2_1CH(prescaler, period);
    PWM_Init_TIM2_2CH(prescaler, period);
    PWM_Init_TIM2_3CH(prescaler, period);
    PWM_Init_TIM2_4CH(prescaler, period);
}
void PWM_TIM3_Init(uint16_t  prescaler, uint16_t  period) {
    PWM_Init_TIM3_1CH(prescaler, period);
    PWM_Init_TIM3_2CH(prescaler, period);
    PWM_Init_TIM3_3CH(prescaler, period);
    PWM_Init_TIM3_4CH(prescaler, period);
}
void PWM_TIM4_Init(uint16_t  prescaler, uint16_t  period) {
    PWM_Init_TIM4_1CH(prescaler, period);
    PWM_Init_TIM4_2CH(prescaler, period);
    PWM_Init_TIM4_3CH(prescaler, period);
    PWM_Init_TIM4_4CH(prescaler, period);
}

void PWM_Set_COMPARE(TIM_TypeDef *tim, uint32_t channel, uint32_t compare) {
    if (tim == TIM2) {
        __HAL_TIM_SET_COMPARE(&htim2, channel, compare);
    } else if (tim == TIM3) {
        __HAL_TIM_SET_COMPARE(&htim3, channel, compare);
    } else if ( tim == TIM4) {
        __HAL_TIM_SET_COMPARE(&htim4, channel, compare);
    }
}