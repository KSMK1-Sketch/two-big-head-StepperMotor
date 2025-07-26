#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "A_include.h"

// 获得绝对值
#define ABS(a) (a > 0 ? a : (-a))

typedef struct
{
    int Should_Get_Encoder_Count;   // 将要获得的编码器计数
    int Obtained_Get_Encoder_Count; // 得到的编码器的计数
    int Encoder_Count;              // 编码器计数
} Encoder;

void Encoder_Init(void);
int Encoder_Getcount(int dir);
void Encoder_Clearcount(void);
int Encoder_Getcountdistance(int dir);   

#endif