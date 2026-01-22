//
// Created by pc on 2026/1/22.
//

#include "LCD_Box.h"
#include "lcd_graphics.h"
#include "OLED.h"

void LCD_InitBox(LCD_Box *box) {
    box->typeId = 1;
}
void LCD_DrawBox(LCD_Box *box) {
    uint16_t r = box->corner_radius > box->border_width ? box->corner_radius - box->border_width : 0;
    LCD_RectangleWithRadius(box->x + box->border_width, box->y + box->border_width, box->x + box->width - 1 - box->border_width, box->y + box->height - 1 - box->border_width, r, box->background);
    LCD_RectangularBorderWithRadius(box->x, box->y, box->x + box->width - 1, box->y + box->height - 1, box->border_width, box->corner_radius,box->border_color);

}