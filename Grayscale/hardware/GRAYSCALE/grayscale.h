#ifndef __GRAYSCALE_H__
#define __GRAYSCALE_H__

#include "A_include.h"

#define IR_I2C_ADDR 0x12

void IRI2C_WriteByte(uint8_t addr, uint8_t dat);
uint8_t IRI2C_ReadByte(uint8_t addr);
void printf_i2c_data(void);

#endif

