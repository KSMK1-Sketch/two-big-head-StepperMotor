#include "A_include.h"

float deP = 15, deI = 3.5, deD = 0;   // 增量式PID
float poP = 10.1, poI = 3.2, poD = 0; // 位置式PID
bool flag = true;
int sp = 10;
int po = 0;
void mode_1()
{
    motor_target_set(0, 0);
    delay_ms(3000);
    motor_target_set(5, 5);
    delay_ms(3400);
    motor_target_set(0, 0);
    while (1) ;
}

int main(void)
{
    SYSCFG_DL_init();
    delay_ms(1000);
    USART_Init();
    pid_init(&motorA, DELTA_PID, deP, deI, deD);
    pid_init(&motorB, DELTA_PID, deP, deI, deD);
    TB6612_Motor_Stop();
    Encoder_Init();
    PathSystem_Init();
    LEDB(1);
    track_init();
    while (1)
    {
        // LED_Test();

        // motor_target_set(sp, sp);
        //   printf("sp1=%d\n",Encoder_Getcount(1));
        //   printf("sp2=%d\n",Encoder_Getcount(2));
        //   printf("sp3=%d\n",Encoder_Getcount(3));
        //   printf("sp4=%d\n",Encoder_Getcount(4));


        // printf_i2c_data();
         track();
        // LEDB(0);
        //  send_wave();

        // mode_1();
    }
}
