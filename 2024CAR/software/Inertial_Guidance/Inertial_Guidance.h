#ifndef __Inertial_Guidance_H__
#define __Inertial_Guidance_H__

#include "A_include.h"

// ======================== 系统配置 ========================
#define MAX_WAYPOINTS 200          // 最大路径点数
#define WAYPOINT_INTERVAL_CM 10.0f // 路径点间隔(cm)
#define COUNTS_PER_CM 850.0f       // 每厘米编码器计数 (需校准)
#define BASE_SPEED 5               // 基础速度值
#define MIN_SPEED 1                // 最小速度值
#define MAX_MOTOR_SPEED 10         // 最大电机速度
// PID
#define STEERING_PID_KP 0.3f     // 转向PID比例系数
#define STEERING_PID_KI 0.0f     // 转向PID积分系数
#define STEERING_PID_KD 0.02f    // 转向PID微分系数
#define MAX_STEERING_ANGLE 60.0f // 最大转向角度(度)
// 差速转向参数
#define DIFF_GAIN 1.0f    // 差速增益系数 (需校准)
#define MAX_DIFF_SPEED 10 // 最大差速值
// 新增位置控制参数
#define POSITION_CONTROL_ENABLED 1    // 启用位置闭环控制
#define WAYPOINT_REACH_THRESHOLD 5.0f // 到达路径点的距离阈值(CM)
#define POSITION_KP 0.8f              // 位置控制比例系数
#define MAX_HEADING_ERROR 30.0f       // 最大航向误差容限(度)
// ======================== 类型定义 ========================
typedef struct
{
    float heading;    // 航向角(度)
    float position_x; // X坐标(可选)
    float position_y; // Y坐标(可选)
} Waypoint;

typedef enum
{
    MODE_IDLE,      // 空闲模式
    MODE_RECORDING, // 路径记忆模式
    MODE_REPLAYING  // 路径复现模式
} SystemMode;

// ======================== 函数声明 ========================
void PathSystem_Init(void);
void PathSystem_StartRecording(void);
void PathSystem_StopRecording(void);
void PathSystem_StartReplay(void);
void PathSystem_StopReplay(void);
void steering_control(float target_heading);
void set_steering_angle(float angle);
void set_motor_speed(int left, int right);
float IMU_GetHeading(void);
int32_t get_left_encoder(void);
int32_t get_right_encoder(void);
float constrain(float value, float min_val, float max_val);
uint8_t Get_current_speed();
void position_control(void);
static float normalize_angle(float angle);
#endif