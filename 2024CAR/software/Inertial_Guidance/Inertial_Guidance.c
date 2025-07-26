#include "Inertial_Guidance.h"


// ======================== 全局变量 ========================
// 路径数据
Waypoint waypoints[MAX_WAYPOINTS]; // 路径点数组
volatile uint32_t wp_count = 0;     // 当前路径点数
volatile uint32_t replay_index = 0; // 复现路径点索引

// 系统状态
volatile SystemMode current_mode = MODE_IDLE;

// 编码器状态
volatile int32_t last_left_encoder = 0;
volatile int32_t last_right_encoder = 0;
volatile float accumulated_distance = 0.0f; // 累计位移(cm)

// 航向管理
volatile float total_heading = 0.0f; // 多圈累积航向
volatile float last_heading = 0.0f;  // 上一次航向

// PID控制器状态
float prev_heading_error = 0.0f;
float heading_error_integral = 0.0f;

// 位置跟踪
volatile float current_position_x = 0.0f;
volatile float current_position_y = 0.0f;

// 差速转向状态
float current_steering_angle = 0.0f;
int current_base_speed = BASE_SPEED;

static Gyro_Struct * Yaw;
// ======================== 初始化函数 ========================
void PathSystem_Init(void)
{   
    // 初始化IMU
    jy61pInit();
    
    //初始化中断
     // 定时器中断
    NVIC_ClearPendingIRQ(TIMER_GD_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_GD_INST_INT_IRQN);

    // 重置系统状态
    wp_count = 0;
    replay_index = 0;
    current_mode = MODE_IDLE;
    total_heading = 0.0f;
    accumulated_distance = 0.0f;
}

// ======================== 定时器中断处理 ========================
void TIMER_GD_INST_IRQHandler(void)
{
    
    // 1. 读取编码器值
    int32_t left_encoder = get_left_encoder();
    int32_t right_encoder = get_right_encoder();
    
    // 2. 计算位移增量
    float delta_left = (float)(left_encoder - last_left_encoder);
    float delta_right = (float)(right_encoder - last_right_encoder);
    float delta_distance = (delta_left + delta_right) / 2.0f;
    float delta_dist_cm = delta_distance / COUNTS_PER_CM;
    // 3. 更新累计位移 (转换为cm)
    accumulated_distance += delta_dist_cm;

    // 4. 获取当前航向(弧度制)
    float current_heading_deg = IMU_GetHeading();
    float current_heading_rad = current_heading_deg * 3.1415926 / 180.0f;
    
    // 5. 更新当前位置(新增的位置跟踪)
    current_position_x += delta_dist_cm * cosf(current_heading_rad);
    current_position_y += delta_dist_cm * sinf(current_heading_rad);
    // 6. 检查是否达到路径点间隔
    if (accumulated_distance >= WAYPOINT_INTERVAL_CM && current_mode == MODE_RECORDING) {
        accumulated_distance -= WAYPOINT_INTERVAL_CM; // 保留余数
        if (wp_count < MAX_WAYPOINTS) {
            waypoints[wp_count].heading = current_heading_deg;
            waypoints[wp_count].position_x = current_position_x;
            waypoints[wp_count].position_y = current_position_y;
            wp_count++;
        }
    }
        // 路径复现模式
        if (current_mode == MODE_REPLAYING) {
            // 位置闭环控制(新增)
            position_control();
            // 检查是否到达路径点(距离阈值判断)
            float dx = waypoints[replay_index].position_x - current_position_x;
            float dy = waypoints[replay_index].position_y - current_position_y;
            float dist_to_target = sqrtf(dx*dx + dy*dy);
            // 检查是否到达路径点
        if (dist_to_target < WAYPOINT_REACH_THRESHOLD) {
            if (replay_index < wp_count - 1) {
                replay_index++; // 前往下一个路径点
                // 重置累计距离以进行下一段航向插值
                accumulated_distance = 0.0f;
            } else {
                PathSystem_StopReplay(); // 到达终点
            }
        }
        }
    
    // 5. 更新历史值
    last_left_encoder = left_encoder;
    last_right_encoder = right_encoder;
}
// ======================== 新增: 位置闭环控制函数 ========================
void position_control(void)
{
    if (replay_index >= wp_count) return;
    
    // 1. 确保在航向插值范围内 (replay_index至少为1才能插值)
    float target_heading;
    if (replay_index >= 1) {
        // 获取前后两个路径点的航向
        float prev_yaw = waypoints[replay_index-1].heading;
        float next_yaw = waypoints[replay_index].heading;
        
        // 确保路径点在-180~180度范围内
        prev_yaw = normalize_angle(prev_yaw);
        next_yaw = normalize_angle(next_yaw);
        
        // 计算当前段已行驶的比例 (限制在0~1范围)
        float ratio = constrain(accumulated_distance / WAYPOINT_INTERVAL_CM, 0.0f, 1.0f);
        
        // 航向插值算法
        float angle_diff = next_yaw - prev_yaw;
        
        // 处理360°边界情况
        if (angle_diff > 180.0f) angle_diff -= 360.0f;
        if (angle_diff < -180.0f) angle_diff += 360.0f;
        
        // 执行线性插值
        target_heading = prev_yaw + ratio * angle_diff;
        
        // 限幅最终结果
        target_heading = normalize_angle(target_heading);
    } else {
        // 第一个点没有前一个点可插值，使用路径点的实际航向
        target_heading = normalize_angle(waypoints[replay_index].heading);
    }
    
    // 2. 计算目标点方向
    float target_x = waypoints[replay_index].position_x;
    float target_y = waypoints[replay_index].position_y;
    float dx = target_x - current_position_x;
    float dy = target_y - current_position_y;
    
    // 3. 计算期望航向 (atan2得到弧度值，转为角度)
    float desired_heading = atan2f(dy, dx) * 180.0f / 3.1415926;
    
    // 4. 计算当前位置到目标的距离
    float distance_error = sqrtf(dx*dx + dy*dy);
    
    // 5. 航向控制(考虑距离因素)
    float heading_correction = POSITION_KP * distance_error;
    heading_correction = constrain(heading_correction, -MAX_HEADING_ERROR, MAX_HEADING_ERROR);
    
    // 6. 应用航向修正：基础插值航向 + 距离修正项
    steering_control(target_heading + heading_correction);
}


// ======================== 路径记忆控制 ========================
void PathSystem_StartRecording(void)
{
    if (current_mode != MODE_IDLE) return;
    
    // 重置状态
    wp_count = 0;
    accumulated_distance = 0.0f;
    total_heading = 0.0f;
    last_heading = IMU_GetHeading();
    current_position_x = 0.0f;
    current_position_y = 0.0f;
    
    // 设置模式
    current_mode = MODE_RECORDING;
    
    // 启动车辆
    set_motor_speed(BASE_SPEED, BASE_SPEED);
}

void PathSystem_StopRecording(void)
{
    if (current_mode != MODE_RECORDING) return;
    
    // 停止车辆
    set_motor_speed(0, 0);
    
    // 设置模式
    current_mode = MODE_IDLE;
}

// ======================== 路径复现控制 ========================
void PathSystem_StartReplay(void)
{
    if (current_mode != MODE_IDLE || wp_count == 0) return;
    
    // 重置状态
    replay_index = 0;
    accumulated_distance = 0.0f;
    total_heading = 0.0f;
    last_heading = IMU_GetHeading();
    current_position_x = 0.0f;
    current_position_y = 0.0f;
    
    // 设置模式
    current_mode = MODE_REPLAYING;
    
    // 控制车辆转向第一个路径点
    steering_control(waypoints[0].heading);
    
    // 启动车辆
    set_motor_speed(BASE_SPEED, BASE_SPEED);
}

void PathSystem_StopReplay(void)
{
    if (current_mode != MODE_REPLAYING) return;
    
    // 停止车辆
    set_motor_speed(0, 0);
    
    // 设置模式
    current_mode = MODE_IDLE;
}

// ======================== 转向控制函数 ========================
void steering_control(float target_heading)
{
    // 1. 获取当前航向
    float current_heading = IMU_GetHeading();
    
    // 2. 计算航向误差
    float error = target_heading - current_heading;
    
    // 3. 归一化角度误差 (-180°到180°)
    while (error > 180.0f) error -= 360.0f;
    while (error < -180.0f) error += 360.0f;
    
    // 4. PID控制计算
    float derivative = error - prev_heading_error;
    heading_error_integral += error;
    
    // 积分限幅
    if (heading_error_integral > 100.0f) heading_error_integral = 100.0f;
    if (heading_error_integral < -100.0f) heading_error_integral = -100.0f;
    
    // PID输出
    float steer_output = STEERING_PID_KP * error + 
                         STEERING_PID_KI * heading_error_integral + 
                         STEERING_PID_KD * derivative;
    
    // 5. 输出限幅
    if (steer_output > MAX_STEERING_ANGLE) steer_output = MAX_STEERING_ANGLE;
    if (steer_output < -MAX_STEERING_ANGLE) steer_output = -MAX_STEERING_ANGLE;
    
    // 6. 应用转向
    set_steering_angle(steer_output);
    
    // 7. 保存误差用于下次计算
    prev_heading_error = error;
}

// ======================== 差速转向函数 ========================
void set_steering_angle(float angle)
{
    // 保存当前角度
    current_steering_angle = angle;
    
    // 1. 计算转向修正量
    float diff_speed = angle * DIFF_GAIN;
    
    // 2. 限制差速范围
    diff_speed = constrain(diff_speed, -MAX_DIFF_SPEED, MAX_DIFF_SPEED);
    
    // 3. 计算左右轮速度
   // 3. 计算左右轮速度 - 使用传入的基础速度
    int left_speed = (int)(BASE_SPEED - diff_speed);
    int right_speed = (int)(BASE_SPEED + diff_speed);
    
    // 4. 确保最小速度
    if (abs(left_speed) < MIN_SPEED) {
        left_speed = (left_speed > 0) ? MIN_SPEED : -MIN_SPEED;
    }
    if (abs(right_speed) < MIN_SPEED) {
        right_speed = (right_speed > 0) ? MIN_SPEED : -MIN_SPEED;
    }
    
    // 5. 限制最大速度
    left_speed = constrain(left_speed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    right_speed = constrain(right_speed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    
    // 6. 应用电机速度
    set_motor_speed(left_speed, right_speed);
}


// ======================== 硬件抽象层 (需根据实际硬件实现) ========================

// 设置电机速度
void set_motor_speed(int left, int right)
{
    motor_target_set(left,right);
}

uint8_t Get_current_speed()
{
    int32_t left_encoder = Encoder_Getcount(1);
    int32_t right_encoder = Encoder_Getcount(2);
    return (left_encoder + right_encoder)/2;
}

// 获取IMU航向角
float IMU_GetHeading(void)
{
     Yaw = get_angle();
    return Yaw->z;
}

// 获取左编码器值
int32_t get_left_encoder(void)
{
    // 实现左编码器读取
    return Encoder_Getcountdistance(1); // 示例
}

// // 获取右编码器值
int32_t get_right_encoder(void)
{
    // 实现右编码器读取
    return Encoder_Getcountdistance(2); // 示例
}

// ======================== 辅助函数 ========================
float constrain(float value, float min_val, float max_val)
{
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

static float normalize_angle(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}