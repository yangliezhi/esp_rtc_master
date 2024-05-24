/*
 * @Author: 都建民 
 * @Date: 2024-03-20 00:42:43 
 * @Last Modified by:   dujianmin qq群 26875961 
 * @Last Modified time: 2024-03-20 00:42:43 
 */
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/i2c.h"
#include "driver/gpio.h"

#include "esp_lvgl_port.h"

#include "app_lcd.h"

void app_lcd_run(void)
{
    // /* LCD HW initialization */
    ESP_ERROR_CHECK(app_lcd_init());

    // // /* Touch initialization */
    ESP_ERROR_CHECK(app_touch_init());

    // /* LVGL initialization */
    ESP_ERROR_CHECK(app_lvgl_init());
}