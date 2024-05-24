/*
 * @Author: 都建民
 * @Date: 2024-03-20 10:42:22
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 00:09:45
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <string.h>
#include "app_sr_audio.h"

#include "bsp_board.h"
#include "audio_player.h"

static const char *TAG = "app_sr_audio";

// 定义指令数组
const char *commands[] = {
    "dakaifangmen",
    "guanbifangmen",
    "bofangyinyue",
    "tingzhibofang",

};

int detect_flag = 0;
esp_afe_sr_iface_t *afe_handle = NULL;
esp_afe_sr_data_t *afe_data = NULL;
// int task_flag = 0;
bool app_sr_task = false;
srmodel_list_t *models = NULL;

static int play_voice = -2;
afe_config_t afe_config = {
    .aec_init = true,
    .se_init = true,
    .vad_init = true,
    .wakenet_init = true,
    .voice_communication_init = false,
    .voice_communication_agc_init = false,
    .voice_communication_agc_gain = 15,
    .vad_mode = VAD_MODE_3,
    .wakenet_model_name = NULL,
    .wakenet_model_name_2 = NULL,
    .wakenet_mode = DET_MODE_2CH_90,
    .afe_mode = SR_MODE_LOW_COST,
    .afe_perferred_core = 0,
    .afe_perferred_priority = 5,
    .afe_ringbuf_size = 50,
    .memory_alloc_mode = AFE_MEMORY_ALLOC_MORE_PSRAM,
    .afe_linear_gain = 1.0,
    .agc_mode = AFE_MN_PEAK_AGC_MODE_2,
    .pcm_config = {
        .total_ch_num = 3,
        .mic_num = 2,
        .ref_num = 1,
        .sample_rate = 16000,
    },
    .debug_init = false,
    .debug_hook = {{AFE_DEBUG_HOOK_MASE_TASK_IN, NULL}, {AFE_DEBUG_HOOK_FETCH_TASK_IN, NULL}},
};

static void play_music(void *arg)
{
    while (app_sr_task)
    {
        switch (play_voice)
        {
        case -2:
            vTaskDelay(10);
            break;
        case -1:
            wake_up_action();
            play_voice = -2;
            break;
        case 2:
            app_play_index(0);

            play_voice = -2;
            break;

        default:
            speech_commands_action(play_voice);
            play_voice = -2;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

static void feed_Task(void *arg)
{
    esp_afe_sr_data_t *afe_data = arg;
    int audio_chunksize = afe_handle->get_feed_chunksize(afe_data);
    int nch = afe_handle->get_channel_num(afe_data);
    int feed_channel = esp_get_feed_channel();
    assert(nch <= feed_channel);
    int16_t *i2s_buff = malloc(audio_chunksize * sizeof(int16_t) * feed_channel);
    assert(i2s_buff);

    while (app_sr_task)
    {
        esp_get_feed_data(false, i2s_buff, audio_chunksize * sizeof(int16_t) * feed_channel);

        afe_handle->feed(afe_data, i2s_buff);
    }
    if (i2s_buff)
    {
        free(i2s_buff);
        i2s_buff = NULL;
    }
    vTaskDelete(NULL);
}

static void detect_Task(void *arg)
{
    esp_afe_sr_data_t *afe_data = arg;
    int afe_chunksize = afe_handle->get_fetch_chunksize(afe_data);
    char *mn_name = esp_srmodel_filter(models, ESP_MN_PREFIX, ESP_MN_CHINESE);
    // printf("multinet:%s\n", mn_name);
    esp_mn_iface_t *multinet = esp_mn_handle_from_name(mn_name);
    model_iface_data_t *model_data = multinet->create(mn_name, 6000);
    esp_mn_commands_update_from_sdkconfig(multinet, model_data); // Add speech commands from sdkconfig
    int mu_chunksize = multinet->get_samp_chunksize(model_data);
    assert(mu_chunksize == afe_chunksize);

    // print active speech commands
    multinet->print_active_speech_commands(model_data);
    printf("------------detect start------------\n");
    // FILE *fp = fopen("/sdcard/out1", "w");
    // if (fp == NULL) printf("can not open file\n");
    while (app_sr_task)
    {
        afe_fetch_result_t *res = afe_handle->fetch(afe_data);
        if (!res || res->ret_value == ESP_FAIL)
        {
            printf("fetch error!\n");
            break;
        }

        if (res->wakeup_state == WAKENET_DETECTED)
        {
            printf("WAKEWORD DETECTED\n");
            multinet->clean(model_data); // clean all status of multinet
        }
        else if (res->wakeup_state == WAKENET_CHANNEL_VERIFIED)
        {
            play_voice = -1;
            detect_flag = 1;
            printf("AFE_FETCH_CHANNEL_VERIFIED, channel index: %d\n", res->trigger_channel_id);
        }

        if (detect_flag == 1)
        {
            esp_mn_state_t mn_state = multinet->detect(model_data, res->data);

            if (mn_state == ESP_MN_STATE_DETECTING)
            {
                continue;
            }

            if (mn_state == ESP_MN_STATE_DETECTED)
            {
                esp_mn_results_t *mn_result = multinet->get_results(model_data);
                for (int i = 0; i < mn_result->num; i++)
                {
                    printf("TOP %d, command_id: %d, phrase_id: %d, string:%s prob: %f\n",
                           i + 1, mn_result->command_id[i], mn_result->phrase_id[i], mn_result->string, mn_result->prob[i]);
                }
                // 获取识别结果指令
                const char *recognizedCommand = mn_result->string;

                // 遍历指令数组，进行匹配并赋值
                for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
                {
                    if (strcmp(recognizedCommand, commands[i]) == 0)
                    {
                        play_voice = i;
                        break;
                    }
                }
            }

            if (mn_state == ESP_MN_STATE_TIMEOUT)
            {
                esp_mn_results_t *mn_result = multinet->get_results(model_data);
                printf("timeout, string:%s\n", mn_result->string);
                afe_handle->enable_wakenet(afe_data);
                detect_flag = 0;
                printf("\n-----------awaits to be waken up-----------\n");
                continue;
            }
        }
    }
    if (model_data)
    {
        multinet->destroy(model_data);
        model_data = NULL;
    }
    printf("detect exit\n");
    vTaskDelete(NULL);
}

extern EventGroupHandle_t global_event_group;

void app_sr_audio_init(void)
{
    static bool initialized = false; // 添加一个静态标志位

    if (!initialized)
    {
        models = esp_srmodel_init("model");
        ESP_ERROR_CHECK(esp_board_init(8000, 1, 16));
        // esp_sr_audio_play();
        // ESP_ERROR_CHECK(esp_sdcard_init("/sdcard", 10));
        // app_play_index(0);
        afe_handle = (esp_afe_sr_iface_t *)&ESP_AFE_SR_HANDLE;

        afe_config.wakenet_model_name = esp_srmodel_filter(models, ESP_WN_PREFIX, NULL);

        afe_data = afe_handle->create_from_config(&afe_config);

        initialized = true; // 设置标志位，确保只执行一次
    }
}

void app_sr_audio(void *arg)
{
    TaskHandle_t detect_Task_handle = NULL;
    TaskHandle_t feed_Task_handle = NULL;
    TaskHandle_t play_music_handle = NULL;

    while (1)
    {
        EventBits_t bits = xEventGroupWaitBits(global_event_group, SR_TASK_START_BIT | SR_TASK_STOP_BIT, pdTRUE, pdFALSE, portMAX_DELAY);
        printf("------------voice imgbtn  start------------\n");
        if (bits & SR_TASK_START_BIT)
        {
            app_sr_audio_init();
            app_sr_task = true;
            if (afe_data)
            {

                // 启动所有任务
                xTaskCreatePinnedToCore(&detect_Task, "detect", 8 * 1024, (void *)afe_data, 5, &detect_Task_handle, 1);
                xTaskCreatePinnedToCore(&feed_Task, "feed", 8 * 1024, (void *)afe_data, 5, &feed_Task_handle, 0);
                xTaskCreatePinnedToCore(&play_music, "play", 2 * 1024, NULL, 5, &play_music_handle, 1);
            }

            // 清除任务标志位
            xEventGroupClearBits(global_event_group, SR_TASK_START_BIT);
        }
        else if (bits & SR_TASK_STOP_BIT)
        {

            if (afe_data)
            {
                free(afe_data);
                afe_data = NULL;
            }

            esp_srmodel_deinit(models);

            if (detect_Task_handle)
            {
                vTaskDelete(detect_Task_handle);
                detect_Task_handle = NULL;
            }
            if (feed_Task_handle)
            {
                vTaskDelete(feed_Task_handle);
                feed_Task_handle = NULL;
            }
            if (play_music_handle)
            {
                vTaskDelete(play_music_handle);
                play_music_handle = NULL;
            }
            app_sr_task = false;
            // 清除任务标志位
            xEventGroupClearBits(global_event_group, SR_TASK_STOP_BIT);
        }
    }
}
