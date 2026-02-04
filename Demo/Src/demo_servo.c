//
// Created by pc on 2026/2/5.
//

#include "demo_servo.h"
#include "PWM.h"

void demo_servo() {

    PWM_TIM2_Init(7200, 100);
    PWM_TIM3_Init(7200, 100);
    PWM_TIM4_Init(7200, 100);


    uint32_t i = 0;
    uint8_t direction = 1;
    while (1)
    {
        if(direction) {
            i++;
            if(i >= 100) {
                direction = 0;
            }
        } else {
            i--;
            if(i <= 0) {
                direction = 1;
            }
        }
        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_1, i);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_1, i);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_1, i);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_2, i);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_2, i);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_2, i);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_3, i);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_3, i);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_3, i);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_4, i);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_4, i);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_4, i);
        HAL_Delay((100 - i) / 5);
    }
}
