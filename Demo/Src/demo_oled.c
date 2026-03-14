//
// Created by pc on 2026/3/10.
//

#include "demo_oled.h"
#include "OLED.h"

void demo_oled01(void) {
    OLED_Init();
    OLED_ShowImage(0, 0, 128, 64, Face_very_happy);
    OLED_Update();
}


void demo_oled(void)
{
    demo_oled01();
}
