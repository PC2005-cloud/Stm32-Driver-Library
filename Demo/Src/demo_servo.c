//
// Created by pc on 2026/2/5.
//

#include "demo_servo.h"
#include "servo.h"

void demo_servo01() {
    PWM_TIM2_Init(7200, 200);
    PWM_TIM3_Init(7200, 200);
    PWM_TIM4_Init(7200, 200);


    uint32_t i = 0;
    uint8_t direction = 1;
    while (1) {
        if (direction) {
            i++;
            if (i >= 200) {  // 对应20ms周期
                direction = 0;
            }
        } else {
            i--;
            if (i <= 0) {
                direction = 1;
            }
        }

        uint32_t servo_pwm = 5 + (i * 20 / 200);  // 线性映射

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_1, servo_pwm);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_1, servo_pwm);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_1, servo_pwm);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_2, servo_pwm);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_2, servo_pwm);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_2, servo_pwm);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_3, servo_pwm);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_3, servo_pwm);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_3, servo_pwm);

        PWM_Set_COMPARE(TIM2, TIM_CHANNEL_4, servo_pwm);
        PWM_Set_COMPARE(TIM3, TIM_CHANNEL_4, servo_pwm);
        PWM_Set_COMPARE(TIM4, TIM_CHANNEL_4, servo_pwm);
        HAL_Delay(20);
    }
}

void demo_servo02() {
    PWM_TIM2_Init(7200, 200);


    PWM_Set_COMPARE(TIM2, TIM_CHANNEL_1, 10);

    HAL_Delay(20);

}

void demo_servo03() {
    Servo_Init(TIM2);

    int8_t speed = 0;
    int8_t step = 1;
    int8_t flag = 1;

    while (1) {
        Servo360_Move(TIM2, TIM_CHANNEL_1, speed);

        if (flag) {
            speed = step;      // 正数: 1, 2, 3, 4...
            flag = 0;
        } else {
            speed = -step;     // 负数: -1, -2, -3, -4...
            step++;            // 步进增加
            flag = 1;
        }

        // 到达边界后重置（可选）
        if (step > 1) {
            step = 1;
        }

        HAL_Delay(1000);
    }


}

void demo_servo() {
    demo_servo03();

}
