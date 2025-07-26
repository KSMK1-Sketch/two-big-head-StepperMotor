#include "A_include.h"

int main(void)
{
    SYSCFG_DL_init();
    USART_Init();
    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    AB_Motor_Stop();
    printf("\nL298N Motor Demo Start...\r\n");
    while (1)
    {
        for (int i = 0; i < 1000; i += 50)
        {

            A_Motor_Control(1, i); // A端电机转动 速度最大1000
            B_Motor_Control(1, i); // B端电机转动 速度最大1000

            printf("Dir[ 1 ]   i[ %d ]\r\n", i);

            delay_ms(500);
        }
        AB_Motor_Stop(); // 停止转动
        delay_ms(1000);

        for (int i = 0; i < 1000; i += 50)
        {
            A_Motor_Control(1, i); // A端电机转动 速度最大1000
            B_Motor_Control(1, i); // B端电机转动 速度最大1000

            printf("Dir[ 0 ]   i[ %d ]\r\n", i);

            delay_ms(500);
        }
        AB_Motor_Stop(); // 停止转动
        delay_ms(1000);
    }
}