#include "du_sr.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"

#include "esp_mn_speech_commands.h"
#include "esp_process_sdkconfig.h"
#include "esp_afe_sr_models.h"
#include "esp_mn_models.h"
#include "esp_wn_iface.h"
#include "esp_wn_models.h"
#include "esp_afe_sr_iface.h"
#include "esp_mn_iface.h"

static const char *TAG = "app_sr";

extern sr_data_t *g_sr_data;

esp_err_t app_sr_get_result(sr_result_t *result, TickType_t xTicksToWait)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");

    xQueueReceive(g_sr_data->result_que, result, xTicksToWait);
    return ESP_OK;
}

esp_err_t app_sr_add_cmd(const sr_cmd_t *cmd)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");
    ESP_RETURN_ON_FALSE(NULL != cmd, ESP_ERR_INVALID_ARG, TAG, "pointer of cmd is invaild");
    ESP_RETURN_ON_FALSE(cmd->lang == g_sr_data->lang, ESP_ERR_INVALID_ARG, TAG, "cmd lang error");
    ESP_RETURN_ON_FALSE(ESP_MN_MAX_PHRASE_NUM >= g_sr_data->cmd_num, ESP_ERR_INVALID_STATE, TAG, "cmd is full");

    sr_cmd_t *item = (sr_cmd_t *)heap_caps_calloc(1, sizeof(sr_cmd_t), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    ESP_RETURN_ON_FALSE(NULL != item, ESP_ERR_NO_MEM, TAG, "memory for sr cmd is not enough");
    memcpy(item, cmd, sizeof(sr_cmd_t));
    item->next.sle_next = NULL;
#if 1 // insert after
    sr_cmd_t *last = SLIST_FIRST(&g_sr_data->cmd_list);
    if (last == NULL)
    {
        SLIST_INSERT_HEAD(&g_sr_data->cmd_list, item, next);
    }
    else
    {
        sr_cmd_t *it;
        while ((it = SLIST_NEXT(last, next)) != NULL)
        {
            last = it;
        }
        SLIST_INSERT_AFTER(last, item, next);
    }
#else // insert head
    SLIST_INSERT_HEAD(&g_sr_data->cmd_list, it, next);
#endif

    if (strstr(g_sr_data->mn_name, "mn7_en"))
    {
        esp_mn_commands_add(g_sr_data->cmd_num, (char *)cmd->str);
    }
    else
    {
        esp_mn_commands_add(g_sr_data->cmd_num, (char *)cmd->phoneme);
    }
    g_sr_data->cmd_num++;
    return ESP_OK;
}

esp_err_t app_sr_modify_cmd(uint32_t id, const sr_cmd_t *cmd)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");
    ESP_RETURN_ON_FALSE(NULL != cmd, ESP_ERR_INVALID_ARG, TAG, "pointer of cmd is invaild");
    ESP_RETURN_ON_FALSE(id < g_sr_data->cmd_num, ESP_ERR_INVALID_ARG, TAG, "cmd id out of range");
    ESP_RETURN_ON_FALSE(cmd->lang == g_sr_data->lang, ESP_ERR_INVALID_ARG, TAG, "cmd lang error");

    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        if (it->id == id)
        {
            ESP_LOGI(TAG, "modify cmd [%ld] from %s to %s", id, it->str, cmd->str);
            if (strstr(g_sr_data->mn_name, "mn6_en"))
            {
                esp_mn_commands_modify(it->str, (char *)cmd->str);
            }
            else
            {
                esp_mn_commands_modify(it->phoneme, (char *)cmd->phoneme);
            }
            memcpy(it, cmd, sizeof(sr_cmd_t));
            break;
        }
    }
    ESP_RETURN_ON_FALSE(NULL != it, ESP_ERR_NOT_FOUND, TAG, "can't find cmd id:%d", cmd->id);
    return ESP_OK;
}

esp_err_t app_sr_remove_cmd(uint32_t id)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");
    ESP_RETURN_ON_FALSE(id < g_sr_data->cmd_num, ESP_ERR_INVALID_ARG, TAG, "cmd id out of range");
    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        if (it->id == id)
        {
            ESP_LOGI(TAG, "remove cmd id [%ld]", it->id);
            SLIST_REMOVE(&g_sr_data->cmd_list, it, sr_cmd_t, next);
            heap_caps_free(it);
            g_sr_data->cmd_num--;
            break;
        }
    }
    ESP_RETURN_ON_FALSE(NULL != it, ESP_ERR_NOT_FOUND, TAG, "can't find cmd id:%d", id);
    return ESP_OK;
}

esp_err_t app_sr_remove_all_cmd(void)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");
    sr_cmd_t *it;
    while (!SLIST_EMPTY(&g_sr_data->cmd_list))
    {
        it = SLIST_FIRST(&g_sr_data->cmd_list);
        SLIST_REMOVE_HEAD(&g_sr_data->cmd_list, next);
        heap_caps_free(it);
    }
    SLIST_INIT(&g_sr_data->cmd_list);
    return ESP_OK;
}

esp_err_t app_sr_update_cmds(void)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, ESP_ERR_INVALID_STATE, TAG, "SR is not running");

    uint32_t count = 0;
    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        it->id = count++;
    }

    esp_mn_error_t *err_id = esp_mn_commands_update(g_sr_data->multinet, g_sr_data->model_data);
    if (err_id)
    {
        for (int i = 0; i < err_id->num; i++)
        {
            // ESP_LOGE(TAG, "err cmd id:%u", err_id->phrases[i]);
        }
    }
    esp_mn_commands_print();

    return ESP_OK;
}

uint8_t app_sr_search_cmd_from_user_cmd(sr_user_cmd_t user_cmd, uint8_t *id_list, uint16_t max_len)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, 0, TAG, "SR is not running");

    uint8_t cmd_num = 0;
    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        if (user_cmd == it->cmd)
        {
            if (id_list)
            {
                id_list[cmd_num] = it->id;
            }
            if (++cmd_num >= max_len)
            {
                break;
            }
        }
    }
    return cmd_num;
}

uint8_t app_sr_search_cmd_from_phoneme(const char *phoneme, uint8_t *id_list, uint16_t max_len)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, 0, TAG, "SR is not running");

    uint8_t cmd_num = 0;
    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        if (0 == strcmp(phoneme, it->phoneme))
        {
            if (id_list)
            {
                id_list[cmd_num] = it->id;
            }
            if (++cmd_num >= max_len)
            {
                break;
            }
        }
    }
    return cmd_num;
}

const sr_cmd_t *app_sr_get_cmd_from_id(uint32_t id)
{
    ESP_RETURN_ON_FALSE(NULL != g_sr_data, NULL, TAG, "SR is not running");
    ESP_RETURN_ON_FALSE(id < g_sr_data->cmd_num, NULL, TAG, "cmd id out of range");

    sr_cmd_t *it;
    SLIST_FOREACH(it, &g_sr_data->cmd_list, next)
    {
        if (id == it->id)
        {
            return it;
        }
    }
    ESP_RETURN_ON_FALSE(NULL != it, NULL, TAG, "can't find cmd id:%d", id);
    return NULL;
}
