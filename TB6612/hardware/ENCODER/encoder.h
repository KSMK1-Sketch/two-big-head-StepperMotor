

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "A_include.h"


// ��þ���ֵ
#define ABS(a) (a > 0 ? a : (-a))

typedef struct
{
    int Should_Get_Encoder_Count;   // ��Ҫ��õı���������
    int Obtained_Get_Encoder_Count; // �õ��ı������ļ���
} Encoder;


void Encoder_Init(void);
int Encoder_Getcount(int dir);
void Encoder_Clearcount(void);

#endif