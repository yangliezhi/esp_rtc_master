#include <stdio.h>
#include "du_bsp_tca9554.h"
#include "esp_io_expander_tca9554.h"
#include "esp_system.h"
#include "esp_check.h"

static esp_io_expander_handle_t io_expander = NULL;
static bool is_tca9554_init = false;
void tca9554_init(void)
{
    if (is_tca9554_init)
    {
        return;
    }

    if (ESP_OK == (esp_io_expander_new_i2c_tca9554(1, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, &io_expander)))
    {
        ESP_LOGI("MY_TAG", "设备探测成功，无需额外操作");
    }
    else if (ESP_OK == (esp_io_expander_new_i2c_tca9554(1, ESP_IO_EXPANDER_I2C_TCA9554A_ADDRESS_000, &io_expander)))
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