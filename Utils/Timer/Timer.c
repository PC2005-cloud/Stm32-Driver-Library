//
// Created by pc on 2025/12/21.
//

#include "Timer.h"
#include "USART.h"


static TIM_HandleTypeDef htim2;
static TIM_HandleTypeDef htim3;
static TIM_HandleTypeDef htim4;



static struct Timer_Config timer_configs[3] = {
        {TIM2, TIM2_IRQn, &htim2, 0},
        {TIM3, TIM3_IRQn, &htim3, 0},
        {TIM4, TIM4_IRQn, &htim4, 0}
};




// 通过TIM_TypeDef获取TIM_HandleTypeDef
// 通过TIM_TypeDef获取IRQn_Type
struct Timer_Config *Timer_GetConfig(TIM_TypeDef *tim) {
    if (tim == TIM2) {
        return &timer_configs[0];
    }  else if (tim == TIM3) {
        return &timer_configs[1];
    } else if (tim == TIM4) {
        return &timer_configs[2];
    }
}



void Timer_Init(TIM_TypeDef *tim, uint32_t prescaler, uint32_t period) {
    struct Timer_Config *timer_config = Timer_GetConfig(tim);
    TIM_HandleTypeDef *htim = timer_config->htim;
    IRQn_Type IRQ = timer_config->irq;

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

    /* 4. 配置中断 */
    HAL_NVIC_SetPriority(IRQ, 3, 2);
    HAL_NVIC_EnableIRQ(IRQ);


}

// 开启计时器
void Timer_Start(TIM_TypeDef *tim, uint16_t n) {
    struct Timer_Config *config = Timer_GetConfig(tim);
    config->count +=  n;
    TIM_HandleTypeDef *htim = config->htim;
    HAL_TIM_Base_Start_IT(htim);
}

// 获取计时器值
uint16_t Timer_Get_Value(TIM_TypeDef *tim) {
    TIM_HandleTypeDef *htim = Timer_GetConfig(tim)->htim;
    return __HAL_TIM_GET_COUNTER(htim);
}

// 暂停计时器
void Timer_Pause(TIM_TypeDef *tim) {
    TIM_HandleTypeDef *htim = Timer_GetConfig(tim)->htim;
    HAL_TIM_Base_Stop_IT(htim);
}

// 重置计时器
void Timer_Reset(TIM_TypeDef *tim) {
    TIM_HandleTypeDef *htim = Timer_GetConfig(tim)->htim;
    __HAL_TIM_SET_COUNTER(htim, 0);
    HAL_TIM_Base_Stop_IT(htim);
}


static void Timer_DecrementAndReset(struct Timer_Config *timer) {
    if (timer == NULL) return;

    timer->count--;

    if (timer->count == 0) {
        Timer_Reset(timer->tim);
    }
}


void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
    Timer_DecrementAndReset(&timer_configs[0]);
}

void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim3);
    Timer_DecrementAndReset(&timer_configs[1]);
}

void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim4);
    Timer_DecrementAndReset(&timer_configs[2]);
}

/* 定时器更新中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) {
        Timer_Interrupt_2();
    } else if (htim == &htim3) {
        Timer_Interrupt_3();
    } else if (htim == &htim4) {
        Timer_Interrupt_4();
    }
}

// 中断函数
__weak void Timer_Interrupt_2(void) {
    USART1_Printf("Timer_Interrupt_2\r\n");
}

__weak void Timer_Interrupt_3(void) {
    USART1_Printf("Timer_Interrupt_3\r\n");
}

__weak void Timer_Interrupt_4(void) {
    USART1_Printf("Timer_Interrupt_4\r\n");
}
