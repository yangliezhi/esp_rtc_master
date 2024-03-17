#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_idf_version.h"
#include "esp_log.h"
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "esp_adc/adc_cali.h"
#endif
#include "iot_button.h"
#include "sdkconfig.h"

#include "app_button.h"

static const char *TAG = "BUTTON_ESP32_S3";
extern QueueHandle_t audio_button_q;
#define BUTTON_NUM BSP_BUTTON_NUM
static button_handle_t g_btns[BUTTON_NUM] = {0};
static int get_btn_index(button_handle_t btn)
{
    for (size_t i = 0; i < BUTTON_NUM; i++)
    {
        if (btn == g_btns[i])
        {
            return i;
        }
    }
    return -1;
}

static void button_press_down_cb(void *arg, void *data)
{  
    int btn_index = get_btn_index((button_handle_t)arg);
    xQueueSend(audio_button_q, &btn_index, 0);
    ESP_LOGI(TAG, "BTN%d : BUTTON_PRESS_DOWN", get_btn_index((button_handle_t)arg));
    switch (btn_index)
    {
    case BSP_BUTTON_REC:

        break;
    case BSP_BUTTON_MUTE:
        /* code */
        break;
    case BSP_BUTTON_PLAY:
        /* code */
        break;
    case BSP_BUTTON_SET:
        /* code */
        break;
    case BSP_BUTTON_VOLDOWN:
        /* code */
        break;
    case BSP_BUTTON_VOLUP:
        /* code */
        break;
    default:
        break;
    }
}

void esp32_s3_adc_button(void)
{
    adc_oneshot_unit_handle_t adc1_handle;
    adc_cali_handle_t adc1_cali_handle;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    esp_err_t ret = adc_oneshot_new_unit(&init_config, &adc1_handle);

    // /*!< use atten 11db or 12db */
    // adc_calibration_init(ADC_UNIT_1, 3, &adc1_cali_handle);

    // /** ESP32-S3-Korvo board */
    const uint16_t vol[6] = {380, 820, 1180, 1570, 1980, 2410};
    button_config_t cfg = {0};
    cfg.type = BUTTON_TYPE_ADC;
    cfg.long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS;
    cfg.short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS;
    for (size_t i = 0; i < 6; i++)
    {
        cfg.adc_button_config.adc_handle = &adc1_handle;
        cfg.adc_button_config.adc_channel = 4,
        cfg.adc_button_config.button_index = i;
        if (i == 0)
        {
            cfg.adc_button_config.min = (0 + vol[i]) / 2;
        }
        else
        {
            cfg.adc_button_config.min = (vol[i - 1] + vol[i]) / 2;
        }

        if (i == 5)
        {
            cfg.adc_button_config.max = (vol[i] + 3000) / 2;
        }
        else
        {
            cfg.adc_button_config.max = (vol[i] + vol[i + 1]) / 2;
        }

        g_btns[i] = iot_button_create(&cfg);
        iot_button_register_cb(g_btns[i], BUTTON_PRESS_DOWN, button_press_down_cb, NULL);
    }
}