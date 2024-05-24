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


void setup_scr_setting(lv_ui *ui)
{
	//Write codes setting
	ui->setting = lv_obj_create(NULL);
	lv_obj_set_size(ui->setting, 240, 320);

	//Write style for setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->setting, &_setting_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes setting_imgbtn_return
	ui->setting_imgbtn_return = lv_imgbtn_create(ui->setting);
	lv_obj_add_flag(ui->setting_imgbtn_return, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->setting_imgbtn_return, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->setting_imgbtn_return, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->setting_imgbtn_return_label = lv_label_create(ui->setting_imgbtn_return);
	lv_label_set_text(ui->setting_imgbtn_return_label, "");
	lv_label_set_long_mode(ui->setting_imgbtn_return_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->setting_imgbtn_return_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->setting_imgbtn_return, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->setting_imgbtn_return, 10, 7);
	lv_obj_set_size(ui->setting_imgbtn_return, 49, 30);

	//Write style for setting_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->setting_imgbtn_return, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->setting_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->setting_imgbtn_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->setting_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for setting_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->setting_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->setting_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->setting_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->setting_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for setting_imgbtn_return, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->setting_imgbtn_return, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->setting_imgbtn_return, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->setting_imgbtn_return, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->setting_imgbtn_return, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for setting_imgbtn_return, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->setting_imgbtn_return, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->setting);

	
	//Init events for screen.
	events_init_setting(ui);
}
