//
// Created by pc on 2026/3/8.
//

#include "Dog.h"
#include "Servo.h"
void Dog_Init() {
    Servo_Init(TIM2);
    Servo_Init(TIM3);
}

// 测试引脚顺序
void Dog_Test() {
    Dog_Init();
    while (1) {
        Servo180_Move(PWM_A0, 75);
        Servo180_Move(PWM_A1, 75);
        Servo180_Move(PWM_A2, 75);
        Servo180_Move(PWM_A3, 75);
        Servo180_Move(PWM_A6, 75);
        HAL_Delay(1000);
        Servo180_Move(PWM_A0, 105);
        Servo180_Move(PWM_A1, 105);
        Servo180_Move(PWM_A2, 105);
        Servo180_Move(PWM_A3, 105);
        Servo180_Move(PWM_A6, 105);
        HAL_Delay(1000);
    }

}

void Dog_ForwardSync(uint8_t degree) {
    Servo180_Move(Dog_LegFL, 180 - degree);
    Servo180_Move(Dog_LegFR, degree);
}
void Dog_BackwardSync(uint8_t degree) {
    Servo180_Move(Dog_LegBL, 180 - degree);
    Servo180_Move(Dog_LegBR, degree);
}

void Dog_MoveTrot(uint8_t  degree) {
    Dog_ForwardSync( degree);
    Dog_BackwardSync( degree);
}

void Dog_MovePace(uint8_t  degree) {
    Dog_ForwardSync( degree);
    Dog_BackwardSync( 180 - degree);
}

void Dog_TailMove(uint8_t  from, uint8_t  to, uint32_t delay_ms) {
    Servo180_Move(Dog_Tail, from);
    HAL_Delay(delay_ms);
    Servo180_Move(Dog_Tail, to);
    HAL_Delay(delay_ms);
}



void Dog_Walk(uint16_t steps, uint32_t delay_ms, uint16_t degree) {
    for (uint16_t i = 0; i < steps; i++) {
        Servo180_Move(Dog_LegFL, 90 + degree);
        Servo180_Move(Dog_LegBR, 90 - degree);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFR, 90 + degree);
        Servo180_Move(Dog_LegBL, 90 - degree);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFL, 90);
        Servo180_Move(Dog_LegBR, 90);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFR, 90);
        Servo180_Move(Dog_LegBL, 90);
        HAL_Delay(delay_ms);

    }
}

void Dog_Turn(uint16_t steps, uint32_t delay_ms, uint16_t degree) {
    for (uint16_t i = 0; i < steps; i++) {
        Servo180_Move(Dog_LegFL, 90 + degree);
        Servo180_Move(Dog_LegBR, 90 + degree);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFR, 90 - degree);
        Servo180_Move(Dog_LegBL, 90 - degree);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFL, 90);
        Servo180_Move(Dog_LegBR, 90);
        HAL_Delay(delay_ms);
        Servo180_Move(Dog_LegFR, 90);
        Servo180_Move(Dog_LegBL, 90);
        HAL_Delay(delay_ms);

    }
}