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


void setup_scr_face(lv_ui *ui)
{
	//Write codes face
	ui->face = lv_obj_create(NULL);
	lv_obj_set_size(ui->face, 240, 320);

	//Write style for face, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->face, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->face, &_face_recognition_240x320, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->face, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes face_imgbtn_recognition
	ui->face_imgbtn_recognition = lv_imgbtn_create(ui->face);
	lv_obj_add_flag(ui->face_imgbtn_recognition, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->face_imgbtn_recognition, LV_IMGBTN_STATE_RELEASED, NULL, &_face_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_recognition, LV_IMGBTN_STATE_PRESSED, NULL, &_face_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_recognition, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_face_1_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_recognition, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_face_1_alpha_44x35, NULL);
	ui->face_imgbtn_recognition_label = lv_label_create(ui->face_imgbtn_recognition);
	lv_label_set_text(ui->face_imgbtn_recognition_label, "");
	lv_label_set_long_mode(ui->face_imgbtn_recognition_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->face_imgbtn_recognition_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->face_imgbtn_recognition, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->face_imgbtn_recognition, 98, 271);
	lv_obj_set_size(ui->face_imgbtn_recognition, 44, 35);

	//Write style for face_imgbtn_recognition, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->face_imgbtn_recognition, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->face_imgbtn_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->face_imgbtn_recognition, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_recognition, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for face_imgbtn_recognition, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_recognition, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->face_imgbtn_recognition, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->face_imgbtn_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_recognition, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for face_imgbtn_recognition, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_recognition, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->face_imgbtn_recognition, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->face_imgbtn_recognition, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_recognition, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for face_imgbtn_recognition, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_recognition, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes face_imgbtn_motion
	ui->face_imgbtn_motion = lv_imgbtn_create(ui->face);
	lv_obj_add_flag(ui->face_imgbtn_motion, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->face_imgbtn_motion, LV_IMGBTN_STATE_RELEASED, NULL, &_people_move_1_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_motion, LV_IMGBTN_STATE_PRESSED, NULL, &_people_move_1_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_motion, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_people_move_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_motion, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_people_move_alpha_44x35, NULL);
	ui->face_imgbtn_motion_label = lv_label_create(ui->face_imgbtn_motion);
	lv_label_set_text(ui->face_imgbtn_motion_label, "");
	lv_label_set_long_mode(ui->face_imgbtn_motion_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->face_imgbtn_motion_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->face_imgbtn_motion, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->face_imgbtn_motion, 179, 271);
	lv_obj_set_size(ui->face_imgbtn_motion, 44, 35);

	//Write style for face_imgbtn_motion, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->face_imgbtn_motion, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->face_imgbtn_motion, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->face_imgbtn_motion, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_motion, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for face_imgbtn_motion, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_motion, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->face_imgbtn_motion, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->face_imgbtn_motion, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_motion, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for face_imgbtn_motion, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_motion, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->face_imgbtn_motion, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->face_imgbtn_motion, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_motion, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for face_imgbtn_motion, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_motion, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes face_imgbtn_retrun
	ui->face_imgbtn_retrun = lv_imgbtn_create(ui->face);
	lv_obj_add_flag(ui->face_imgbtn_retrun, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->face_imgbtn_retrun, LV_IMGBTN_STATE_RELEASED, NULL, &_return_alpha_49x30, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_retrun, LV_IMGBTN_STATE_PRESSED, NULL, &_return_alpha_49x30, NULL);
	ui->face_imgbtn_retrun_label = lv_label_create(ui->face_imgbtn_retrun);
	lv_label_set_text(ui->face_imgbtn_retrun_label, "");
	lv_label_set_long_mode(ui->face_imgbtn_retrun_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->face_imgbtn_retrun_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->face_imgbtn_retrun, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->face_imgbtn_retrun, 10, 7);
	lv_obj_set_size(ui->face_imgbtn_retrun, 49, 30);

	//Write style for face_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->face_imgbtn_retrun, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->face_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->face_imgbtn_retrun, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for face_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->face_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->face_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for face_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_retrun, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->face_imgbtn_retrun, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->face_imgbtn_retrun, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_retrun, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for face_imgbtn_retrun, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_retrun, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes face_imgbtn_save
	ui->face_imgbtn_save = lv_imgbtn_create(ui->face);
	lv_obj_add_flag(ui->face_imgbtn_save, LV_OBJ_FLAG_CHECKABLE);
	lv_imgbtn_set_src(ui->face_imgbtn_save, LV_IMGBTN_STATE_RELEASED, NULL, &_save_1_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_save, LV_IMGBTN_STATE_PRESSED, NULL, &_save_1_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_save, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_save_alpha_44x35, NULL);
	lv_imgbtn_set_src(ui->face_imgbtn_save, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_save_alpha_44x35, NULL);
	ui->face_imgbtn_save_label = lv_label_create(ui->face_imgbtn_save);
	lv_label_set_text(ui->face_imgbtn_save_label, "");
	lv_label_set_long_mode(ui->face_imgbtn_save_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->face_imgbtn_save_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->face_imgbtn_save, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->face_imgbtn_save, 26, 271);
	lv_obj_set_size(ui->face_imgbtn_save, 44, 35);

	//Write style for face_imgbtn_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->face_imgbtn_save, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->face_imgbtn_save, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->face_imgbtn_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for face_imgbtn_save, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_save, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->face_imgbtn_save, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->face_imgbtn_save, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_save, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for face_imgbtn_save, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_save, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->face_imgbtn_save, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->face_imgbtn_save, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->face_imgbtn_save, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for face_imgbtn_save, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->face_imgbtn_save, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Update current screen layout.
	lv_obj_update_layout(ui->face);

	
	//Init events for screen.
	events_init_face(ui);
}
