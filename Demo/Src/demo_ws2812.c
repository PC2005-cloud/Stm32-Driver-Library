//
// Created by pc on 2026/1/23.
//

#include "demo_ws2812.h"
#include "WS2812.h"

static void demo01() {
    WS2812_Update();
    WS2812_SetColor(0, 0, 0x124578);
}

void demo_ws2812() {
    WS2812_Init();
    demo01();
}
