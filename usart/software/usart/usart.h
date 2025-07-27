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
 * 2024-12-19     Updated    Added multi-UART support

 配置uart端口，PA10与PA11，并且设置时钟树
 支持UART_0和UART_1两个串口实例
 */
#ifndef __USART_H__
#define __USART_H__

#include "ti_msp_dl_config.h"
#include <stdio.h>
#include "stdint.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>

// 基础串口函数
void USART_Init_Instance(UART_Regs *uart_inst, IRQn_Type irq_irqn);
void USART_Init(void);

// 通用串口发送函数
void uart_send_char(UART_Regs *uart_inst, char ch);
void uart_send_string(UART_Regs *uart_inst, char *str);

// UART_0 专用函数
void uart0_send_char(char ch);
void uart0_send_string(char *str);

// UART_1 专用函数
void uart1_send_char(char ch);
void uart1_send_string(char *str);

// 串口数据管理函数
uint8_t uart_get_received_data(UART_Regs *uart_inst,
                               volatile uint8_t **buffer,
                               volatile uint16_t **length,
                               volatile uint8_t **flag);
void uart_clear_buffer(UART_Regs *uart_inst);
uint8_t uart_data_available(UART_Regs *uart_inst);

#endif
