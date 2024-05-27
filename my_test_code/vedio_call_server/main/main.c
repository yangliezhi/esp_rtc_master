/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-05-27 02:04:37
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-27 02:28:26
 */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "nvs_flash.h"

#include "du_bsp_wifi_sta.h"
#include "du_bsp_audio_record.h"
#include "du_bsp_udp_server.h"
#include "du_bsp_lvgl_camera.h"
#include "du_bsp_lcd.h"
#include "du_bsp_button.h"
static const char *TAG = "main";

static void main_init(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    wifi_init_sta();
}
void app_main(void)
{
    main_init();
    // 按键功能
    esp32_s3_adc_button();
    multimedia_data_t *receive_video_audio = malloc(sizeof(multimedia_data_t)); // 分配内存给 av_stream_frame_t 结构体指针
    if (receive_video_audio != NULL)
    {
        // 分配成功
        // 现在可以初始化结构体成员了
        receive_video_audio->video_data = (uint8_t *)heap_caps_malloc(320 * 240 * 2, MALLOC_CAP_SPIRAM);
        receive_video_audio->audio_data = (uint8_t *)malloc(1 * 1024);
        receive_video_audio->video_len = 0;
        receive_video_audio->audio_len = 0;
    }
    else
    {
        return;
    }
    // 麦克风和喇叭初始化
    audio_recorded_init();
    // 屏幕初始化
    du_bsp_lcd_init();
    // 摄像头初始化
    init_camera();
    // udp服务端任务函数
    xTaskCreate(udp_server_task, "udp_server", 1024 * 10, receive_video_audio, 5, NULL);
}
