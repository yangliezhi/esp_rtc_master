#ifndef __BSP_GPIO_OUT__
#define __BSP_GPIO_OUT__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

/* 引脚定义 */
#define LED_GPIO_PIN GPIO_NUM_47 /* LED连接的GPIO端口 */

/* 引脚的输出的电平状态 */
enum GPIO_OUTPUT_STATE
{
    PIN_RESET,
    PIN_SET
};

/* LED端口定义 */
#define LED(x)                                                                               \
    do                                                                                       \
    {                                                                                        \
        x ? gpio_set_level(LED_GPIO_PIN, PIN_SET) : gpio_set_level(LED_GPIO_PIN, PIN_RESET); \
    } while (0) /* LED翻转 */

/* LED取反定义 */
#define LED_TOGGLE()                                                 \
    do                                                               \
    {                                                                \
        gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); \
    } while (0) /* LED翻转 */

/* 函数声明*/
void led_init(void); /* 初始化LED */

#endif