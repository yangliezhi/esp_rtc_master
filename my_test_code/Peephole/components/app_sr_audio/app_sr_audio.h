#pragma once

#include <stdio.h>
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
#include "esp_board_init.h"
#include "speech_commands_action.h"
#include "model_path.h"

#include "file_iterator.h"
#include "esp_spiffs.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
extern esp_afe_sr_iface_t *afe_handle;
extern esp_afe_sr_data_t *afe_data;
extern int task_flag;
extern srmodel_list_t *models;

#define SR_TASK_START_BIT (1 << 4) // 用于表示播放音乐任务状态的位
#define SR_TASK_STOP_BIT (1 << 5) // 用于表示播放音乐任务状态的位
#ifdef __cplusplus
extern "C"
{
#endif

void app_sr_audio(void *arg);

#ifdef __cplusplus
}
#endif
