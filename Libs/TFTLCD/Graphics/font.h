#ifndef __FONT_H
#define __FONT_H

#include "stm32f1xx_hal.h"

extern const unsigned char asc2_1206[95][12];

extern const unsigned char asc2_1608[95][16];

typedef struct {
    char Index[5];
    uint8_t Data[24];
} Character1212;

typedef struct {
    char Index[5];
    uint8_t Data[32];
} Character1616;

typedef struct {
    char Index[5];
    uint8_t Data[72];
} Character2424;

extern const Character1212 character1212[];
extern const Character1616 character1616[];
extern const Character2424 character2424[];
#endif
