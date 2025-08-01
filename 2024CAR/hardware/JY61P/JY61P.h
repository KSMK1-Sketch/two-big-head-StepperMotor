#ifndef	__JY61P_H__
#define __JY61P_H__

#include "A_include.h"

// 调试开关
#define GYRO_DEBUG	0

// 定义一个结构体来存储
typedef struct {
    float x;
    float y;
    float z;
} Gyro_Struct;

// 模块地址
#define	IIC_ADDR		0x50
// 航向角地址
#define YAW_REG_ADDR	0x3F
// 寄存器解锁
#define UN_REG			0x69
// 保存寄存器
#define SAVE_REG		0x00
// 角度参考寄存器
#define ANGLE_REFER_REG	0x01

//SDA输入模式
#define SDA_IN()   {  DL_GPIO_initDigitalInput(IIC_JY61P_SDA_JY61P_IOMUX); }
//SDA输出模式
#define SDA_OUT()  {  DL_GPIO_initDigitalOutput(IIC_JY61P_SDA_JY61P_IOMUX); \
                      DL_GPIO_enableOutput(IIC_JY61P_PORT, IIC_JY61P_SDA_JY61P_PIN); \
                   }

#define SCL(BIT)  ( BIT ? DL_GPIO_setPins(IIC_JY61P_PORT,IIC_JY61P_SCL_JY61P_PIN) : DL_GPIO_clearPins(IIC_JY61P_PORT,IIC_JY61P_SCL_JY61P_PIN) )
#define SDA(BIT)  ( BIT ? DL_GPIO_setPins(IIC_JY61P_PORT,IIC_JY61P_SDA_JY61P_PIN) : DL_GPIO_clearPins(IIC_JY61P_PORT,IIC_JY61P_SDA_JY61P_PIN) )
#define SDA_GET() ( ( DL_GPIO_readPins( IIC_JY61P_PORT, IIC_JY61P_SDA_JY61P_PIN ) & IIC_JY61P_SDA_JY61P_PIN ) ? 1 : 0 )

void jy61pInit(void);
uint8_t readDataJy61p(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
uint8_t writeDataJy61p(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);
Gyro_Struct *get_angle(void);

#endif