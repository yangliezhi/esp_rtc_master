/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-05-17 20:26:57
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 21:56:05
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include <string.h>

#include <stdio.h>
#include "esp_log.h"

#include "app_sr_audio.h"
#include "app_face_recognition.hpp"
#include "app_wifi.h"

// 声音麦克风组件
// #include "my_audio_player.h"

// LCD屏幕组件
#include "app_i2c.h"
#include "app_lcd.h"
#include "gui_guider.h"
// 按键组件
#include "app_button.h"
#include "bsp_board.h"

// 外设
#include "app_peripheral.h"

#include "config.h"
static const char *TAG = "peephole";

lv_ui guider_ui;
EventGroupHandle_t global_event_group;

// SystemState current_state = VOICE_RECOGNITION_STATE; // 默认状态为人脸识别

void switch_event_status(int state)
{
  // 创建事件组

  switch (state)
  {
  case VOICE_RECOGNITION_STATE:
    xEventGroupSetBits(global_event_group, SR_TASK_START_BIT);
    // 语音识别
    xTaskCreate(app_sr_audio, "app_sr_audio", 1024 * 4, NULL, 5, NULL);
    break;
  case VOICE_RECOGNITION_STOP:
    xEventGroupSetBits(global_event_group, SR_TASK_STOP_BIT);
    break;
  case FACE_RECOGNITION_STATE:
    xEventGroupSetBits(global_event_group, FACE_RECOGNITION_TASK_BIT);
    xTaskCreate(app_face_recognition_task, "app_face_recognition_task", 1024 * 4, NULL, 5, NULL);
    break;
  case FACE_RECOGNITION_STOP:
    xEventGroupSetBits(global_event_group, FACE_RECOGNITION_TASK_STOP);
    xTaskCreate(app_face_recognition_task, "app_face_recognition_task", 1024 * 4, NULL, 5, NULL);
    break;
  case RECORDING_STATE:
    xEventGroupSetBits(global_event_group, WIFI_CONNECTED_BIT_G);
    xEventGroupSetBits(global_event_group, RECORDING_TASK_BIT);

    break;
  default:
    // 处理默认情况
    break;
  }
}

void peripheral_initialization(void)
{
  my_i2c_init();
  bsp_spiffs_mount();
  tca9554_init();
  // 按键组件
  esp32_s3_adc_button();
}

extern "C" void app_main()
{
  // 外设初始化
  peripheral_initialization();
  // 事件组状态切换
  global_event_group = xEventGroupCreate();
  // switch_event_status(VOICE_RECOGNITION_STATE); // 切换到语音识别状态
  // switch_event_status(FACE_RECOGNITION_STATE);  // 切换到人脸识别状态
  // switch_event_status(RECORDING_STATE);         // 切换到录制状态

  // 屏幕组件
  app_lcd_run();
  setup_ui(&guider_ui);

  // wifi组件
  // xTaskCreate(wifi_task, "wifi_task", 4096, NULL, 5, NULL);
  //   人脸识别和录像 远程查看视频

  while (1)
  {

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
