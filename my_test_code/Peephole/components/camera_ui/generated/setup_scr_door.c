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


void setup_scr_door(lv_ui *ui)
{
	//Write codes door
	ui->door = lv_obj_create(NULL);
	lv_obj_set_size(ui->door, 240, 320);

	//Write style for door, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->door, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->door, &_keshimenling_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->door, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes door_imgbtn_call
	ui->door_imgbtn_call = lv_imgbtn_create(ui->door);
	lv_obj_add_flag(ui->door_imgbtn_call, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->door_imgbtn_call, LV_IMGBTN_STATE_RELEASED, NULL, &_door_dell_off_alpha_78x51, NULL);
	lv_imgbtn_set_src(ui->door_imgbtn_call, LV_IMGBTN_STATE_PRESSED, NULL, &_door_dell_off_alpha_78x51, NULL);
	lv_imgbtn_set_src(ui->door_imgbtn_call, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_door_dell_on_alpha_78x51, NULL);
	lv_imgbtn_set_src(ui->door_imgbtn_call, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_door_dell_on_alpha_78x51, NULL);
	ui->door_imgbtn_call_label = lv_label_create(ui->door_imgbtn_call);
	lv_label_set_text(ui->door_imgbtn_call_label, "");
	lv_label_set_long_mode(ui->door_imgbtn_call_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->door_imgbtn_call_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->door_imgbtn_call, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->door_imgbtn_call, 81, 261);
	lv_obj_set_size(ui->door_imgbtn_call, 78, 51);

	//Write style for door_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->door_imgbtn_call, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->door_imgbtn_call, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->door_imgbtn_call, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for door_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_call, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->door_imgbtn_call, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->door_imgbtn_call, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for door_imgbtn_call, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_call, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->door_imgbtn_call, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->door_imgbtn_call, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_call, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for door_imgbtn_call, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_call, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes door_imgbtn_retrun
	ui->door_imgbtn_retrun = lv_imgbtn_create(ui->door);
	lv_obj_add_flag(ui->door_imgbtn_retrun, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->door_imgbtn_retrun, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->door_imgbtn_retrun, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->door_imgbtn_retrun_label = lv_label_create(ui->door_imgbtn_retrun);
	lv_label_set_text(ui->door_imgbtn_retrun_label, "");
	lv_label_set_long_mode(ui->door_imgbtn_retrun_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->door_imgbtn_retrun_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->door_imgbtn_retrun, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->door_imgbtn_retrun, 10, 7);
	lv_obj_set_size(ui->door_imgbtn_retrun, 49, 30);

	//Write style for door_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->door_imgbtn_retrun, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->door_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->door_imgbtn_retrun, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for door_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->door_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->door_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for door_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->door_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->door_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->door_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for door_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->door_imgbtn_retrun, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->door);

	
	//Init events for screen.
	events_init_door(ui);
}
