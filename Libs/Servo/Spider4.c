//
// Created by pc on 2026/3/5.
//

#include "Spider4.h"
#include "Servo.h"

void Spider4_Init() {
    Servo_Init(TIM2);
    Servo_Init(TIM3);
}

void Spider4_Test() {
    Servo_Init(TIM2);
    Servo_Init(TIM3);

    while (1) {
        Servo180_Move(Spider4_FL_Leg, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_FL_Leg, 105);
        HAL_Delay(1000);
        Servo180_Move(Spider4_FL_Foot, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_FL_Foot, 105);
        HAL_Delay(1000);

        Servo180_Move( Spider4_FR_Leg, 75);
        HAL_Delay(1000);
        Servo180_Move( Spider4_FR_Leg, 105);
        HAL_Delay(1000);
        Servo180_Move(Spider4_FR_Foot, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_FR_Foot, 105);
        HAL_Delay(1000);

        Servo180_Move(Spider4_BL_Leg, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BL_Leg, 105);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BL_Foot, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BL_Foot, 105);
        HAL_Delay(1000);


        Servo180_Move(Spider4_BR_Leg, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BR_Leg, 105);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BR_Foot, 75);
        HAL_Delay(1000);
        Servo180_Move(Spider4_BR_Foot, 105);
        HAL_Delay(1000);

        Servo180_Move(Spider4_FL_Leg, 90);
        Servo180_Move(Spider4_FL_Foot, 90);
        Servo180_Move(Spider4_FR_Leg, 90);
        Servo180_Move(Spider4_FR_Foot, 90);
        Servo180_Move(Spider4_BL_Leg, 90);
        Servo180_Move(Spider4_BL_Foot, 90);
        Servo180_Move(Spider4_BR_Leg, 90);
        Servo180_Move(Spider4_BR_Foot, 90);
        HAL_Delay(10000);




    }


}

void Spider4_FootAll(uint8_t  degree) {
    Servo180_Move(Spider4_FL_Foot, 180 - degree);
    Servo180_Move(Spider4_FR_Foot, degree);
    Servo180_Move(Spider4_BL_Foot, degree);
    Servo180_Move(Spider4_BR_Foot, 180 - degree);

}

void Spider4_LegAll(uint8_t  degree) {
    Servo180_Move(Spider4_FL_Leg, 180- degree);
    Servo180_Move(Spider4_FR_Leg, degree);
    Servo180_Move(Spider4_BL_Leg, degree);
    Servo180_Move(Spider4_BR_Leg, 180 - degree);
}


