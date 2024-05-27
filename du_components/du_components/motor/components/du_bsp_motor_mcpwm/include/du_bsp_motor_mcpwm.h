/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-04-26 01:22:27
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-04-26 01:32:53
 */
#ifndef __DU_BSP_MOTOR_MCPWM__
#define __DU_BSP_MOTOR_MCPWM__
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"
#include "driver/gpio.h"

#define EXAMPLE_TIMER_RESOLUTION_HZ 1000000 // 1MHz, 1us per tick
#define EXAMPLE_TIMER_PERIOD 1000           // 1000 ticks, 1ms
#define EXAMPLE_GEN_GPIO0 6
#define EXAMPLE_GEN_GPIO1 19
#define EXAMPLE_GEN_GPIO2 20
#define EXAMPLE_GEN_GPIO3 48
typedef struct
{
    uint32_t values[4];
} MotorSpeeds;
void du_set_motor_speed(const MotorSpeeds *speeds);
void du_bsp_mcpwm_init(void);
#endif