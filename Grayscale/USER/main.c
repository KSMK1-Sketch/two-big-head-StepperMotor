#include "A_include.h"

int main(void)
{
    SYSCFG_DL_init();
    USART_Init();
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    printf("start\r\n");

    IRI2C_WriteByte(0x01, 1); // 控制进入校准
    delay_ms(200);
    IRI2C_WriteByte(0x01, 0); // 控制退出校准
    delay_ms(200);

    printf("okok\r\n");

    while (1)
    {

        printf_i2c_data();
        delay_ms(500);
    }
}