#include "..\HARDWARE\1298N\1298n.h"

/******************************************************************
 * �� �� �� �ƣ�AB_Motor_Stop
 * �� �� ˵ ����AB�˿ڵ��ֹͣ
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LCKFB
 * ��       ע����
******************************************************************/
void AB_Motor_Stop(void)
{
    //AIN1���
    DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 999 , GPIO_PWM_IN12_C0_IDX);
    //AIN2���
    DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 999 , GPIO_PWM_IN12_C1_IDX);
    //AIN3���
    DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 999 , GPIO_PWM_IN34_C0_IDX);
    //AIN4���
    DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 999 , GPIO_PWM_IN34_C1_IDX);
}

/******************************************************************
 * �� �� �� �ƣ�A_Motor_Control
 * �� �� ˵ ����A�˿ڵ������
 * �� �� �� �Σ�dir��ת���� 1��ת0��ת   speed��ת�ٶȣ���Χ��0 ~ per-1��
 * �� �� �� �أ���
 * ��       �ߣ�LCKFB
 * ��       ע����
******************************************************************/
void A_Motor_Control(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        //AIN1���
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 0 , GPIO_PWM_IN12_C0_IDX);
        //AIN2���
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, speed , GPIO_PWM_IN12_C1_IDX);
    }
    else
    {
        //AIN1���
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, speed , GPIO_PWM_IN12_C0_IDX);
        //AIN2���
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 0 , GPIO_PWM_IN12_C1_IDX);
    }
}


/******************************************************************
 * �� �� �� �ƣ�B_Motor_Control
 * �� �� ˵ ����B�˿ڵ������
 * �� �� �� �Σ�dir��ת���� 1��ת0��ת   speed��ת�ٶȣ���Χ��0 ~ per-1��
 * �� �� �� �أ���
 * ��       �ߣ�LCKFB
 * ��       ע����
******************************************************************/
void B_Motor_Control(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        //AIN3���
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 0 , GPIO_PWM_IN34_C0_IDX);
        //AIN4���
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, speed , GPIO_PWM_IN34_C1_IDX);
    }
    else
    {
        //AIN3���
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 0 , GPIO_PWM_IN34_C0_IDX);
        //AIN4���
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, speed , GPIO_PWM_IN34_C1_IDX);
    }
}