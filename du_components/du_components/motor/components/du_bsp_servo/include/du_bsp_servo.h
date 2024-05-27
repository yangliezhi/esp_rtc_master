#ifndef __DU_BSP_SERVO__
#define __DU_BSP_SERVO__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"


// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500 // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE -90         // Minimum angle
#define SERVO_MAX_DEGREE 90          // Maximum angle

#define SERVO_PULSE_GPIO 0                   // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000 // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD 20000          // 20000 ticks, 20ms



void du_servo_init(void);
void du_set_servo_angle(int angle);

#endif