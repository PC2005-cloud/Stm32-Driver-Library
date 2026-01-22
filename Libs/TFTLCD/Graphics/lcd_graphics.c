//
// Created by pc on 2026/1/21.
//

#include "lcd_graphics.h"
#include "lcd_cmd.h"
#include "SPI1.h"
#include "lcd_gpio.h"
#include "OLED.h"

void LCD_Point(uint16_t x, uint16_t y, uint16_t color) {
    LCD_Draw(x, y, x, y, color);
}

void LCD_Rectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color) {
    LCD_Draw(sx, sy, ex, ey, color);
}

void LCD_RectangleWithRadius(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t radius, uint16_t color) {
    LCD_Rectangle(sx, sy + radius, ex, ey - radius, color);
    LCD_Rectangle(sx + radius, sy, ex - radius, sy + radius, color);
    LCD_Rectangle(sx + radius, ey - radius, ex - radius, ey, color);

    uint16_t cX = (sx + ex) / 2;
    uint16_t cY = (sy + ey) / 2;
    uint16_t rX = cX - sx - radius;
    uint16_t rY = cY - sy - radius;
    LCD_Arc(cX - rX, cY - rY, radius, color, 3, 4);
    LCD_Arc(cX + rX, cY - rY, radius, color, 1, 2);
    LCD_Arc(cX - rX, cY + rY, radius, color, 5, 6);
    LCD_Arc(cX + rX, cY + rY, radius, color, 7, 8);
}
void LCD_RectangularBorder(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t width, uint16_t color) {
    // 上边
    LCD_Rectangle(sx, sy, ex, sy + width - 1, color);
    // 下边
    LCD_Rectangle(sx, ey - width + 1, ex, ey, color);
    // 左边
    LCD_Rectangle(sx, sy + width, sx + width - 1, ey - width, color);
    // 右边
    LCD_Rectangle(ex - width + 1, sy + width, ex, ey - width, color);
}

void LCD_RectangularBorderWithRadius(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t width, uint16_t radius, uint16_t color) {
    // 上边
    LCD_Rectangle(sx + radius, sy, ex - radius, sy + width - 1, color);
    // 下边
    LCD_Rectangle(sx + radius, ey - width + 1, ex - radius, ey, color);
    // 左边
    LCD_Rectangle(sx, sy + radius, sx + width - 1, ey - radius, color);
    // 右边
    LCD_Rectangle(ex - width + 1, sy + radius, ex, ey - radius, color);

    uint16_t centerX = (sx + ex) / 2;
    uint16_t centerY = (sy + ey) / 2;
    uint16_t rX = centerX - sx- radius;
    uint16_t rY = centerY - sy - radius;
    uint16_t r = radius > width ? width :radius;
    LCD_ArcBorder(centerX - rX, centerY - rY, radius, width, color, 3, 4);
    LCD_ArcBorder(centerX + rX, centerY - rY, radius, width, color, 1, 2);
    LCD_ArcBorder(centerX + rX, centerY + rY, radius, width, color, 7, 8);
    LCD_ArcBorder(centerX - rX, centerY + rY, radius, width, color, 5, 6);

}

void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)incx = 1; //设置单步方向
    else if (delta_x == 0)incx = 0;//垂直线
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;//水平线
    else {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++)//画线输出
    {
        LCD_Point(uRow, uCol, color);//画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void _draw_circle_8(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y, uint16_t color,  uint8_t start, uint8_t end) {
    for (uint8_t segment = start; segment <= end; segment++) {
        switch (segment) {
            case 7:  // ( x,  y)
                LCD_Point(xc + x, yc + y, color);
                break;
            case 6:  // (-x,  y)
                LCD_Point(xc - x, yc + y, color);
                break;
            case 2:  // ( x, -y)
                LCD_Point(xc + x, yc - y, color);
                break;
            case 3:  // (-x, -y)
                LCD_Point(xc - x, yc - y, color);
                break;
            case 8:  // ( y,  x)
                LCD_Point(xc + y, yc + x, color);
                break;
            case 5:  // (-y,  x)
                LCD_Point(xc - y, yc + x, color);
                break;
            case 1:  // ( y, -x)
                LCD_Point(xc + y, yc - x, color);
                break;
            case 4:  // (-y, -x)
                LCD_Point(xc - y, yc - x, color);
                break;
        }
    }
}

void LCD_Circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color) {
    LCD_Arc(xc, yc, r, color, 1, 8);
}

void LCD_CircleBorder(uint16_t xc, uint16_t yc, uint16_t r, uint16_t width, uint16_t color) {
    LCD_ArcBorder(xc, yc, r, width, color, 1, 8);
}

void LCD_Arc(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color, uint8_t start, uint8_t end) {
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;


    while (x <= y) {
        for (yi = x; yi <= y; yi++)
            _draw_circle_8(xc, yc, x, yi, color, start, end);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
void LCD_ArcBorder(uint16_t xc, uint16_t yc, uint16_t r, uint16_t width, uint16_t color,uint8_t start, uint8_t end) {
    int x = 0, y = r,yi, d;

    d = 3 - 2 * r;

    uint16_t l = r - width;

    while (x <= y) {
        for (yi = x; yi <= y; yi++) {
            if (x * x + yi * yi > l * l) {
                _draw_circle_8(xc, yc, x, yi, color, start, end);
            }
        }

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void LCD_Triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    LCD_Line(x0, y0, x1, y1, color);
    LCD_Line(x1, y1, x2, y2, color);
    LCD_Line(x2, y2, x0, y0, color);
}

static void _swap(uint16_t *a, uint16_t *b) {
    uint16_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void LCD_Fill_Triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0;
    long sb = 0;
    if (y0 > y1) {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y1 > y2) {
        _swap(&y2, &y1);
        _swap(&x2, &x1);
    }
    if (y0 > y1) {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) {
            a = x1;
        } else if (x1 > b) {
            b = x1;
        }
        if (x2 < a) {
            a = x2;
        } else if (x2 > b) {
            b = x2;
        }
        LCD_Rectangle(a, y0, b, y0, color);
        return;
    }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if (y1 == y2) {
        last = y1;
    } else {
        last = y1 - 1;
    }
    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b) {
            _swap(&a, &b);
        }
        LCD_Rectangle(a, y, b, y, color);
    }
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) {
            _swap(&a, &b);
        }
        LCD_Rectangle(a, y, b, y, color);
    }
}


void LCD_Picture(uint16_t x, uint16_t y, uint16_t column, uint16_t row, uint16_t *pic) {
    LCD_SetWindows(x, y, x + column - 1, y + row - 1);
    LCD_DataMode();
    SPI1_Start();
    uint16_t m, h;
    for (h = 0 + y; h < row + y; h++) {
        for (m = 0 + x; m < column + x; m++) {
            uint16_t color = *pic;
            LCD_ChangeColor(&color);
            SPI1_SwapByte(color >> 8);
            SPI1_SwapByte(color);

            pic++;
        }
    }
    SPI1_Stop();
}