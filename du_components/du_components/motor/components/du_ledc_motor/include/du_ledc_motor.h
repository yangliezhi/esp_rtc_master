#ifndef __DU_LEDC_MOTOR__
#define __DU_LEDC_MOTOR__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

// dc_motor

#define PWM_TIMER LEDC_TIMER_0
#define PWM_MODE LEDC_LOW_SPEED_MODE
#define PWM_INTR_TYPE LEDC_INTR_DISABLE
#define PWM_CLK_TYPE LEDC_AUTO_CLK
#define PWM_DUTY_RES LEDC_TIMER_10_BIT // Set duty resolution to 13 bits
#define PWM_FREQUENCY (50)             // Frequency in Hertz. Set frequency at 5 kHz

// dc_gpio
#define motor1_left_a 2
#define motor1_left_b 3
#define motor1_right_a 4
#define motor1_right_b 5

#define servo1_gpio 6

void example_pwm_init(void);
void remote_control(int ch1_value, int ch2_value, int ch3_value, int ch4_value, int ch5_value, int ch6_value, int ch7_value, int ch8_value);
void du_remote_control(int ch1_value, int ch2_value, int ch3_value, int ch4_value, int ch5_value, int ch6_value, int ch7_value, int ch8_value);
#endif