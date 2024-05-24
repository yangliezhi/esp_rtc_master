/*
 * @Author: 都建民
 * @Date: 2024-03-20 18:58:02
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 21:59:14
 */
#include "app_face_recognition.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <stdio.h>
#include <string.h>
#include "event_logic.hpp"
#include "esp_err.h"
#include "file_server.h"
#include "stram_server.h"
#include "file_manager.h"
#include "avi_recorder.h"
#include <iostream>
#include "who_adc_button.h"
camera_fb_t *g_frame = nullptr;
#define EXAMPLE_SENSOR_FRAME_SIZE FRAMESIZE_VGA
extern int select_switch;
static QueueHandle_t xQueueAIFrame = NULL;
static QueueHandle_t xQueueLCDFrame = NULL;
static QueueHandle_t xQueueEventLogic = NULL;
static QueueHandle_t xQueueKeyState = NULL;

static QueueHandle_t xQueueFrameI = NULL;
static QueueHandle_t xQueueFrameO = NULL;
static bool gReturnFB = true;
const char *video_file = SD_CARD_MOUNT_POINT "/recorde.avi";
static const char *TAG = "APP_FACE_RECOGNITION";

static int _get_frame(void **buf, size_t *len)
{
    if (!g_frame)
    {
        ESP_LOGE(TAG, "Camera capture failed");
        return -1;
    }
    else
    {
        ESP_LOGI(TAG, "len=%d", g_frame->len);
        *buf = g_frame->buf; // 设置 buf 指向实际的图像数据
        *len = g_frame->len; // 设置 len 为图像数据的长度
    }
    return 0;
}
static int _return_frame(void *inbuf)
{
    esp_camera_fb_return(reinterpret_cast<camera_fb_t *>(inbuf)); // 将 inbuf 转换为 camera_fb_t* 类型进行返回
    return 0;
}
static void task_process_handler(void *arg)
{
    ESP_ERROR_CHECK(fm_sdcard_init()); /* Initialize file storage */
    camera_fb_t *frame = NULL;
    bool switch1_triggered = false; // 标志是否已触发调用第一个函数
    bool switch2_triggered = false; // 标志是否已触发调用第二个函数
    bool switch3_triggered = false; // 标志是否已触发调用第三个函数
    while (true)
    {
        if (xQueueReceive(xQueueFrameI, &frame, portMAX_DELAY))
        {
            if (!g_frame)
            {
                // 分配内存给 g_frame
                g_frame = (camera_fb_t *)malloc(sizeof(camera_fb_t));
                if (g_frame)
                {
                    g_frame->len = frame->len;                    // 设置图像数据的长度
                    g_frame->buf = (uint8_t *)malloc(frame->len); // 为图像数据分配内存
                    if (g_frame->buf)
                    {
                        memcpy(g_frame->buf, frame->buf, frame->len); // 将图像帧数据拷贝到 g_frame 中
                    }
                    else
                    {
                        // 处理内存分配失败的情况
                        ESP_LOGI(TAG, "处理内存失败的情况11111111");
                    }
                }
                else
                {
                    // 处理内存分配失败的情况
                    ESP_LOGI(TAG, "处理内存失败的情况22222222222222222222");
                }
            }

            if (select_switch == 5 && !switch1_triggered)
            {
                avi_recorder_start(video_file, _get_frame, _return_frame, resolution[EXAMPLE_SENSOR_FRAME_SIZE].width, resolution[EXAMPLE_SENSOR_FRAME_SIZE].height, 10 * 2, 1);
                switch1_triggered = true; // 设置标志，避免重复调用第一个函数
            }
            else if (select_switch == 7 && !switch2_triggered)
            {
                start_stream_server(xQueueFrameI, true);
                switch2_triggered = true; // 设置标志，避免重复调用第二个函数
            }
            else if (select_switch == 6 && !switch3_triggered)
            {
                start_file_server(SD_CARD_MOUNT_POINT);
                switch3_triggered = true; // 设置标志，避免重复调用第三个函数
            }

            if (xQueueFrameO)
            {
                xQueueSend(xQueueFrameO, &frame, portMAX_DELAY);
            }
            else if (gReturnFB)
            {
                esp_camera_fb_return(frame);
            }
            else
            {
                free(frame);
            }
        }
    }
}

esp_err_t register_record(const QueueHandle_t frame_i, const QueueHandle_t frame_o, const bool return_fb)
{
    xQueueFrameI = frame_i;
    xQueueFrameO = frame_o;
    gReturnFB = return_fb;
    xTaskCreatePinnedToCore(task_process_handler, TAG, 4 * 1024, NULL, 5, NULL, 0);

    return ESP_OK;
}
extern EventGroupHandle_t global_event_group;
void app_face_recognition_task(void *arg)
{
    // 创建队列
    xQueueAIFrame = xQueueCreate(2, sizeof(camera_fb_t *));
    xQueueLCDFrame = xQueueCreate(2, sizeof(camera_fb_t *));
    xQueueKeyState = xQueueCreate(1, sizeof(int *));
    xQueueEventLogic = xQueueCreate(1, sizeof(int *));
    printf("------------face recognition start------------\n");
    while (1)
    {
        EventBits_t bits = xEventGroupWaitBits(global_event_group, FACE_RECOGNITION_TASK_BIT | RECORDING_TASK_BIT, pdTRUE, pdFALSE, portMAX_DELAY);

        if (bits & FACE_RECOGNITION_TASK_BIT)
        {

            // // 注册相关任务
            register_adc_button(xQueueKeyState);
            register_event(xQueueKeyState, xQueueEventLogic);
            register_camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueAIFrame);
            // register_motion_detection(xQueueAIFrame, NULL, NULL, xQueueLCDFrame);
            register_human_face_recognition(xQueueAIFrame, xQueueEventLogic, NULL, xQueueLCDFrame, true);
            register_lcd(xQueueLCDFrame, NULL, true);

            // 清除任务标志位
            xEventGroupClearBits(global_event_group, FACE_RECOGNITION_TASK_BIT);
        }
        else if (bits & RECORDING_TASK_BIT)
        {
            // 注册录像任务
            // register_record(xQueueAIFrame, NULL, true);

            // 清除任务标志位
            xEventGroupClearBits(global_event_group, RECORDING_TASK_BIT);
        }
        else if (bits & FACE_RECOGNITION_TASK_STOP)
        {
            // 重新启动ESP32
            esp_restart();
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
