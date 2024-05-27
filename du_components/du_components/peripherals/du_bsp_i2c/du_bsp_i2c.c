#include <stdio.h>
#include "du_bsp_i2c.h"
#include "esp_check.h"

static const char *TAG = "DU_BSP_I2C";
static bool i2c_initialized = false;
esp_err_t du_i2c_init()
{
    /* I2C was initialized before */
    if (i2c_initialized)
    {
        return ESP_OK;
    }

    /* Initilize I2C */
    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = DU_I2C_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = DU_I2C_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000};

    ESP_RETURN_ON_ERROR(i2c_param_config(I2C_NUM, &i2c_conf), TAG, "I2C configuration failed");
    ESP_RETURN_ON_ERROR(i2c_driver_install(I2C_NUM, i2c_conf.mode, 0, 0, 0), TAG, "I2C initialization failed");
    i2c_initialized = true;
    return ESP_OK;
}