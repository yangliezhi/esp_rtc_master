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


void setup_scr_main(lv_ui *ui)
{
	//Write codes main
	ui->main = lv_obj_create(NULL);
	lv_obj_set_size(ui->main, 240, 320);

	//Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->main, &_maoyan_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_imgbtn_door
	ui->main_imgbtn_door = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_door, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_door, LV_IMGBTN_STATE_RELEASED, NULL, &_door_bell_alpha_60x40, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_door, LV_IMGBTN_STATE_PRESSED, NULL, &_door_bell_alpha_60x40, NULL);
	ui->main_imgbtn_door_label = lv_label_create(ui->main_imgbtn_door);
	lv_label_set_text(ui->main_imgbtn_door_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_door_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_door_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_door, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_door, 7, 70);
	lv_obj_set_size(ui->main_imgbtn_door, 60, 40);

	//Write style for main_imgbtn_door, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_door, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_door, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_door, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_door, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_door, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_door, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_door, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_door, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_door, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_door, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_door, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_door, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_door, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_door, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_door, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_door, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes main_imgbtn_recording
	ui->main_imgbtn_recording = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_recording, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_recording, LV_IMGBTN_STATE_RELEASED, NULL, &_recorde_alpha_60x40, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_recording, LV_IMGBTN_STATE_PRESSED, NULL, &_recorde_alpha_60x40, NULL);
	ui->main_imgbtn_recording_label = lv_label_create(ui->main_imgbtn_recording);
	lv_label_set_text(ui->main_imgbtn_recording_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_recording_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_recording_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_recording, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_recording, 168, 70);
	lv_obj_set_size(ui->main_imgbtn_recording, 60, 40);

	//Write style for main_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_recording, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_recording, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_recording, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_recording, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_recording, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_recording, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_recording, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_recording, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_recording, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_recording, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_recording, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes main_imgbtn_face_recognition
	ui->main_imgbtn_face_recognition = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_face_recognition, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_face_recognition, LV_IMGBTN_STATE_RELEASED, NULL, &_face_alpha_60x49, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_face_recognition, LV_IMGBTN_STATE_PRESSED, NULL, &_face_alpha_60x49, NULL);
	ui->main_imgbtn_face_recognition_label = lv_label_create(ui->main_imgbtn_face_recognition);
	lv_label_set_text(ui->main_imgbtn_face_recognition_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_face_recognition_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_face_recognition_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_face_recognition, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_face_recognition, 12, 164);
	lv_obj_set_size(ui->main_imgbtn_face_recognition, 60, 49);

	//Write style for main_imgbtn_face_recognition, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_face_recognition, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_face_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_face_recognition, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_face_recognition, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_face_recognition, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_face_recognition, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_face_recognition, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_face_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_face_recognition, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_face_recognition, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_face_recognition, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_face_recognition, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_face_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_face_recognition, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_face_recognition, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_face_recognition, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes main_imgbtn_sr
	ui->main_imgbtn_sr = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_sr, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_sr, LV_IMGBTN_STATE_RELEASED, NULL, &_voice_alpha_60x48, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_sr, LV_IMGBTN_STATE_PRESSED, NULL, &_voice_alpha_60x48, NULL);
	ui->main_imgbtn_sr_label = lv_label_create(ui->main_imgbtn_sr);
	lv_label_set_text(ui->main_imgbtn_sr_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_sr_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_sr_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_sr, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_sr, 155, 164);
	lv_obj_set_size(ui->main_imgbtn_sr, 60, 48);

	//Write style for main_imgbtn_sr, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_sr, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_sr, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_sr, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_sr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_sr, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_sr, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_sr, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_sr, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_sr, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_sr, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_sr, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_sr, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_sr, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_sr, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_sr, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_sr, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes main_imgbtn_remote_monior
	ui->main_imgbtn_remote_monior = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_remote_monior, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_remote_monior, LV_IMGBTN_STATE_RELEASED, NULL, &_remote_monitor_alpha_48x39, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_remote_monior, LV_IMGBTN_STATE_PRESSED, NULL, &_remote_monitor_alpha_48x39, NULL);
	ui->main_imgbtn_remote_monior_label = lv_label_create(ui->main_imgbtn_remote_monior);
	lv_label_set_text(ui->main_imgbtn_remote_monior_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_remote_monior_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_remote_monior_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_remote_monior, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_remote_monior, 24, 270);
	lv_obj_set_size(ui->main_imgbtn_remote_monior, 48, 39);

	//Write style for main_imgbtn_remote_monior, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_remote_monior, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_remote_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_remote_monior, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_remote_monior, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_remote_monior, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_remote_monior, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_remote_monior, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_remote_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_remote_monior, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_remote_monior, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_remote_monior, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_remote_monior, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_remote_monior, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_remote_monior, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_remote_monior, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_remote_monior, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes main_imgbtn_setting
	ui->main_imgbtn_setting = lv_imgbtn_create(ui->main);
	lv_obj_add_flag(ui->main_imgbtn_setting, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->main_imgbtn_setting, LV_IMGBTN_STATE_RELEASED, NULL, &_setting_icon_alpha_48x40, NULL);
	lv_imgbtn_set_src(ui->main_imgbtn_setting, LV_IMGBTN_STATE_PRESSED, NULL, &_setting_alpha_48x40, NULL);
	ui->main_imgbtn_setting_label = lv_label_create(ui->main_imgbtn_setting);
	lv_label_set_text(ui->main_imgbtn_setting_label, "");
	lv_label_set_long_mode(ui->main_imgbtn_setting_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_imgbtn_setting_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_imgbtn_setting, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_imgbtn_setting, 168, 269);
	lv_obj_set_size(ui->main_imgbtn_setting, 48, 40);

	//Write style for main_imgbtn_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->main_imgbtn_setting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_imgbtn_setting, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_imgbtn_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_imgbtn_setting, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_setting, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_imgbtn_setting, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_imgbtn_setting, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_setting, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for main_imgbtn_setting, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_setting, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->main_imgbtn_setting, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->main_imgbtn_setting, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->main_imgbtn_setting, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for main_imgbtn_setting, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->main_imgbtn_setting, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->main);

	
	//Init events for screen.
	events_init_main(ui);
}
