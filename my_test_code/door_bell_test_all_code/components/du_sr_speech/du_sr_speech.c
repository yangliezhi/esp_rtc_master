#include <stdio.h>
#include "du_sr_speech.h"

#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_process_sdkconfig.h"
#include "esp_wn_iface.h"
#include "esp_wn_models.h"
#include "esp_afe_sr_iface.h"
#include "esp_afe_sr_models.h"
#include "esp_mn_iface.h"
#include "esp_mn_models.h"

#include "esp_mn_speech_commands.h"
#include "model_path.h"

#include "du_mic_audio.h"
#include "file_iterator.h"
#include <stdbool.h>
#include "esp_check.h"
#include <string.h>
#include <sys/time.h>

#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_err.h"
#include "esp_log.h"

// #include "my_audio_player.h"
static const char *TAG = "app_sr_speech";

int detect_flag = 0;
static esp_afe_sr_iface_t *afe_handle = NULL;
static esp_afe_sr_data_t *afe_data = NULL;
static volatile int task_flag = 0;
srmodel_list_t *models = NULL;
static int play_voice = -2;
sr_data_t *g_sr_data = NULL;

/**
 * @brief all default commands
 */
static const sr_cmd_t g_default_cmd_info[] = {
    // English
    {SR_CMD_LIGHT_ON, SR_LANG_EN, 0, "Turn On the Light", "TkN nN jc LiT", {NULL}},
    {SR_CMD_LIGHT_ON, SR_LANG_EN, 0, "Switch On the Light", "SWgp nN jc LiT", {NULL}},
    {SR_CMD_LIGHT_OFF, SR_LANG_EN, 0, "Switch Off the Light", "SWgp eF jc LiT", {NULL}},
    {SR_CMD_LIGHT_OFF, SR_LANG_EN, 0, "Turn Off the Light", "TkN eF jc LiT", {NULL}},
    {SR_CMD_SET_RED, SR_LANG_EN, 0, "Turn Red", "TkN RfD", {NULL}},
    {SR_CMD_SET_GREEN, SR_LANG_EN, 0, "Turn Green", "TkN GRmN", {NULL}},
    {SR_CMD_SET_BLUE, SR_LANG_EN, 0, "Turn Blue", "TkN BLo", {NULL}},
    {SR_CMD_CUSTOMIZE_COLOR, SR_LANG_EN, 0, "Customize Color", "KcSTcMiZ KcLk", {NULL}},
    {SR_CMD_PLAY, SR_LANG_EN, 0, "Sing a song", "Sgl c Sel", {NULL}},
    {SR_CMD_PLAY, SR_LANG_EN, 0, "Play Music", "PLd MYoZgK", {NULL}},
    {SR_CMD_NEXT, SR_LANG_EN, 0, "Next Song", "NfKST Sel", {NULL}},
    {SR_CMD_PAUSE, SR_LANG_EN, 0, "Pause Playing", "PeZ PLdgl", {NULL}},

    {SR_CMD_AC_ON, SR_LANG_EN, 0, "Turn on the Air", "TkN nN jc fR", {NULL}},
    {SR_CMD_AC_OFF, SR_LANG_EN, 0, "Turn off the Air", "TkN eF jc fR", {NULL}},

    // Chinese
    {SR_CMD_LIGHT_ON, SR_LANG_CN, 0, "画一个猫", "hua yi ge mao", {NULL}},
    {SR_CMD_LIGHT_OFF, SR_LANG_CN, 0, "画一个狗", "hua yi ge gou", {NULL}},
    {SR_CMD_SET_RED, SR_LANG_CN, 0, "画一个小孩", "hua yi ge xiao hai", {NULL}},
    {SR_CMD_SET_GREEN, SR_LANG_CN, 0, "调成绿色", "tiao cheng lv se", {NULL}},
    {SR_CMD_SET_BLUE, SR_LANG_CN, 0, "调成蓝色", "tiao cheng lan se", {NULL}},
    {SR_CMD_CUSTOMIZE_COLOR, SR_LANG_CN, 0, "自定义颜色", "zi ding yi yan se", {NULL}},
    {SR_CMD_PLAY, SR_LANG_CN, 0, "播放音乐", "bo fang yin yue", {NULL}},
    {SR_CMD_NEXT, SR_LANG_CN, 0, "切歌", "qie ge", {NULL}},
    {SR_CMD_NEXT, SR_LANG_CN, 0, "下一曲", "xia yi qu", {NULL}},
    {SR_CMD_PAUSE, SR_LANG_CN, 0, "暂停", "zan ting", {NULL}},
    {SR_CMD_PAUSE, SR_LANG_CN, 0, "暂停播放", "zan ting bo fang", {NULL}},
    {SR_CMD_PAUSE, SR_LANG_CN, 0, "停止播放", "ting zhi bo fang", {NULL}},

    {SR_CMD_AC_ON, SR_LANG_CN, 0, "打开空调", "da kai kong tiao", {NULL}},
    {SR_CMD_AC_OFF, SR_LANG_CN, 0, "关闭空调", "guan bi kong tiao", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "舒适模式", "shu shi mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "制冷模式", "zhi leng mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "制热模式", "zhi re mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "加热模式", "jia re mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "除湿模式", "chu shi mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "送风模式", "song feng mo shi", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "升高温度", "sheng gao wen du", {NULL}},
    {SR_CMD_MAX, SR_LANG_CN, 0, "降低温度", "jiang di wen du", {NULL}},
};

esp_err_t app_sr_set_language(sr_language_t new_lang)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");

    if (new_lang == g_sr_data->lang)
    {
        ESP_LOGW(TAG, "nothing to do");
        return ESP_OK;
    }
    else
    {
        g_sr_data->lang = new_lang;
    }

    ESP_LOGW(TAG, "Set language to %s", SR_LANG_EN == g_sr_data->lang ? "EN" : "CN");
    if (g_sr_data->model_data)
    {
        g_sr_data->multinet->destroy(g_sr_data->model_data);
    }

    g_sr_data->cmd_num = 0;

    char *wn_name = esp_srmodel_filter(models, ESP_WN_PREFIX, (SR_LANG_EN == g_sr_data->lang ? "hiesp" : "hilexin"));
    ESP_RETURN_ON_FALSE(NULL != wn_name, ESP_ERR_INVALID_ARG, TAG, "Modifications to the code are required to support the relevant configuration");
    g_sr_data->afe_handle->set_wakenet(g_sr_data->afe_data, wn_name);
    ESP_LOGI(TAG, "load wakenet:%s", wn_name);

    char *mn_name = esp_srmodel_filter(models, ESP_MN_PREFIX, ((SR_LANG_EN == g_sr_data->lang) ? ESP_MN_ENGLISH : ESP_MN_CHINESE));
    ESP_RETURN_ON_FALSE(NULL != mn_name, ESP_ERR_INVALID_ARG, TAG, "Modifications to the code are required to support the relevant configuration");
    esp_mn_iface_t *multinet = esp_mn_handle_from_name(mn_name);
    model_iface_data_t *model_data = multinet->create(mn_name, 5760);
    g_sr_data->multinet = multinet;
    g_sr_data->model_data = model_data;
    g_sr_data->mn_name = mn_name;
    ESP_LOGI(TAG, "load multinet:%s", g_sr_data->mn_name);

    // remove all command
    app_sr_remove_all_cmd();
    if (strstr(g_sr_data->mn_name, "mn6"))
    {
        esp_mn_commands_clear();
    }

    uint8_t cmd_number = 0;
    // count command number
    for (size_t i = 0; i < sizeof(g_default_cmd_info) / sizeof(sr_cmd_t); i++)
    {
        if (g_default_cmd_info[i].lang == g_sr_data->lang)
        {
            app_sr_add_cmd(&g_default_cmd_info[i]);
            cmd_number++;
        }
    }
    ESP_LOGI(TAG, "cmd_number=%d", cmd_number);

    return app_sr_update_cmds(); /* Reset command list */
}

#define I2S_CHANNEL_NUM (2)
static void feed_Task(void *arg)
{
    size_t bytes_read = 0;
    esp_afe_sr_data_t *afe_data = (esp_afe_sr_data_t *)arg;
    int audio_chunksize = afe_handle->get_feed_chunksize(afe_data);
    int feed_channel = 3;
    ESP_LOGI(TAG, "audio_chunksize=%d, feed_channel=%d", audio_chunksize, feed_channel);

    /* Allocate audio buffer and check for result */
    int16_t *audio_buffer = heap_caps_malloc(audio_chunksize * sizeof(int16_t) * feed_channel, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (NULL == audio_buffer)
    {
        esp_system_abort("No mem for audio buffer");
    }
    g_sr_data->afe_in_buffer = audio_buffer;

    while (true)
    {

        /* Read audio data from I2S bus */
        bsp_i2s_read((char *)audio_buffer, audio_chunksize * I2S_CHANNEL_NUM * sizeof(int16_t), &bytes_read, portMAX_DELAY);
        // bsp_get_feed_data(false, audio_buffer, audio_chunksize * sizeof(int16_t) * feed_channel);

        // afe_handle->feed(afe_data, audio_buffer);

        /* Channel Adjust */
        for (int i = audio_chunksize - 1; i >= 0; i--)
        {
            audio_buffer[i * 3 + 2] = 0;
            audio_buffer[i * 3 + 1] = audio_buffer[i * 2 + 1];
            audio_buffer[i * 3 + 0] = audio_buffer[i * 2 + 0];
        }

        afe_handle->feed(afe_data, audio_buffer);
    }
}

#define MAX_RECORD_TIME_SECONDS 5 // Maximum recording time in seconds

static void record_audio(void *arg)
{
    esp_afe_sr_data_t *afe_data = arg;
    int afe_chunksize = afe_handle->get_fetch_chunksize(afe_data);
    int16_t audio_buffer[afe_chunksize * sizeof(int16_t)];
    // size_t bytes_read;
    time_t start_time = time(NULL); // Record start time
    time_t current_time;

    while (true)
    {

        afe_fetch_result_t *res = afe_handle->fetch(afe_data);
        if (res && res->ret_value != ESP_FAIL)
        {
            memcpy(audio_buffer, res->data, afe_chunksize * sizeof(int16_t));
            // bsp_audio_play(audio_buffer, afe_chunksize * sizeof(int16_t), 0);
            fwrite(audio_buffer, 1, afe_chunksize * sizeof(int16_t), g_sr_data->fp);
        }

        // Check elapsed time
        current_time = time(NULL);
        if (current_time - start_time >= MAX_RECORD_TIME_SECONDS)
        {
            // Close the file
            fclose(g_sr_data->fp);
            g_sr_data->fp = NULL; // Reset file pointer

            printf("Recording finished. Closed file.\n");
            break; // Exit the loop
        }
    }
}
static void read_record_audio(char *buffer, size_t len)
{
    // char *file_name = "/sdcard/rec3.pcm";
    char *file_name = "/spiffs/rec3.pcm";
    g_sr_data->fp = fopen(file_name, "r");

    size_t bytes_read;

    if (!g_sr_data || !g_sr_data->fp)
    {
        ESP_LOGE(TAG, "File pointer is NULL");
        return;
    }

    while ((bytes_read = fread(buffer, 1, len, g_sr_data->fp)) > 0)
    {
        ESP_LOGI(TAG, "file read    ..............%d", bytes_read);

        bsp_audio_play(buffer, bytes_read, 0);
    }

    if (bytes_read == 0 && ferror(g_sr_data->fp))
    {
        ESP_LOGI(TAG, "End of file reached..............");
        // ESP_LOGE(TAG, "Error reading from file: %s", strerror(errno));
    }
    else
    {
        ESP_LOGI(TAG, "End of file reached");
    }
}



void detect_Task(void *arg)
{
    bool detect_flag = false;

    esp_afe_sr_data_t *afe_data = arg;
    int afe_chunksize = afe_handle->get_fetch_chunksize(afe_data);

    int mu_chunksize = g_sr_data->multinet->get_samp_chunksize(g_sr_data->model_data);
    assert(mu_chunksize == afe_chunksize);
    ESP_LOGI(TAG, "------------detect start------------\n");
    char buffer[512]; // 假设缓冲区大小为128字节

    while (true)
    {

        afe_fetch_result_t *res = afe_handle->fetch(afe_data);
        if (!res || res->ret_value == ESP_FAIL)
        {
            continue;
        }

        if (res->wakeup_state == WAKENET_DETECTED)
        {
            ESP_LOGI(TAG, LOG_BOLD(LOG_COLOR_GREEN) "wakeword detected");
        }
        else if (res->wakeup_state == WAKENET_CHANNEL_VERIFIED)
        {
            detect_flag = true;
            g_sr_data->afe_handle->disable_wakenet(afe_data);
            ESP_LOGI(TAG, LOG_BOLD(LOG_COLOR_GREEN) "AFE_FETCH_CHANNEL_VERIFIED, channel index: %d\n", res->trigger_channel_id);
        }

        if (true == detect_flag)
        {
            record_audio(afe_data);
            read_record_audio(buffer, sizeof(buffer));

            g_sr_data->afe_handle->enable_wakenet(afe_data);
            detect_flag = false;
            continue;
        }
    }
    /* Task never returns */
    vTaskDelete(NULL);
}

esp_err_t du_sr_speech(bool record_en)
{
    esp_err_t ret = ESP_OK;
    ESP_RETURN_ON_FALSE(NULL == g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR already running");

    g_sr_data = heap_caps_calloc(1, sizeof(sr_data_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_NO_MEM, TAG, "Failed create sr data");

    g_sr_data->result_que = xQueueCreate(3, sizeof(sr_result_t));
    ESP_GOTO_ON_FALSE(NULL != g_sr_data->result_que, ESP_ERR_NO_MEM, err, TAG, "Failed create result queue");

    g_sr_data->event_group = xEventGroupCreate();
    ESP_GOTO_ON_FALSE(NULL != g_sr_data->event_group, ESP_ERR_NO_MEM, err, TAG, "Failed create event_group");

    SLIST_INIT(&g_sr_data->cmd_list);

    g_sr_data->b_record_en = record_en;
    if (record_en)
    {
        // char *file_name = "/sdcard/rec3.pcm";
        char *file_name = "/spiffs/rec3.pcm";
        g_sr_data->fp = fopen(file_name, "wb");
        ESP_GOTO_ON_FALSE(g_sr_data->fp != NULL, ESP_FAIL, err, TAG, "Failed to create record file");
        ESP_LOGI(TAG, "File created at %s", file_name);
    }

    BaseType_t ret_val;

    models = esp_srmodel_init("model");
    afe_handle = (esp_afe_sr_iface_t *)&ESP_AFE_SR_HANDLE;
    afe_config_t afe_config = AFE_CONFIG_DEFAULT();

    afe_config.wakenet_model_name = esp_srmodel_filter(models, ESP_WN_PREFIX, NULL);
    afe_config.aec_init = false;

    esp_afe_sr_data_t *afe_data = afe_handle->create_from_config(&afe_config);
    g_sr_data->afe_handle = afe_handle;
    g_sr_data->afe_data = afe_data;
    g_sr_data->afe_handle = afe_handle;
    g_sr_data->afe_data = afe_data;
    ret = app_sr_set_language(SR_LANG_CN);

    xTaskCreatePinnedToCore(&detect_Task, "detect", 8 * 1024, (void *)afe_data, 5, NULL, 1);
    xTaskCreatePinnedToCore(&feed_Task, "feed", 8 * 1024, (void *)afe_data, 5, NULL, 0);

    return ret;
err:
    // app_sr_stop();
    return ret;
}
