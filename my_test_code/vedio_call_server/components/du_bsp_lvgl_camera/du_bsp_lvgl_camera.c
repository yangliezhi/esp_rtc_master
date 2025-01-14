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
#include "esp_camera.h"

#include "du_bsp_lvgl_camera.h"

static const char *TAG = "LCD_Camera";

camera_fb_t *fb;

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
    // .pixel_format = PIXFORMAT_RGB565,  // YUV422,GRAYSCALE,RGB565,JPEG
    .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_QVGA,      // QQVGA-UXGA Do not use sizes above QVGA when not JPEG
    .fb_location = CAMERA_FB_IN_PSRAM, // 存放在外部PSRAM中
    .jpeg_quality = 12,                // 0-63 lower number means higher quality
    .fb_count = 2,                     // if more than one, i2s runs in continuous mode. Use only with JPEG
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

esp_err_t init_camera()
{
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


int camera_read(av_frame_t *frame)
{
    fb = esp_camera_fb_get();
    frame->data = fb->buf;
    return fb->len;
}

void camera_return(void)
{
    esp_camera_fb_return(fb);
}