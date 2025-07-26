#include "pid.h"

pid_t motorA;
pid_t motorB;
pid_t motorC;
pid_t motorD;

uint8_t motorA_dir = 1; // 0为正转 1为反转
uint8_t motorB_dir = 1; // 0为正转 1为反转
uint8_t motorC_dir = 1; // 0为正转 1为反转
uint8_t motorD_dir = 1; // 0为正转 1为反转

void send_wave(void)
{
	// 定义通道名帧头帧尾
	u8 frameNameHead[] = "AABBCC";
	u8 frameNameEnd[] = "CCBBAA";

	// 定义数据帧头帧尾
	u8 frameDataHead[] = "DDEEFF";
	u8 frameDataEnd[] = "FFEEDD";

	// 定义通道名
	u8 name[] = {"Sp1,Sp2,Tg1,Tg2"};

	// 赋值数据
	float channels[4];
	channels[0] = Encoder_Getcount(1);
	channels[1] = Encoder_Getcount(2);
	channels[2] = motorA.target;
	channels[3] = motorB.target;

	// 通过串口1，向上位机发送数据
	// 下面sizeof(frameNameHead)-1) 中的减1，就是忽略掉frameNameHead字符串最后的 ‘\0’ 字符
	uart0_send_string(frameNameHead);
	uart0_send_string(name);
	uart0_send_string(frameNameEnd);

	uart0_send_string(frameDataHead);
	uart0_send_datas((u8 *)channels, sizeof(channels));
	uart0_send_string(frameDataEnd);
}

void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

void motor_target_set(int spe1, int spe2)
{
	if (spe1 >= 0)
	{
		motorA_dir = 0;
		motorA.target = spe1;
	}
	else
	{
		motorA_dir = 1;
		motorA.target = -spe1;
	}

	if (spe2 >= 0)
	{
		motorB_dir = 0;
		motorB.target = spe2;
	}
	else
	{
		motorB_dir = 1;
		motorB.target = -spe2;
	}

	// if (spe3 >= 0)
	// {
	// 	motorC_dir = 0;
	// 	motorC.target = spe3;
	// }
	// else
	// {
	// 	motorC_dir = 1;
	// 	motorC.target = -spe3;
	// }

	// if (spe4 >= 0)
	// {
	// 	motorD_dir = 0;
	// 	motorD.target = spe4;
	// }
	// else
	// {
	// 	motorD_dir = 1;
	// 	motorD.target = -spe4;
	// }
}

void pid_control()
{
	// 1.设置目标速度
	//	motor_target_set(5, 5);
	// if(mode == 2 |mode == 3 |mode == 4)
	// {
	// 	track();
	// }

	// 2.获取当前速度
	if (motorA_dir)
	{
		motorA.now = -Encoder_Getcount(1);
	}
	else
	{
		motorA.now = Encoder_Getcount(1);
	}
	if (motorB_dir)
	{
		motorB.now = -Encoder_Getcount(2);
	}
	else
	{
		motorB.now = Encoder_Getcount(2);
	}
	// if (motorC_dir){motorC.now = -Encoder_Getcount(3);}else{motorC.now = Encoder_Getcount(3);}
	// if (motorD_dir){motorD.now = -Encoder_Getcount(4);}else{motorD.now = Encoder_Getcount(4);}
	/* 编码器计数值清零 */
	Encoder_Clearcount();
	// 3.输入PID控制器进行计算
	pid_cal(&motorA);
	pid_cal(&motorB);
	// pid_cal(&motorC);
	// pid_cal(&motorD);
	// 电机输出限幅
	pidout_limit(&motorA);
	pidout_limit(&motorB);
	// pidout_limit(&motorC);
	// pidout_limit(&motorD);
	// 4.PID的输出值 输入给电机
	AO_Control(motorA_dir, motorA.out);
	CO_Control(motorA_dir, motorA.out);

	BO_Control(motorB_dir, motorB.out);
	DO_Control(motorB_dir, motorB.out);
}
void pid_cal(pid_t *pid)
{
	// 计算当前偏差
	pid->error[0] = pid->target - pid->now;

	// 计算输出
	if (pid->pid_mode == DELTA_PID) // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if (pid->pid_mode == POSITION_PID) // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}
	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
}

void pidout_limit(pid_t *pid)
{
	// 输出限幅
	if (pid->out >= MAX_DUTY)
		pid->out = MAX_DUTY;
	if (pid->out <= 0)
		pid->out = 0;
}
