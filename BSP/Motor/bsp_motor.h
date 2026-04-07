#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H
#include <stdint.h>

#include "main.h"

typedef struct {
    float target_speed;   // 目标速度
    float current_speed;  // 当前速度
    float pulse_count;    // 模拟编码器脉冲
    uint8_t is_running;   // 运行状态
} Motor_TypeDef;

void Motor_Init(Motor_TypeDef* motor);
void Motor_Loop(Motor_TypeDef* motor);
#endif