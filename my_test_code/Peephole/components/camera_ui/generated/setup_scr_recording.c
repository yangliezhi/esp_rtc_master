/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_recording(lv_ui *ui)
{
	//Write codes recording
	ui->recording = lv_obj_create(NULL);
	lv_obj_set_size(ui->recording, 240, 320);

	//Write style for recording, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->recording, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->recording, &_recording_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->recording, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes recording_imgbtn_play
	ui->recording_imgbtn_play = lv_imgbtn_create(ui->recording);
	lv_obj_add_flag(ui->recording_imgbtn_play, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->recording_imgbtn_play, LV_IMGBTN_STATE_RELEASED, NULL, &_vedio_play_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_play, LV_IMGBTN_STATE_PRESSED, NULL, &_vedio_play_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_play, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_vedio_play_1_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_play, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_vedio_play_1_alpha_57x40, NULL);
	ui->recording_imgbtn_play_label = lv_label_create(ui->recording_imgbtn_play);
	lv_label_set_text(ui->recording_imgbtn_play_label, "");
	lv_label_set_long_mode(ui->recording_imgbtn_play_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->recording_imgbtn_play_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->recording_imgbtn_play, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->recording_imgbtn_play, 13, 263);
	lv_obj_set_size(ui->recording_imgbtn_play, 57, 40);

	//Write style for recording_imgbtn_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->recording_imgbtn_play, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->recording_imgbtn_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->recording_imgbtn_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for recording_imgbtn_play, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_play, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_play, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_play, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for recording_imgbtn_play, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_play, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_play, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_play, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for recording_imgbtn_play, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_play, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes recording_imgbtn_recording
	ui->recording_imgbtn_recording = lv_imgbtn_create(ui->recording);
	lv_obj_add_flag(ui->recording_imgbtn_recording, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->recording_imgbtn_recording, LV_IMGBTN_STATE_RELEASED, NULL, &_vedio_record_1_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_recording, LV_IMGBTN_STATE_PRESSED, NULL, &_vedio_record_1_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_recording, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_vedio_record_alpha_57x40, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_recording, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_vedio_record_alpha_57x40, NULL);
	ui->recording_imgbtn_recording_label = lv_label_create(ui->recording_imgbtn_recording);
	lv_label_set_text(ui->recording_imgbtn_recording_label, "");
	lv_label_set_long_mode(ui->recording_imgbtn_recording_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->recording_imgbtn_recording_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->recording_imgbtn_recording, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->recording_imgbtn_recording, 162, 263);
	lv_obj_set_size(ui->recording_imgbtn_recording, 57, 40);

	//Write style for recording_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->recording_imgbtn_recording, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->recording_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->recording_imgbtn_recording, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for recording_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_recording, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_recording, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for recording_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_recording, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_recording, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for recording_imgbtn_recording, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_recording, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes recording_imgbtn_return
	ui->recording_imgbtn_return = lv_imgbtn_create(ui->recording);
	lv_obj_add_flag(ui->recording_imgbtn_return, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->recording_imgbtn_return, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->recording_imgbtn_return, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->recording_imgbtn_return_label = lv_label_create(ui->recording_imgbtn_return);
	lv_label_set_text(ui->recording_imgbtn_return_label, "");
	lv_label_set_long_mode(ui->recording_imgbtn_return_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->recording_imgbtn_return_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->recording_imgbtn_return, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->recording_imgbtn_return, 10, 7);
	lv_obj_set_size(ui->recording_imgbtn_return, 49, 30);

	//Write style for recording_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->recording_imgbtn_return, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->recording_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->recording_imgbtn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for recording_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for recording_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->recording_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->recording_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->recording_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for recording_imgbtn_return, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->recording_imgbtn_return, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->recording);

	
	//Init events for screen.
	events_init_recording(ui);
}
