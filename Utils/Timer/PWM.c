//
// Created by pc on 2026/2/4.
//

#include "PWM.h"

// pwm配置结构体（时钟，通道，GPIOx,pin）
typedef struct {
    TIM_HandleTypeDef *htim;
    TIM_TypeDef *tim;
    uint32_t channel;
    GPIO_TypeDef *GPIOx;
    uint16_t pin;
} PWM_Config;

static TIM_HandleTypeDef htim2;
static TIM_HandleTypeDef htim3;
static TIM_HandleTypeDef htim4;

// 配置表（用枚举索引访问）
static const PWM_Config pwm_configs[PIN_COUNT] = {
        [PWM_A0] = {&htim2, TIM2, TIM_CHANNEL_1, GPIOA, GPIO_PIN_0},
        [PWM_A1] = {&htim2, TIM2, TIM_CHANNEL_2, GPIOA, GPIO_PIN_1},
        [PWM_A2] = {&htim2, TIM2, TIM_CHANNEL_3, GPIOA, GPIO_PIN_2},
        [PWM_A3] = {&htim2, TIM2, TIM_CHANNEL_4, GPIOA, GPIO_PIN_3},

        [PWM_A6] = {&htim3, TIM3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_6},
        [PWM_A7] = {&htim3, TIM3, TIM_CHANNEL_2, GPIOA, GPIO_PIN_7},
        [PWM_B0] = {&htim3, TIM3, TIM_CHANNEL_3, GPIOB, GPIO_PIN_0},
        [PWM_B1] = {&htim3, TIM3, TIM_CHANNEL_4, GPIOB, GPIO_PIN_1},

        [PWM_B6] = {&htim4, TIM4, TIM_CHANNEL_1, GPIOB, GPIO_PIN_6},
        [PWM_B7] = {&htim4, TIM4, TIM_CHANNEL_2, GPIOB, GPIO_PIN_7},
        [PWM_B8] = {&htim4, TIM4, TIM_CHANNEL_3, GPIOB, GPIO_PIN_8},
        [PWM_B9] = {&htim4, TIM4, TIM_CHANNEL_4, GPIOB, GPIO_PIN_9}
};



void PWM_Init(enum PWMPin ePin, uint16_t prescaler, uint16_t period) {
    TIM_HandleTypeDef *htim = pwm_configs[ePin].htim;
    TIM_TypeDef  *tim = pwm_configs[ePin].tim;
    uint32_t channel = pwm_configs[ePin].channel;
    GPIO_TypeDef *GPIOx = pwm_configs[ePin].GPIOx;
    uint16_t pin = pwm_configs[ePin].pin;

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

void PWM_Init_TIM(TIM_TypeDef *tim, uint16_t prescaler, uint16_t period) {
    if (tim == TIM2) {
        PWM_Init(PWM_A0, prescaler, period);
        PWM_Init(PWM_A1, prescaler, period);
        PWM_Init(PWM_A2, prescaler, period);
        PWM_Init(PWM_A3, prescaler, period);
    } else if (tim == TIM3) {
        PWM_Init(PWM_A6, prescaler, period);
        PWM_Init(PWM_A7, prescaler, period);
        PWM_Init(PWM_B6, prescaler, period);
        PWM_Init(PWM_B7, prescaler, period);
    } else if (tim == TIM4) {
        PWM_Init(PWM_B0, prescaler, period);
        PWM_Init(PWM_B1, prescaler, period);
        PWM_Init(PWM_B8, prescaler, period);
        PWM_Init(PWM_B9, prescaler, period);
    }

}

void PWM_Set_COMPARE(enum PWMPin ePin, uint32_t compare) {
    __HAL_TIM_SET_COMPARE(pwm_configs[ePin].htim, pwm_configs[ePin].channel, compare);
}
