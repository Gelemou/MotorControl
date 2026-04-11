#include "bsp_pid.h"

// 初始化参数
void PID_Init(PID_TypeDef* pid, float p, float i, float d, float max_out,
              float max_i) {
    pid->Kp = p;
    pid->Ki = i;
    pid->Kd = d;
    pid->MaxOutput = max_out;
    pid->MaxIntegral = max_i;
    pid->Integral = 0;
    pid->LastError = 0;
}

// 核心计算函数
float PID_Compute(PID_TypeDef* pid, float target, float measure) {
    pid->Target = target;
    pid->Measure = measure;
    pid->Error = target - measure;  // 计算误差

    // 1. P 比例项
    float p_out = pid->Kp * pid->Error;

    // 2. I 积分项（带限幅，防止饱和）
    pid->Integral += pid->Error;
    if (pid->Integral > pid->MaxIntegral) pid->Integral = pid->MaxIntegral;
    if (pid->Integral < -pid->MaxIntegral) pid->Integral = -pid->MaxIntegral;
    float i_out = pid->Ki * pid->Integral;

    // 3. D 微分项
    float d_out = pid->Kd * (pid->Error - pid->LastError);
    pid->LastError = pid->Error;

    // 总输出
    pid->Output = p_out + i_out + d_out;

    // 输出限幅（防止 PWM 超过最大范围）
    if (pid->Output > pid->MaxOutput) pid->Output = pid->MaxOutput;
    if (pid->Output < -pid->MaxOutput) pid->Output = -pid->MaxOutput;

    return pid->Output;
}
