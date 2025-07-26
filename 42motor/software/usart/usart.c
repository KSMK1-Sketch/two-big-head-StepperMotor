#include "usart.h"
#include "stdio.h"

// 串口缓冲区定义
#define RE_0_BUFF_LEN_MAX 128
#define RE_1_BUFF_LEN_MAX 128

// UART_0 接收缓冲区
volatile uint8_t recv0_buff[RE_0_BUFF_LEN_MAX] = {0};
volatile uint16_t recv0_length = 0;
volatile uint8_t recv0_flag = 0;

// UART_1 接收缓冲区
volatile uint8_t recv1_buff[RE_1_BUFF_LEN_MAX] = {0};
volatile uint16_t recv1_length = 0;
volatile uint8_t recv1_flag = 0;

/**
 * @brief 串口初始化函数
 * @param uart_inst 串口实例 (UART_0_INST 或 UART_1_INST)
 * @param irq_irqn 中断号 (UART_0_INST_INT_IRQN 或 UART_1_INST_INT_IRQN)
 */
void USART_Init_Instance(UART_Regs *uart_inst, IRQn_Type irq_irqn)
{
	// 清除串口中断标志
	NVIC_ClearPendingIRQ(irq_irqn);
	// 使能串口中断
	NVIC_EnableIRQ(irq_irqn);
}

/**
 * @brief 初始化所有串口
 */
void USART_Init(void)
{
	// 初始化UART_0
	USART_Init_Instance(UART_0_INST, UART_0_INST_INT_IRQN);
	// 初始化UART_1
	USART_Init_Instance(UART_1_INST, UART_1_INST_INT_IRQN);

	// pr1tf("Board Init [[ ** LCKFB ** ]]\r\n");
}

/**
 * @brief 串口发送单个字符
 * @param uart_inst 串口实例
 * @param ch 要发送的字符
 */
void uart_send_char(UART_Regs *uart_inst, char ch)
{
	// 当串口忙的时候等待，不忙的时候再发送传进来的字符
	while (DL_UART_isBusy(uart_inst) == true)
		;
	// 发送单个字符
	DL_UART_Main_transmitData(uart_inst, ch);
}

/**
 * @brief 串口发送数据
 * @param uart_inst 串口实例
 * @param data 要发送的数据
 * @param len 数据长度
 */
void uart_send_data(UART_Regs *uart_inst,const uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		// 等待发送完成
		while (DL_UART_isBusy(uart_inst) == true)
			;
		// 发送数据
		DL_UART_Main_transmitData(uart_inst, data[i]);
	}
}
/**
 * @brief 串口发送字符串
 * @param uart_inst 串口实例
 * @param str 要发送的字符串
 */
void uart_send_string(UART_Regs *uart_inst, char *str)
{
	// 当前字符串地址不在结尾 并且 字符串首地址不为空

	while (*str != 0 && str != 0)
	{
		// 发送字符串首地址中的字符，并且在发送完成之后首地址自增
		uart_send_char(uart_inst, *str++);
	}
}

// UART_0 专用发送函数
void uart0_send_char(char ch)
{
	uart_send_char(UART_0_INST, ch);
}

void uart0_send_string(char *str)
{
	uart_send_string(UART_0_INST, str);
}

// UART_1 专用发送函数
void uart1_send_char(char ch)
{
	uart_send_char(UART_1_INST, ch);
}

void uart1_send_string(char *str)
{
	uart_send_string(UART_1_INST, str);
}

/**
 * @brief 获取串口接收数据
 * @param uart_inst 串口实例
 * @param buffer 接收缓冲区指针
 * @param length 接收长度指针
 * @param flag 接收标志指针
 * @return 接收到的数据
 */
uint8_t uart_get_received_data(UART_Regs *uart_inst,
							   volatile uint8_t **buffer,
							   volatile uint16_t **length,
							   volatile uint8_t **flag)
{
	if (uart_inst == UART_0_INST)
	{
		*buffer = recv0_buff;
		*length = &recv0_length;
		*flag = &recv0_flag;
	}
	else if (uart_inst == UART_1_INST)
	{
		*buffer = recv1_buff;
		*length = &recv1_length;
		*flag = &recv1_flag;
	}
	else
	{
		return 0; // 无效的串口实例
	}
	return 1;
}

/**
 * @brief 清除串口接收缓冲区
 * @param uart_inst 串口实例
 */
void uart_clear_buffer(UART_Regs *uart_inst)
{
	volatile uint8_t *buffer;
	volatile uint16_t *length;
	volatile uint8_t *flag;

	if (uart_get_received_data(uart_inst, &buffer, &length, &flag))
	{
		memset((void *)buffer, 0, RE_0_BUFF_LEN_MAX);
		*length = 0;
		*flag = 0;
	}
}

/**
 * @brief 检查串口是否有数据接收
 * @param uart_inst 串口实例
 * @return 1:有数据 0:无数据
 */
uint8_t uart_data_available(UART_Regs *uart_inst)
{
	volatile uint8_t *flag;
	volatile uint16_t *length;
	volatile uint8_t *buffer;

	if (uart_get_received_data(uart_inst, &buffer, &length, &flag))
	{
		return *flag;
	}
	return 0;
}

#if !defined(__MICROLIB)
// 不使用微库的话就需要添加下面的函数，
// 我们采用的是不用微库+ac6编译
#if (__ARMCLIB_VERSION <= 6000000)
// 如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

// printf函数重定义 - 默认使用UART_0
int fputc(int ch, FILE *stream)
{
	// 当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while (DL_UART_isBusy(UART_0_INST) == true)
		;

	DL_UART_Main_transmitData(UART_0_INST, ch);

	return ch;
}

// UART_0 中断服务函数
void UART_0_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;

	// 如果产生了串口中断
	switch (DL_UART_getPendingInterrupt(UART_0_INST))
	{
	case DL_UART_IIDX_RX: // 如果是接收中断
		// 接收发送过来的数据保存
		receivedData = DL_UART_Main_receiveData(UART_0_INST);

		// 检查缓冲区是否已满
		if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
		{
			recv0_buff[recv0_length++] = receivedData;

			// 将保存的数据再发送出去，不想回传可以注释掉
			// uart0_send_char(receivedData);
		}
		else
		{
			recv0_length = 0;
		}

		// 标记接收标志
		recv0_flag = 1;
		break;

	default: // 其他的串口中断
		break;
	}
}

// UART_1 中断服务函数
void UART_1_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;

	// 如果产生了串口中断
	switch (DL_UART_getPendingInterrupt(UART_1_INST))
	{
	case DL_UART_IIDX_RX: // 如果是接收中断
		// 接收发送过来的数据保存
		receivedData = DL_UART_Main_receiveData(UART_1_INST);

		// 检查缓冲区是否已满
		if (recv1_length < RE_1_BUFF_LEN_MAX - 1)
		{
			recv1_buff[recv1_length++] = receivedData;

			// 将保存的数据再发送出去，不想回传可以注释掉
			// uart1_send_char(receivedData);
		}
		else
		{
			recv1_length = 0;
		}

		// 标记接收标志
		recv1_flag = 1;
		break;

	default: // 其他的串口中断
		break;
	}
}
