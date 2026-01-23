// ws2812.c
#include "stm32f1xx_hal.h"  // 请根据实际使用的STM32系列调整头文件
#define Code0 30
#define Code1 60
#define CodeR 0

#define WS2812_W 4
#define WS2812_H 4

// 全局句柄定义
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch1_trig;

uint16_t WS2812_Data[WS2812_W * WS2812_H * 24 + 1] = {0};

// 初始化函数
void WS2812_Init(void) {
    // 1. 启用相关外设时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();

    // 2. DMA 初始化
    hdma_tim3_ch1_trig.Instance = DMA1_Channel6;
    hdma_tim3_ch1_trig.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim3_ch1_trig.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim3_ch1_trig.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim3_ch1_trig.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_tim3_ch1_trig.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_tim3_ch1_trig.Init.Mode = DMA_NORMAL;
    hdma_tim3_ch1_trig.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_tim3_ch1_trig);

    // 3. 配置 TIM3 为 PWM 输出模式
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 90 - 1;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim3);


    HAL_TIM_PWM_Init(&htim3);


    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);

    // 4. 链接 DMA 到 TIM3
    __HAL_LINKDMA(&htim3, hdma[TIM_DMA_ID_CC1], hdma_tim3_ch1_trig);
    __HAL_LINKDMA(&htim3, hdma[TIM_DMA_ID_TRIGGER], hdma_tim3_ch1_trig);

    // 5. 配置 GPIO 为 PWM 输出引脚（TIM3_CH1 -> PB4）
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;      // 复用推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 6. 引脚重映射
    __HAL_AFIO_REMAP_TIM3_PARTIAL();

    // 7. 配置 DMA 中断（可选）
    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

    // 8. 启动 PWM 输出
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)NULL, 0); // 可以稍后设置数据

    // 9. 初始哈 颜色数据
    for(int32_t i = 0;i < WS2812_W * WS2812_H * 24;i++) {
        WS2812_Data[i] = Code0;
    }
}

void WS2812_SetColor(uint16_t y, uint16_t x, uint32_t color) {
    for(int32_t i = 0;i < WS2812_W * WS2812_H * 24;i++) {
        WS2812_Data[i] = Code0;
    }
//    for (uint32_t i = y + WS2812_H + x;i < 24;i++) {
//        WS2812_Data[i] = color >> (23 - i) == 1 ? Code1 : Code0;
//    }
}


void WS2812_Update() {
    HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *) WS2812_Data,WS2812_W * WS2812_H * 24 + 1);
}