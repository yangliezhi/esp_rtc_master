
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
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
static const char *TAG = "MAIN";

QueueHandle_t audio_button_q = NULL;
lv_ui guider_ui;

static bool i2c_initialized = false;
static esp_err_t my_i2c_init()
{
    /* I2C was initialized before */
    if (i2c_initialized)
    {
        return ESP_OK;
    }

    /* Initilize I2C */
    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = EXAMPLE_TOUCH_I2C_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = EXAMPLE_TOUCH_I2C_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000};

    ESP_RETURN_ON_ERROR(i2c_param_config(EXAMPLE_TOUCH_I2C_NUM, &i2c_conf), TAG, "I2C configuration failed");
    ESP_RETURN_ON_ERROR(i2c_driver_install(EXAMPLE_TOUCH_I2C_NUM, i2c_conf.mode, 0, 0, 0), TAG, "I2C initialization failed");
    i2c_initialized = true;
    return ESP_OK;
}
static void button_task(void)
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
    // 按键组件
    esp32_s3_adc_button();
    xTaskCreate(button_task, "button_task", 1024 * 4, NULL, 1, NULL);
    my_i2c_init();
    // 屏幕组件
    app_lcd_run();
    setup_ui(&guider_ui);
    // // 声音组件
    my_audio_play_test();
    play_index(0);
    // 摄像头组件
    xTaskCreate(Cam_Task, "camera_task", 1024 * 4, NULL, 1, NULL);
}
