//
// Created by pc on 2026/2/28.
//



#include "Servo.h"

#define prescaler 7200
#define period 200

void Servo_Init(TIM_TypeDef *tim) {
    PWM_Init_TIM(tim, prescaler, period);
}

// 360度舵机移动
void Servo360_Move(enum PWMPin ePin, int8_t speed) {
    uint32_t servo_pwm = speed + 15;
    PWM_Set_COMPARE(ePin, servo_pwm);
}

// 180度舵机转动角度
void Servo180_Move(enum PWMPin ePin, uint8_t degree) {
    uint32_t servo_pwm = degree / 9 + 5;
    PWM_Set_COMPARE(ePin, servo_pwm);
}

