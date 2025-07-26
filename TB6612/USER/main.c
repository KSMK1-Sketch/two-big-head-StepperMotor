#include "A_include.h"

float deP = 10.1, deI = 3.2, deD = 0;//增量式PID
float poP = 10.1, poI = 3.2, poD = 0;//位置式PID
bool flag = true;
int sp = 00;
int po = 0;

int main(void)
{
    SYSCFG_DL_init();
    USART_Init();

    OLED_Init();
    OLED_ColorTurn(0);   // 0正常显示，1 反色显示
    OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    pid_init(&motorA, DELTA_PID, deP, deI, deD);
    pid_init(&motorB, POSITION_PID, poP, poI, poD);
    TB6612_Motor_Stop();
    Encoder_Init();

    while (1)
    {
        motor_target_set(sp, po);
        // LED_Test();
        delay_ms(10);
        send_wave();
    }
}
