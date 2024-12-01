#pragma once

#include <stdint.h>

typedef union {
    uint8_t reg[8];
} paw3204_all_reg;

uint8_t read_pid_paw3204_custom(void);
void    init_paw3204_custom(void);
int     read_paw3204_custom(uint8_t *stat, int8_t *x, int8_t *y);
void    read_all_paw3204_custom(paw3204_all_reg *dat);
