//
// Created by pc on 2026/2/5.
//

#include "demo_servo.h"
#include "Servo.h"
#include "Spider4.h"
#include "Dog.h"

void demo_servo01() {

    PWM_Init_TIM(TIM2, 7200, 200);
    PWM_Init_TIM(TIM3, 7200, 200);
    PWM_Init_TIM(TIM4, 7200, 200);


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

        PWM_Set_COMPARE(PWM_A0, servo_pwm);
        PWM_Set_COMPARE(PWM_A1, servo_pwm);
        PWM_Set_COMPARE(PWM_A2, servo_pwm);

        PWM_Set_COMPARE(PWM_A3, servo_pwm);
        PWM_Set_COMPARE(PWM_A6, servo_pwm);
        PWM_Set_COMPARE(PWM_A7, servo_pwm);

        PWM_Set_COMPARE(PWM_B6, servo_pwm);
        PWM_Set_COMPARE(PWM_B7, servo_pwm);
        PWM_Set_COMPARE(PWM_B8, servo_pwm);

        PWM_Set_COMPARE(PWM_B9, servo_pwm);
        PWM_Set_COMPARE(PWM_B0, servo_pwm);
        PWM_Set_COMPARE(PWM_B1, servo_pwm);

    }
}

void demo_servo02() {
    PWM_Init_TIM(TIM2, 7200, 200);


    PWM_Set_COMPARE(PWM_A0, 10);

    HAL_Delay(20);

}

void demo_servo03() {
    Servo_Init(TIM2);

    int8_t speed = 0;
    int8_t step = 1;
    int8_t flag = 1;

    while (1) {
        Servo360_Move(PWM_A0, speed);

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

void demo_servo04() {
    Servo_Init(TIM2);
    Servo_Init(TIM3);
    while (1) {
        Servo180_Move(PWM_A0, 75);
        Servo180_Move(PWM_A1, 75);
        Servo180_Move(PWM_A2, 75);
        Servo180_Move(PWM_A3, 75);
        Servo180_Move(PWM_A6, 75);
        Servo180_Move(PWM_A7, 75);
        Servo180_Move(PWM_B6, 75);
        Servo180_Move(PWM_B7, 75);
        HAL_Delay(1000);
        Servo180_Move(PWM_A0, 105);
        Servo180_Move(PWM_A1, 105);
        Servo180_Move(PWM_A2, 105);
        Servo180_Move(PWM_A3, 105);
        Servo180_Move(PWM_A6, 105);
        Servo180_Move(PWM_A7, 105);
        Servo180_Move(PWM_B6, 105);
        Servo180_Move(PWM_B7, 105);
        HAL_Delay(1000);

    }

}

void demo_servo05() {
    Spider4_Init();
    while (1) {
        Spider4_FootAll(30);
        Spider4_LegAll(45);
        HAL_Delay(5000);

        Spider4_FootAll(0);
        Spider4_LegAll(90);
        HAL_Delay(5000);
    }

}

void demo_servo06() {
    Dog_Init();

    Dog_Turn(50000, 250, -30);


}


void demo_servo() {
    demo_servo06();

}
