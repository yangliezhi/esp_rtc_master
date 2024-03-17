
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// 摄像头组件
#include "esp_camera.h"
#include "lvgl_camera.h"
// LCD屏幕组件
#include "app_lcd.h"
#include "gui_guider.h"
// 按键组件
#include "app_button.h"

// 声音麦克风组件
#include "my_audio_player.h"
#include "ui_audio.h"
#include "audio_player.h"

static const char *TAG = "MAIN";

QueueHandle_t audio_button_q = NULL;
lv_ui guider_ui;

void button_task(void)
{

    while (1)
    {
        int btn_index = 0;
        if (xQueueReceive(audio_button_q, &btn_index, portMAX_DELAY) == pdTRUE)
        {
            switch (btn_index)
            {
            case BSP_BUTTON_REC:
            {
                my_lcd_led(1);
                play_index(0);
                // my_lcd_led(0);
                break;
            }
            case BSP_BUTTON_MUTE:
            {

                break;
            }
            case BSP_BUTTON_SET:
            {

                break;
            }
            case BSP_BUTTON_PLAY:
            {
                my_lcd_led(1);
                play_index(0);
                break;
            }
            case BSP_BUTTON_VOLDOWN:
            {

                break;
            }
            case BSP_BUTTON_VOLUP:
            {

                break;
            }
            default:
                ESP_LOGI(TAG, "No function for this button");
                break;
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{

    /* Create FreeRTOS tasks and queues */
    audio_button_q = xQueueCreate(10, sizeof(int));

    // 屏幕组件
    app_lcd_run();
    setup_ui(&guider_ui);
    // // 声音组件
    my_audio_play_test();
    play_index(0);
    my_lcd_led(1);
    // 摄像头组件
    xTaskCreate(Cam_Task, "camera_task", 1024 * 4, NULL, 1, NULL);
    // 按键组件
    esp32_s3_adc_button();
    xTaskCreate(button_task, "button_task", 1024 * 4, NULL, 1, NULL);

    
}
