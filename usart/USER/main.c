#include "A_include.h"

int main(void)
{
    SYSCFG_DL_init();
    USART_Init();
    u8 t = 0;
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    // 通过UART_0发送初始化信息
    uart0_send_string("MSP430G3507 Multi-UART Test\r\n");
    uart0_send_string("UART_0: PA10(TX), PA11(RX)\r\n");

    // 通过UART_1发送初始化信息
    uart1_send_string("UART_1: PA23(TX), PA24(RX)\r\n");
    uart1_send_string("System initialized successfully!\r\n");

    while (1)
    {
        LED_Test();
        delay_ms(1000);

        // UART_0发送测试数据
        uart0_send_char('A' + (t % 26));
        uart0_send_string(" - UART_0 Test\r\n");

        // UART_1发送测试数据
        uart1_send_char('a' + (t % 26));
        uart1_send_string(" - UART_1 Test\r\n");

        t++;

        // 检查串口接收数据
        if (uart_data_available(UART_0_INST))
        {
            uart0_send_string("UART_0 received data!\r\n");
            uart_clear_buffer(UART_0_INST);
        }

        if (uart_data_available(UART_1_INST))
        {
            uart1_send_string("UART_1 received data!\r\n");
            uart_clear_buffer(UART_1_INST);
        }

        // OLED显示测试代码（已注释）
        // OLED_Clear();
        // OLED_Refresh();
        // OLED_ShowString(8, 16, "ZHONGJINGYUAN", 16, 1);
        // OLED_ShowString(20, 32, "2025/07/17", 16, 1);
        // OLED_ShowString(0, 48, "ASCII:", 16, 1);
        // OLED_ShowString(63, 48, "CODE:", 16, 1);
        // OLED_ShowChar(48, 48, t, 16, 1); // 显示ASCII字符
        // t++;
        // if (t > '~')
        //     t = ' ';
        // OLED_ShowNum(103, 48, t, 3, 16, 1);
        // OLED_Refresh();
        // printf("刷新%d次\n", t);
    }
}