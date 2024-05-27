#ifndef __DU_BSP_PWM_MOTOR__
#define __DU_BSP_PWM_MOTOR__

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/pulse_cnt.h"
#include "bdc_motor.h"
#include "pid_ctrl.h"


// Enable this config,  we will print debug formated string, which in return can be captured and parsed by Serial-Studio
#define SERIAL_STUDIO_DEBUG 0

#define BDC_MCPWM_TIMER_RESOLUTION_HZ 10000000                                      // 10MHz, 1 tick = 0.1us
#define BDC_MCPWM_FREQ_HZ 25000                                                     // 25KHz PWM
#define BDC_MCPWM_DUTY_TICK_MAX (BDC_MCPWM_TIMER_RESOLUTION_HZ / BDC_MCPWM_FREQ_HZ) // maximum value we can set for the duty cycle, in ticks
#define BDC_MCPWM_GPIO_A 6
#define BDC_MCPWM_GPIO_B 19

#define BDC_ENCODER_GPIO_A 48
#define BDC_ENCODER_GPIO_B 20
#define BDC_ENCODER_PCNT_HIGH_LIMIT 1000
#define BDC_ENCODER_PCNT_LOW_LIMIT -1000

#define BDC_PID_LOOP_PERIOD_MS 10 // calculate the motor speed every 10ms


void du_bsp_motor_pid_pcnt(void);

#endif