#ifndef __GRAYSCALE_H__
#define __GRAYSCALE_H__

#include "A_include.h"

#define IR_I2C_ADDR 0x12

void IRI2C_WriteByte(uint8_t addr, uint8_t dat);
uint8_t IRI2C_ReadByte(uint8_t addr);

void deal_IRdata(u8 *x1,u8 *x2,u8 *x3,u8 *x4,u8 *x5,u8 *x6,u8 *x7,u8 *x8);
void printf_i2c_data(void);

#endif

