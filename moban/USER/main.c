#include "A_include.h"

int main(void)
{
    SYSCFG_DL_init();
    USART_Init();
    u8 t = 0;
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    while (1)
    {
        LED_Test();
        delay_ms(1000);

         OLED_Clear();
       OLED_Refresh();
        OLED_ShowString(8, 16, "ZHONGJINGYUAN", 16, 1);
        OLED_ShowString(20, 32, "2025/07/17", 16, 1);
        OLED_ShowString(0, 48, "ASCII:", 16, 1);
        OLED_ShowString(63, 48, "CODE:", 16, 1);
        OLED_ShowChar(48, 48, t, 16, 1); // 显示ASCII字符
        t++;
        if (t > '~')
            t = ' ';
        OLED_ShowNum(103, 48, t, 3, 16, 1);
        OLED_Refresh();
        printf("刷新%d次\n", t);
    }
}