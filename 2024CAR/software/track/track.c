#include "track.h"
u8 x1, x2, x3, x4, x5, x6, x7, x8;
bool mode2_flag = false;

void track_init()
{
	// 定时器中断
	NVIC_ClearPendingIRQ(TIMER_1_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
}

static int white_area_cnt = 0;

void mode2_check()
{
	static int cur_mode2 = 0;
	static int last_mode2 = 0;
	static int mode2_count = 0;

	if ((x1 == 1) && (x2 == 1) && (x3 == 1) && (x4 == 1) &&
		(x5 == 1) && (x6 == 1) && (x7 == 1) && (x8 == 1))
	{
		white_area_cnt++;
		if (white_area_cnt >= 5)
		{ // 连续3次全为1才算空白区
			cur_mode2 = 1;
		}
	}
	else
	{
		white_area_cnt = 0;
		cur_mode2 = 0;
	}

	if ((cur_mode2 != last_mode2) && cur_mode2 == 0)
	{
		mode2_flag = !mode2_flag;
	}

	last_mode2 = cur_mode2;
}

void TIMER_1_INST_IRQHandler(void)
{
	mode2_check();
}

void track() // 1234 5678
{

	deal_IRdata(&x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
	printf("x1=%d,x2=%d,x3=%d,x4=%d,x5=%d,x6=%d,x7=%d,x8=%d\n", x1, x2, x3, x4, x5, x6, x7, x8);
	if ((x1 == 0) | (x2 == 0))
	{
		motor_target_set(3, 9);
	}
	else if ((x7 == 0) | (x8 == 0))
	{
		motor_target_set(9, 3);
	}
	else if ((x3 == 0) | (x4 == 0))
	{
		motor_target_set(2, 6);
	}
	else if ((x5 == 0) | (x6 == 0))
	{
		motor_target_set(6, 2);
	}
	else if ((x1 == 1) && (x2 == 1) && (x3 == 1) && (x4 == 1) && (x5 == 1) && (x6 == 1) && (x7 == 1) && (x8 == 1)) // 1111 1111
	{
		motor_target_set(8, 8);
		if (white_area_cnt == 0 || white_area_cnt >= 5)
		{
			if (mode2_flag == false)
			{
				steering_control(0);
			}
			else
			{
				steering_control(180);
			}
		}
	}
	else
	{
		motor_target_set(8, 8);
	}
}