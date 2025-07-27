

#include "encoder.h"

static volatile Encoder Encoder_A;
static volatile Encoder Encoder_B;
static volatile Encoder Encoder_C;
static volatile Encoder Encoder_D;

/******************************************************************
 * 函 数 名 称：Motor_Init
 * 函 数 说 明：电机与编码器初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：silly
 * 备       注：无
 ******************************************************************/
void Encoder_Init(void)
{
    // 编码器引脚外部中断
    NVIC_ClearPendingIRQ(ENCODER_GPIOA_INT_IRQN);
    NVIC_EnableIRQ(ENCODER_GPIOA_INT_IRQN);
    NVIC_ClearPendingIRQ(ENCODER_GPIOB_INT_IRQN);
    NVIC_EnableIRQ(ENCODER_GPIOB_INT_IRQN);

    // 定时器中断
    NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    printf("Motor initialized successfully\r\n");
}

/******************************************************************
 * 函 数 名 称：Motor_Get_Encoder
 * 函 数 说 明：获取编码器的值
 * 函 数 形 参：dir=1/3获取左轮编码器值  dir=2/4获取右轮编码器值
 * 函 数 返 回：返回对应的编码器值
 * 作       者：silly
 * 备       注：无
 ******************************************************************/
int Encoder_Getcount(int dir)
{
    if (dir == 1)
        return Encoder_A.Obtained_Get_Encoder_Count;
    else if (dir == 2)
        return Encoder_B.Obtained_Get_Encoder_Count;
    else if (dir == 3)
        return Encoder_C.Obtained_Get_Encoder_Count;
    else if (dir == 4)
        return Encoder_D.Obtained_Get_Encoder_Count;
    else
        return 0;
}
/******************************************************************
 * 函 数 名 称：Encoder_Getcountdistance
 * 函 数 说 明：获取编码器的总值
 * 函 数 形 参：dir=1/3获取左轮编码器值  dir=2/4获取右轮编码器值
 * 函 数 返 回：返回对应的编码器值
 * 作       者：silly
 * 备       注：无
 ******************************************************************/
int Encoder_Getcountdistance(int dir)
{
    if (dir == 1)
        return Encoder_A.Encoder_Count;
    else if (dir == 2)
        return Encoder_B.Encoder_Count;
    else if (dir == 3)
        return Encoder_C.Encoder_Count;
    else if (dir == 4)
        return Encoder_D.Encoder_Count;
    else
        return 0;
}

/******************************************************************
 * 函 数 名 称：Encoder_Clearcount
 * 函 数 说 明：编码器计数值清零
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：silly
 * 备       注：无
 ******************************************************************/
void Encoder_Clearcount(void)
{
    Encoder_A.Should_Get_Encoder_Count = 0;
    Encoder_B.Should_Get_Encoder_Count = 0;
    Encoder_C.Should_Get_Encoder_Count = 0;
    Encoder_D.Should_Get_Encoder_Count = 0;
}
/*******************************************************
函数功能：外部中断模拟编码器信号
入口函数：无
返回  值：无
***********************************************************/
void GROUP1_IRQHandler(void)
{
    uint32_t gpio_interrup1 = 0;
    uint32_t gpio_interrup2 = 0;
    uint32_t gpio_interrup3 = 0;
    uint32_t gpio_interrup4 = 0;

    // 获取中断信号
    gpio_interrup1 = DL_GPIO_getEnabledInterruptStatus(ENCODER_E1A_PORT  , ENCODER_E1A_PIN | ENCODER_E1B_PIN);
    gpio_interrup2 = DL_GPIO_getEnabledInterruptStatus(ENCODER_E2A_PORT  , ENCODER_E2A_PIN | ENCODER_E2B_PIN);
    gpio_interrup3 = DL_GPIO_getEnabledInterruptStatus(ENCODER_E3A_PORT  , ENCODER_E3A_PIN | ENCODER_E3B_PIN);
    gpio_interrup4 = DL_GPIO_getEnabledInterruptStatus(ENCODER_E4A_PORT  , ENCODER_E4A_PIN | ENCODER_E4B_PIN);

    // encoderA
    if ((gpio_interrup1 & ENCODER_E1A_PIN) == ENCODER_E1A_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E1A_PORT, ENCODER_E1B_PIN))
        {
            Encoder_A.Should_Get_Encoder_Count--;
        }
        else
        {
            Encoder_A.Should_Get_Encoder_Count++;
        }
    }
    else if ((gpio_interrup1 & ENCODER_E1B_PIN) == ENCODER_E1B_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E1A_PORT, ENCODER_E1A_PIN))
        {
            Encoder_A.Should_Get_Encoder_Count++;
        }
        else
        {
            Encoder_A.Should_Get_Encoder_Count--;
        }
    }

    // encoderB
    if ((gpio_interrup2 & ENCODER_E2A_PIN) == ENCODER_E2A_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E2A_PORT, ENCODER_E2B_PIN))
        {
            Encoder_B.Should_Get_Encoder_Count--;
        }
        else
        {
            Encoder_B.Should_Get_Encoder_Count++;
        }
    }
    else if ((gpio_interrup2 & ENCODER_E2B_PIN) == ENCODER_E2B_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E2A_PORT, ENCODER_E2A_PIN))
        {
            Encoder_B.Should_Get_Encoder_Count++;
        }
        else
        {
            Encoder_B.Should_Get_Encoder_Count--;
        }
    }

    // encoderC
    if ((gpio_interrup3 & ENCODER_E3A_PIN) == ENCODER_E3A_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E3A_PORT, ENCODER_E3B_PIN))
        {
            Encoder_C.Should_Get_Encoder_Count--;
        }
        else
        {
            Encoder_C.Should_Get_Encoder_Count++;
        }
    }
    else if ((gpio_interrup3 & ENCODER_E3B_PIN) == ENCODER_E3B_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E3A_PORT, ENCODER_E3A_PIN))
        {
            Encoder_C.Should_Get_Encoder_Count++;
        }
        else
        {
            Encoder_C.Should_Get_Encoder_Count--;
        }
    }

    // encoderD
    if ((gpio_interrup4 & ENCODER_E4A_PIN) == ENCODER_E4A_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E4A_PORT, ENCODER_E4B_PIN))
        {
            Encoder_D.Should_Get_Encoder_Count--;
        }
        else
        {
            Encoder_D.Should_Get_Encoder_Count++;
        }
    }
    else if ((gpio_interrup4 & ENCODER_E4B_PIN) == ENCODER_E4B_PIN)
    {
        if (!DL_GPIO_readPins(ENCODER_E4A_PORT, ENCODER_E4A_PIN))
        {
            Encoder_D.Should_Get_Encoder_Count++;
        }
        else
        {
            Encoder_D.Should_Get_Encoder_Count--;
        }
    }

    DL_GPIO_clearInterruptStatus(ENCODER_E1A_PORT, ENCODER_E1A_PIN | ENCODER_E1B_PIN);
    DL_GPIO_clearInterruptStatus(ENCODER_E2A_PORT, ENCODER_E2A_PIN | ENCODER_E2B_PIN);
    DL_GPIO_clearInterruptStatus(ENCODER_E3A_PORT, ENCODER_E3A_PIN | ENCODER_E3B_PIN);
    DL_GPIO_clearInterruptStatus(ENCODER_E4A_PORT, ENCODER_E4A_PIN | ENCODER_E4B_PIN);
}

// 电机编码器脉冲计数
void TIMER_0_INST_IRQHandler(void)
{
    // 编码器速度计算
    if (DL_TimerG_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO)
    {
        /* 两个电机安装相反，所以编码器值也要相反 */
        Encoder_A.Obtained_Get_Encoder_Count = -Encoder_A.Should_Get_Encoder_Count;
        Encoder_B.Obtained_Get_Encoder_Count = Encoder_B.Should_Get_Encoder_Count;
        Encoder_C.Obtained_Get_Encoder_Count = -Encoder_C.Should_Get_Encoder_Count;
        Encoder_D.Obtained_Get_Encoder_Count = -Encoder_D.Should_Get_Encoder_Count;

        Encoder_A.Encoder_Count += Encoder_A.Obtained_Get_Encoder_Count;
        Encoder_B.Encoder_Count += Encoder_B.Obtained_Get_Encoder_Count;
        Encoder_C.Encoder_Count += Encoder_C.Obtained_Get_Encoder_Count;
        Encoder_D.Encoder_Count += Encoder_D.Obtained_Get_Encoder_Count;

        pid_control();
    }
}