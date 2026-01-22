//
// Created by pc on 2026/1/23.
//

#include "LCD_Draw.h"
#include "LCD_Box.h"

void LCD_DrawComponent(LCD_Base * component) {
    if (component->typeId == 1) {
        LCD_DrawBox((LCD_Box*)component);
    }
}
