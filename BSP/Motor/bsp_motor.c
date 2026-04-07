#include "bsp_motor.h"

extern TIM_HandleTypeDef htim1;

void Motor_Init(Motor_TypeDef* motor) {
    motor->target_speed = 0;
    motor->current_speed = 0;
    motor->pulse_count = 0;
    motor->is_running = 0;
}

void Motor_Loop(Motor_TypeDef* motor) {
    if (motor->is_running) {
        float pwm_val = motor->target_speed * 10.0f;

        // 限制最大占空比
        if (pwm_val > 1000) pwm_val = 1000;

        // 写入硬件寄存器
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t)pwm_val);
    } else {
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    }
}