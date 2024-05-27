#ifndef __DU_LED__
#define __DU_LED__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
/* Lights control pin */
#define LEFT_LED_PIN 8     // Left turn signal control pin
#define RIGHT_LED_PIN 9    // Right turn signal control pin
#define BRAKE_LED_PIN 5    // Brake light control pin
#define REVERSE_LED_PIN 40 // Reverse light control pin
#define LED_STRIP_GPIO GPIO_NUM_42
void app_led_init(void);
void light_gpio_init(void);
void app_led_set_color(uint8_t red, uint8_t green, uint8_t blue);
void light_control_task(void *pvParameters);
#endif