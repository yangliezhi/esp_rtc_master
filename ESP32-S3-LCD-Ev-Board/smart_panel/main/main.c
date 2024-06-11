/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-06-05 19:12:09
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-06-05 20:33:40
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_check.h"
#include "nvs_flash.h"

#include "ui_main.h"

#include "bsp_board_extra.h"
#include "bsp/esp-bsp.h"
#include "settings.h"

#include "app_wifi.h"
#include "app_weather.h"

#define LOG_MEM_INFO 0

static char *TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "system start");

    // Initialize NVS.
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(settings_read_parameter_from_nvs());

    bsp_spiffs_mount();

    bsp_extra_codec_init();
    bsp_extra_player_init(BSP_SPIFFS_MOUNT_POINT "/Music");

    bsp_display_start();

    app_weather_start();
    app_network_start();

    ESP_LOGI(TAG, "Display LVGL demo");
    ui_main();

    sys_param_t *sys_set = settings_get_parameter();
    while (true == sys_set->need_hint) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    if (sys_set->sr_enable) {
        ESP_LOGI(TAG, "speech recognition Enable");
        app_sr_start(false);
        bsp_audio_poweramp_enable(true);
    } else {
        ESP_LOGI(TAG, "speech recognition Disable");
    }
}
