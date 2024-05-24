/*
 * @Author: 都建民 
 * @Date: 2024-03-20 16:47:22 
 * @Last Modified by: dujianmin qq群 26875961
 * @Last Modified time: 2024-03-20 16:53:11
 */
#include "app_peripheral.h"

static const char *TAG = "peephole";
esp_err_t bsp_spiffs_mount(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = true,

    };

    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);

    size_t total = 0, used = 0;
    ret_val = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret_val != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret_val));
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return ret_val;
}


static esp_io_expander_handle_t io_expander = NULL;
static bool is_tca9554_init = false;
void tca9554_init(void)
{
    if (is_tca9554_init)
    {
        return;
    }

    if (ESP_OK == (esp_io_expander_new_i2c_tca9554(0, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, &io_expander)))
    {
        ESP_LOGI("MY_TAG", "设备探测成功，无需额外操作");
    }
    else if (ESP_OK == (esp_io_expander_new_i2c_tca9554(0, ESP_IO_EXPANDER_I2C_TCA9554A_ADDRESS_000, &io_expander)))
    {
        ESP_LOGI("MY_TAG", "尝试另一种地址成功，继续其他操作");
        // 继续后续操作
    }
    else
    {
        ESP_LOGE("MY_TAG", "设备探测失败");
        return; // 最终返回
    }

    esp_io_expander_set_dir(io_expander, IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1 | IO_EXPANDER_PIN_NUM_7, IO_EXPANDER_OUTPUT);

    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_0, 1);
    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_1, 1);
    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_7, 1);
    is_tca9554_init = true;
}