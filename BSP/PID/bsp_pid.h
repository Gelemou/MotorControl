#ifndef __BSP_PID_H
#define __BSP_PID_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float Target;   // 目标值（比如你希望电机达到的转速）
    float Measure;  // 测量值（编码器读到的实际转速）

    float Error;      // 本次误差
    float LastError;  // 上次误差
    float Integral;   // 积分累加值

    float Output;       // PID计算后的输出值
    float MaxOutput;    // 输出限幅（比如 PWM 的最大值）
    float MaxIntegral;  // 积分限幅（防止积分过大无法回退）
} PID_TypeDef;

// 函数声明
void PID_Init(PID_TypeDef* pid, float p, float i, float d, float max_out,
              float max_i);
float PID_Compute(PID_TypeDef* pid, float target, float measure);
#endif