#include "..\HARDWARE\1298N\1298n.h"

/******************************************************************
 * 函 数 名 称：AB_Motor_Stop
 * 函 数 说 明：AB端口电机停止
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void AB_Motor_Stop(void)
{
    //AIN1输出
    DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 999 , GPIO_PWM_IN12_C0_IDX);
    //AIN2输出
    DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 999 , GPIO_PWM_IN12_C1_IDX);
    //AIN3输出
    DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 999 , GPIO_PWM_IN34_C0_IDX);
    //AIN4输出
    DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 999 , GPIO_PWM_IN34_C1_IDX);
}

/******************************************************************
 * 函 数 名 称：A_Motor_Control
 * 函 数 说 明：A端口电机控制
 * 函 数 形 参：dir旋转方向 1正转0反转   speed旋转速度，范围（0 ~ per-1）
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void A_Motor_Control(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        //AIN1输出
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 0 , GPIO_PWM_IN12_C0_IDX);
        //AIN2输出
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, speed , GPIO_PWM_IN12_C1_IDX);
    }
    else
    {
        //AIN1输出
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, speed , GPIO_PWM_IN12_C0_IDX);
        //AIN2输出
        DL_TimerG_setCaptureCompareValue(PWM_IN12_INST, 0 , GPIO_PWM_IN12_C1_IDX);
    }
}


/******************************************************************
 * 函 数 名 称：B_Motor_Control
 * 函 数 说 明：B端口电机控制
 * 函 数 形 参：dir旋转方向 1正转0反转   speed旋转速度，范围（0 ~ per-1）
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
******************************************************************/
void B_Motor_Control(uint8_t dir, uint32_t speed)
{
    if( dir == 1 )
    {
        //AIN3输出
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 0 , GPIO_PWM_IN34_C0_IDX);
        //AIN4输出
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, speed , GPIO_PWM_IN34_C1_IDX);
    }
    else
    {
        //AIN3输出
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, 0 , GPIO_PWM_IN34_C0_IDX);
        //AIN4输出
        DL_TimerG_setCaptureCompareValue(PWM_IN34_INST, speed , GPIO_PWM_IN34_C1_IDX);
    }
}