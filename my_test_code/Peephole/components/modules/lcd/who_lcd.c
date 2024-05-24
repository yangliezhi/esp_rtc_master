#include "who_lcd.h"
#include "esp_camera.h"
#include <string.h>
#include "logo_en_240x240_lcd.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "lvgl.h"
#include "gui_guider.h"
// #include "my_audio_player.h"
// #include "ui_audio.h"

static const char *TAG = "who_lcd";

static esp_lcd_panel_handle_t panel_handle = NULL;
static QueueHandle_t xQueueFrameI = NULL;
static QueueHandle_t xQueueFrameO = NULL;
static bool gReturnFB = true;


int select_switch = -1;
lv_img_dsc_t img_dsc_who = {
    .header.always_zero = 0,
    .header.w = 320,
    .header.h = 240,
    .data_size = 320 * 240 * 2,
    .header.cf = LV_IMG_CF_TRUE_COLOR,
    .data = NULL,
};
static void task_process_handler(void *arg)
{
    camera_fb_t *frame = NULL;
   
    while (true)
    {
        if (xQueueReceive(xQueueFrameI, &frame, portMAX_DELAY))
        {
            img_dsc_who.data = frame->buf;
            if (select_switch == 1)
            {
                lv_obj_set_style_bg_img_src(guider_ui.door, &img_dsc_who, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            if (select_switch == 2  || select_switch == 3 ||select_switch == 4)
            {
                lv_obj_set_style_bg_img_src(guider_ui.face, &img_dsc_who, LV_PART_MAIN | LV_STATE_DEFAULT);
            }


            // esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, frame->width, frame->height, (uint16_t *)frame->buf);
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

esp_err_t register_lcd(const QueueHandle_t frame_i, const QueueHandle_t frame_o, const bool return_fb)
{
    xQueueFrameI = frame_i;
    xQueueFrameO = frame_o;
    gReturnFB = return_fb;
    xTaskCreatePinnedToCore(task_process_handler, TAG, 4 * 1024, NULL, 5, NULL, 0);

    return ESP_OK;
}

void app_lcd_draw_wallpaper()
{
    uint16_t *pixels = (uint16_t *)heap_caps_malloc((logo_en_240x240_lcd_width * logo_en_240x240_lcd_height) * sizeof(uint16_t), MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    if (NULL == pixels)
    {
        ESP_LOGE(TAG, "Memory for bitmap is not enough");
        return;
    }
    memcpy(pixels, logo_en_240x240_lcd, (logo_en_240x240_lcd_width * logo_en_240x240_lcd_height) * sizeof(uint16_t));
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, logo_en_240x240_lcd_width, logo_en_240x240_lcd_height, (uint16_t *)pixels);
    heap_caps_free(pixels);
}

void app_lcd_set_color(int color)
{
    uint16_t *buffer = (uint16_t *)malloc(BOARD_LCD_H_RES * sizeof(uint16_t));
    if (NULL == buffer)
    {
        ESP_LOGE(TAG, "Memory for bitmap is not enough");
    }
    else
    {
        for (size_t i = 0; i < BOARD_LCD_H_RES; i++)
        {
            buffer[i] = color;
        }

        for (int y = 0; y < BOARD_LCD_V_RES; y++)
        {
            esp_lcd_panel_draw_bitmap(panel_handle, 0, y, BOARD_LCD_H_RES, y + 1, buffer);
        }

        free(buffer);
    }
}
