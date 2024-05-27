/*
 * @Author: dujianmin@qq:20130527 
 * @Date: 2024-05-03 20:40:04 
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-03 21:10:46
 */
#include <stdio.h>
#include "du_bsp_camera.h"

#include <stdio.h>
#include "string.h"
#include "esp_log.h"

#include "du_bsp_lcd.h"

#include "esp_lcd_panel_ops.h"
#include "esp_camera.h"
#include "du_bsp_decode_jpeg.h"

static const char *TAG = "LCD_Camera";

static const pixformat_t s_camera_format = PIXFORMAT_RGB565;
// static const pixformat_t s_camera_format = PIXFORMAT_JPEG;
uint16_t *rgb_buffer;

static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sscb_sda = CAM_PIN_SIOD,
    .pin_sscb_scl = CAM_PIN_SIOC,

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
    .pixel_format = s_camera_format, // YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_QVGA,    // QQVGA-UXGA Do not use sizes above QVGA when not JPEG

    .jpeg_quality = 12, // 0-63 lower number means higher quality
    .fb_count = 2,      // if more than one, i2s runs in continuous mode. Use only with JPEG
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

static esp_err_t init_camera()
{
    // initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

/* example: RGB565 -> LCD */
static esp_err_t example_lcd_rgb_draw(esp_lcd_panel_handle_t panel_handle, uint8_t *image)
{
    uint32_t lines_num = 40;
    for (int i = 0; i < EXAMPLE_LCD_V_RES / lines_num; ++i)
    {
        esp_lcd_panel_draw_bitmap(panel_handle, 0, i * lines_num, EXAMPLE_LCD_H_RES, lines_num + i * lines_num, image + EXAMPLE_LCD_H_RES * i * lines_num * 2);
    }
    return ESP_OK;
}

/* example: YUV422 -> RGB565 -> LCD */
static esp_err_t example_lcd_yuv422_draw(esp_lcd_panel_handle_t panel_handle, uint8_t *image)
{

    // jpeg_yuv2rgb(JPEG_SUB_SAMPLE_YUV422, JPEG_RAW_TYPE_RGB565_BE, image, EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES, rgb_buffer);
    // example_lcd_rgb_draw(panel_handle, rgb_buffer);
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 320, 240, image);
    return ESP_OK;
}

void du_bsp_camera_task(void *pvParameters)
{
    esp_lcd_panel_handle_t panel_handle_t = (esp_lcd_panel_handle_t)pvParameters;
    TickType_t start_time, end_time;
    uint32_t frame_count = 0;

    if (ESP_OK != init_camera())
    {
        return;
    }

    if (s_camera_format == PIXFORMAT_JPEG)
    {
        rgb_buffer = (uint16_t *)heap_caps_malloc(320 * 240 * 2, MALLOC_CAP_SPIRAM);
    }

    while (1)
    {

        camera_fb_t *pic = esp_camera_fb_get();

        if (s_camera_format == PIXFORMAT_JPEG)
        {
            du_bsp_decode_image(pic->buf, pic->len, rgb_buffer);
            example_lcd_rgb_draw(panel_handle_t, rgb_buffer);
        }
        else
        {
            // PIXFORMAT_YUV565
            example_lcd_rgb_draw(panel_handle_t, pic->buf);
        }

        // vTaskDelay(1000 / portTICK_PERIOD_MS); // 这里设置延时为 100 毫秒
        esp_camera_fb_return(pic);
    }

    if (s_camera_format == PIXFORMAT_JPEG)
    {
        free(rgb_buffer);
    }
    vTaskDelete(NULL);
}
