/*
 * Copyright 2024 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#include "lvgl_camera.h"
#include "audio_player.h"
#include "my_audio_player.h"
static void screen_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        static bool is_bg_color_changed_btn_2 = false;
        if (is_bg_color_changed_btn_2)
        {

            select_camera = false;
            // my_lcd_led(0);
            lv_obj_set_style_bg_color(guider_ui.screen_imgbtn_1, lv_color_hex(0xb76666), LV_PART_MAIN);
            is_bg_color_changed_btn_2 = false;
        }
        else
        {
            select_camera = true;
            xSemaphoreGive(cam_semaphore);
            audio_player_pause();
            lv_obj_set_style_bg_color(guider_ui.screen_imgbtn_1, lv_color_hex(0x2195f6), LV_PART_MAIN);
            is_bg_color_changed_btn_2 = true;
        }

        // lv_obj_set_style_bg_color(guider_ui.screen_imgbtn_1, lv_color_hex(0xcac4c4), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}
void events_init_screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_imgbtn_1, screen_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{
}
