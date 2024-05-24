/*
 * @Author: 都建民
 * @Date: 2024-03-20 00:16:12
 * @Last Modified by: dujianmin qq群 26875961
 * @Last Modified time: 2024-03-20 01:36:39
 */
#include "app_i2c.h"
#define I2C_SCL (GPIO_NUM_18)
#define I2C_SDA (GPIO_NUM_17)
#define I2C_NUM 0
static const char *TAG = "MY_I2C";

esp_err_t my_i2c_init(void)
{

    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 17,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = 18,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000};

    ESP_RETURN_ON_ERROR(i2c_param_config(0, &i2c_conf), TAG, "I2C configuration failed");
    ESP_RETURN_ON_ERROR(i2c_driver_install(0, i2c_conf.mode, 0, 0, 0), TAG, "I2C initialization failed");

    return ESP_OK;
}
