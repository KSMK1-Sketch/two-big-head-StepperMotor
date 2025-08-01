#include "i2c.h"

//实现us级延时
#define delay_us(X)     delay_cycles( (CPUCLK_FREQ/1000000) * (X) )

/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Start(void)
{
    SDA_OUT();//设置SDA为输出模式
    SDA(1);
    SCL(1);
    delay_us(5);
    SDA(0);
    delay_us(5);
    SCL(0);
    delay_us(5);
}

/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();
    SCL(0);
    SDA(0);
    SCL(1);
    delay_us(5);
    SDA(1);
    delay_us(5);
}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答
 * 函 数 形 参：0应答  1非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Send_Ack(uint8_t ack)
{
  SDA_OUT();
  SCL(0);
  SDA(0);
  delay_us(5);
  if(!ack) SDA(0);
  else     SDA(1);
  SCL(1);
  delay_us(5);
  SCL(0);
  SDA(1);
}

/******************************************************************
 * 函 数 名 称：IIC_Wait_Ack
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：1=无应答   0=有应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t IIC_Wait_Ack(void)
{
  char ack = 0;
  unsigned char ack_flag = 10;
  SDA_IN();
  SCL(0);
  delay_us(5);
  SCL(1);
  delay_us(5);
  while( (SDA_GET()==1) && ( ack_flag ) )
  {
          ack_flag--;
          delay_us(5);
  }

  if( ack_flag <= 0 )
  {
          IIC_Stop();
          return 1;
  }
  else
  {
          SCL(0);
          SDA_OUT();
  }
  return ack;
}
/******************************************************************
 * 函 数 名 称：IIC_Send_Byte
 * 函 数 说 明：IIC写一个字节
 * 函 数 形 参：dat写入的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void IIC_Send_Byte(uint8_t dat)
{
    int i = 0;
    SDA_OUT();
    SCL(0);
    for( i = 0; i < 8; i++ )
    {
        SDA( (dat & 0x80) >> 7 );
        delay_us(1);
        SCL(1);
        delay_us(5);
        SCL(0);
        delay_us(5);
        dat<<=1;
    }
}
/******************************************************************
 * 函 数 名 称：IIC_Read_Byte
 * 函 数 说 明：IIC读1个字节
 * 函 数 形 参：无
 * 函 数 返 回：读出的1个字节数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char IIC_Read_Byte(void)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        SCL(0);
        delay_us(5);
        SCL(1);
        delay_us(5);
        receive<<=1;
        if( SDA_GET() )
        {
            receive |= 1;
        }
    }
    SCL(0);
    return receive;
}