//
// Created by pc on 2026/2/28.
//



#include "servo.h"

#define prescaler 7200
#define period 200

void Servo_Init(TIM_TypeDef *tim) {
    if (tim == TIM2) {
        PWM_Init_TIM2_1CH(prescaler, period);
    } else if (tim == TIM3) {
        PWM_Init_TIM3_1CH(prescaler, period);
    } else if ( tim == TIM4) {
        PWM_Init_TIM4_1CH(prescaler, period);
    }
}

// 360度舵机移动
void Servo360_Move(TIM_TypeDef *tim, uint32_t channel, int8_t speed) {
    uint32_t servo_pwm = speed + 15;
    PWM_Set_COMPARE(tim, channel, servo_pwm);
}

// 180度舵机转动角度
void Servo180_Move(TIM_TypeDef *tim, uint32_t channel, int8_t degree) {
    uint32_t servo_pwm = degree / 9 + 5;
    PWM_Set_COMPARE(tim, channel, servo_pwm);
}
