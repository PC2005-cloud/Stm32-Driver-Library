//
// Created by pc on 2026/3/10.
//

#include "HCSR04.h"
#include "BSP_GPIO.h"
#include "Timer.h"
#include "Delay.h"

#define TRIG_PIN            GPIO_PIN_11
#define ECHO_PIN            GPIO_PIN_12
#define GPIOx           GPIOA
#define TIMx            TIM2
#define prescaler 7200
#define period 10000


// 声速
#define SOUND_SPEED 0.034
// 计数与时间转换的系数
#define CONVERT_COEFFICIENT (prescaler / 72.0f )

void HCSR04_Init() {
    GPIO_Init(GPIOx, TRIG_PIN, True);
    GPIO_Init(GPIOx, ECHO_PIN, False);
    Timer_Init(TIMx, prescaler, period);

    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOx, ECHO_PIN, GPIO_PIN_RESET);
}

// 转换成距离
static uint16_t HCSR04_Convert(uint32_t count) {
    // 显式转换为float进行计算
    double distance = (double )count * CONVERT_COEFFICIENT * SOUND_SPEED / 2.0f;

    // 四舍五入返回整数距离
    uint16_t distance_int = (uint16_t)(distance + 0.5f);

    if (distance_int > 400) {
        return 0;
    }

    return distance_int;

}

uint16_t HCSR04_Measure() {
    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_SET);
    Delay_us(10);
    HAL_GPIO_WritePin(GPIOx, TRIG_PIN, GPIO_PIN_RESET);

    while (HAL_GPIO_ReadPin(GPIOx, ECHO_PIN) == GPIO_PIN_RESET);
    Timer_Start(TIMx, 1);
    while (HAL_GPIO_ReadPin(GPIOx, ECHO_PIN) == GPIO_PIN_SET);
    Timer_Pause(TIMx);
    uint32_t time = Timer_GetValue(TIM2);
    Timer_Reset(TIMx);

    return HCSR04_Convert( time);
}
