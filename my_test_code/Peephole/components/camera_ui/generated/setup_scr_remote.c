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


void setup_scr_remote(lv_ui *ui)
{
	//Write codes remote
	ui->remote = lv_obj_create(NULL);
	lv_obj_set_size(ui->remote, 240, 320);

	//Write style for remote, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->remote, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->remote, &_yuanchengjiankong_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->remote, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes remote_imgbtn_retrun
	ui->remote_imgbtn_retrun = lv_imgbtn_create(ui->remote);
	lv_obj_add_flag(ui->remote_imgbtn_retrun, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->remote_imgbtn_retrun, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_retrun, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->remote_imgbtn_retrun_label = lv_label_create(ui->remote_imgbtn_retrun);
	lv_label_set_text(ui->remote_imgbtn_retrun_label, "");
	lv_label_set_long_mode(ui->remote_imgbtn_retrun_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->remote_imgbtn_retrun_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->remote_imgbtn_retrun, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->remote_imgbtn_retrun, 10, 7);
	lv_obj_set_size(ui->remote_imgbtn_retrun, 49, 30);

	//Write style for remote_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->remote_imgbtn_retrun, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->remote_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->remote_imgbtn_retrun, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for remote_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for remote_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for remote_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_retrun, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes remote_imgbtn_download
	ui->remote_imgbtn_download = lv_imgbtn_create(ui->remote);
	lv_obj_add_flag(ui->remote_imgbtn_download, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->remote_imgbtn_download, LV_IMGBTN_STATE_RELEASED, NULL, &_remote_d0_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_download, LV_IMGBTN_STATE_PRESSED, NULL, &_remote_d0_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_download, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_remote_d1_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_download, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_remote_d1_alpha_47x36, NULL);
	ui->remote_imgbtn_download_label = lv_label_create(ui->remote_imgbtn_download);
	lv_label_set_text(ui->remote_imgbtn_download_label, "");
	lv_label_set_long_mode(ui->remote_imgbtn_download_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->remote_imgbtn_download_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->remote_imgbtn_download, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->remote_imgbtn_download, 12, 274);
	lv_obj_set_size(ui->remote_imgbtn_download, 47, 36);

	//Write style for remote_imgbtn_download, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->remote_imgbtn_download, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->remote_imgbtn_download, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->remote_imgbtn_download, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_download, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for remote_imgbtn_download, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_download, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_download, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_download, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_download, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for remote_imgbtn_download, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_download, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_download, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_download, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_download, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for remote_imgbtn_download, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_download, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes remote_imgbtn_monior
	ui->remote_imgbtn_monior = lv_imgbtn_create(ui->remote);
	lv_obj_add_flag(ui->remote_imgbtn_monior, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->remote_imgbtn_monior, LV_IMGBTN_STATE_RELEASED, NULL, &_remote_mo_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_monior, LV_IMGBTN_STATE_PRESSED, NULL, &_remote_mo_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_monior, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_remote_m1_alpha_47x36, NULL);
	lv_imgbtn_set_src(ui->remote_imgbtn_monior, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_remote_m1_alpha_47x36, NULL);
	ui->remote_imgbtn_monior_label = lv_label_create(ui->remote_imgbtn_monior);
	lv_label_set_text(ui->remote_imgbtn_monior_label, "");
	lv_label_set_long_mode(ui->remote_imgbtn_monior_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->remote_imgbtn_monior_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->remote_imgbtn_monior, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->remote_imgbtn_monior, 183, 274);
	lv_obj_set_size(ui->remote_imgbtn_monior, 47, 36);

	//Write style for remote_imgbtn_monior, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->remote_imgbtn_monior, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->remote_imgbtn_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->remote_imgbtn_monior, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_monior, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for remote_imgbtn_monior, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_monior, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_monior, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_monior, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for remote_imgbtn_monior, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_monior, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->remote_imgbtn_monior, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->remote_imgbtn_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->remote_imgbtn_monior, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for remote_imgbtn_monior, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->remote_imgbtn_monior, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->remote);

	
	//Init events for screen.
	events_init_remote(ui);
}
