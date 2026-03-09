//
// Created by pc on 2026/3/9.
//

#include "Demo_time.h"
#include "Timer.h"
#include "OLED.h"

void Timer_Interrupt_2(void) {
    OLED_ShowNum(0, 0, Timer_GetConfig(TIM2)->count, 4, OLED_8X16);
    OLED_Update();
}

void demo_time01() {
    OLED_Init();
    Timer_Init(TIM2, 7200, 10000);
    Timer_Start(TIM2, 10);
}


void demo_time() {
    demo_time01();
}
