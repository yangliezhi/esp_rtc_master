/*
 * @Author: dujianmin
 * @Date: 2023-11-03 05:21:58
 * @LastEditors: Do not edit
 * @LastEditTime: 2023-11-03 05:27:31
 * @FilePath: \test_code_all\components\lvgl_camera\lvgl_camera.c
 * @QQ交流群: 826793815
 */
#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "lvgl_camera.h"
#include "esp_camera.h"
#include "lvgl.h"
#include "gui_guider.h"
static const char *TAG = "LCD_Camera";
bool select_camera = false;
EventGroupHandle_t camera_event_group; // 声明事件组句柄
camera_fb_t *fb;
lv_obj_t *img_cam; // 要显示图像
lv_img_dsc_t img_dsc = {
    .header.always_zero = 0,
    .header.w = 320,
    .header.h = 240,
    .data_size = 320 * 240 * 2,
    .header.cf = LV_IMG_CF_TRUE_COLOR,
    .data = NULL,
};
static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sscb_sda = -1,
    .pin_sscb_scl = -1,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    // XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 10000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,
    .pixel_format = PIXFORMAT_RGB565,  // YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QVGA,      // QQVGA-UXGA Do not use sizes above QVGA when not JPEG
    .fb_location = CAMERA_FB_IN_PSRAM, // 存放在外部PSRAM中
    .jpeg_quality = 12,                // 0-63 lower number means higher quality
    .fb_count = 2,                     // if more than one, i2s runs in continuous mode. Use only with JPEG
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};
static bool i2c_initialized = false;
static esp_err_t bsp_i2c_init(void)
{
    /* I2C was initialized before */
    if (i2c_initialized)
    {
        return ESP_OK;
    }

    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 17,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = 18,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000};
    i2c_param_config(0, &i2c_conf);
    i2c_driver_install(0, i2c_conf.mode, 0, 0, 0);

    i2c_initialized = true;

    return ESP_OK;
}

static esp_err_t init_camera()
{
    // initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }
    sensor_t *s = esp_camera_sensor_get();
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
    return err;
}
static void imgcam_init(void)
{
    // 先初始化摄像头
    if (ESP_OK != init_camera())
    {
        return;
    }
    img_cam = lv_img_create(lv_scr_act());
    static lv_style_t style_img;
    lv_style_init(&style_img);

    // Write style state: LV_STATE_DEFAULT for style_img
    lv_style_set_img_recolor(&style_img, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&style_img, 0);
    lv_style_set_img_opa(&style_img, 255);
    lv_obj_add_style(img_cam, &style_img, LV_STATE_DEFAULT);
    // lv_obj_set_style_transform_angle(img_cam, 90, 0); // 以90度进行旋转
    lv_obj_set_pos(img_cam, 0, 0);
    lv_obj_set_size(img_cam, 320, 240);
}
SemaphoreHandle_t cam_semaphore;
void Cam_Task(void *pvParameters)
{

    cam_semaphore = xSemaphoreCreateBinary();
    if (cam_semaphore == NULL)
    {
        ESP_LOGE(TAG, "Failed to create semaphore for camera task");
        vTaskDelete(NULL);
    }

    // bsp_i2c_init();
    init_camera();
    while (1)
    {
        if (xSemaphoreTake(cam_semaphore, portMAX_DELAY) != pdTRUE)
        {
            ESP_LOGE(TAG, "Failed to take semaphore for camera task");
            continue;
        }
        while (1)
        {
            fb = esp_camera_fb_get();
            if (fb == NULL)
            {
                vTaskDelay(100);
                ESP_LOGE(TAG, "Get image failed!");
            }
            else
            {
                img_dsc.data = fb->buf;
                if (select_camera)
                {
                    lv_obj_set_style_bg_img_src(guider_ui.screen, &img_dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                else
                {
                    lv_obj_set_style_bg_img_src(guider_ui.screen, &_china_240x320, LV_PART_MAIN | LV_STATE_DEFAULT);
                }

                esp_camera_fb_return(fb);
            }
             if (!select_camera)
            {
                break;
            }           
            vTaskDelay(10 / portTICK_PERIOD_MS);

        }
    }
}