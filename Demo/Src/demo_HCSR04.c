//
// Created by pc on 2026/3/10.
//

#include "demo_HCSR04.h"
#include "Timer.h"
#include "OLED.h"
#include "BSP_GPIO.h"
#include "../../Libs/HCSR04/HCSR04.h"
#include "Delay.h"

#define TRIG_PIN            GPIO_PIN_11
#define TRIG_PORT           GPIOA
#define ECHO_PIN            GPIO_PIN_12
#define ECHO_PORT           GPIOA




void demo_HCSR04() {
    HCSR04_Init();

    OLED_Init();

    while (1) {
        uint16_t time = HCSR04_Measure();

        OLED_ShowNum(0, 0, time, 6, OLED_8X16);
        OLED_Update();
    }
}