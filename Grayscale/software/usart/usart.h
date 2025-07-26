/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version


 配置uart端口，PA10与PA11，并且设置时钟树
 */
#ifndef __USART_H__
#define __USART_H__

#include "ti_msp_dl_config.h"
#include <stdio.h>
#include "stdint.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>

void uart0_send_char(char ch);
void uart0_send_string(char *str);
void USART_Init(void);

#endif
