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


void setup_scr_voice(lv_ui *ui)
{
	//Write codes voice
	ui->voice = lv_obj_create(NULL);
	lv_obj_set_size(ui->voice, 240, 320);

	//Write style for voice, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->voice, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->voice, &_yuyinshibie_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->voice, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes voice_imgbtn_return
	ui->voice_imgbtn_return = lv_imgbtn_create(ui->voice);
	lv_obj_add_flag(ui->voice_imgbtn_return, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->voice_imgbtn_return, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_return, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->voice_imgbtn_return_label = lv_label_create(ui->voice_imgbtn_return);
	lv_label_set_text(ui->voice_imgbtn_return_label, "");
	lv_label_set_long_mode(ui->voice_imgbtn_return_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->voice_imgbtn_return_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->voice_imgbtn_return, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->voice_imgbtn_return, 10, 7);
	lv_obj_set_size(ui->voice_imgbtn_return, 49, 30);

	//Write style for voice_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->voice_imgbtn_return, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->voice_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->voice_imgbtn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for voice_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for voice_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for voice_imgbtn_return, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_return, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes voice_imgbtn_detect
	ui->voice_imgbtn_detect = lv_imgbtn_create(ui->voice);
	lv_obj_add_flag(ui->voice_imgbtn_detect, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->voice_imgbtn_detect, LV_IMGBTN_STATE_RELEASED, NULL, &_voice_detect_1_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_detect, LV_IMGBTN_STATE_PRESSED, NULL, &_voice_detect_1_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_detect, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_voice_detect_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_detect, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_voice_detect_alpha_45x34, NULL);
	ui->voice_imgbtn_detect_label = lv_label_create(ui->voice_imgbtn_detect);
	lv_label_set_text(ui->voice_imgbtn_detect_label, "");
	lv_label_set_long_mode(ui->voice_imgbtn_detect_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->voice_imgbtn_detect_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->voice_imgbtn_detect, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->voice_imgbtn_detect, 14, 272);
	lv_obj_set_size(ui->voice_imgbtn_detect, 45, 34);

	//Write style for voice_imgbtn_detect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->voice_imgbtn_detect, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->voice_imgbtn_detect, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->voice_imgbtn_detect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for voice_imgbtn_detect, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_detect, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_detect, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_detect, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_detect, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for voice_imgbtn_detect, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_detect, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_detect, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_detect, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_detect, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for voice_imgbtn_detect, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_detect, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes voice_imgbtn_control
	ui->voice_imgbtn_control = lv_imgbtn_create(ui->voice);
	lv_obj_add_flag(ui->voice_imgbtn_control, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->voice_imgbtn_control, LV_IMGBTN_STATE_RELEASED, NULL, &_voice_control_1_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_control, LV_IMGBTN_STATE_PRESSED, NULL, &_voice_control_1_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_control, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_voice_control_alpha_45x34, NULL);
	lv_imgbtn_set_src(ui->voice_imgbtn_control, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_voice_control_alpha_45x34, NULL);
	ui->voice_imgbtn_control_label = lv_label_create(ui->voice_imgbtn_control);
	lv_label_set_text(ui->voice_imgbtn_control_label, "");
	lv_label_set_long_mode(ui->voice_imgbtn_control_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->voice_imgbtn_control_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->voice_imgbtn_control, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->voice_imgbtn_control, 180, 272);
	lv_obj_set_size(ui->voice_imgbtn_control, 45, 34);

	//Write style for voice_imgbtn_control, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->voice_imgbtn_control, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->voice_imgbtn_control, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->voice_imgbtn_control, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for voice_imgbtn_control, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_control, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_control, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_control, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_control, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for voice_imgbtn_control, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_control, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->voice_imgbtn_control, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->voice_imgbtn_control, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->voice_imgbtn_control, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for voice_imgbtn_control, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->voice_imgbtn_control, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->voice);

	
	//Init events for screen.
	events_init_voice(ui);
}
