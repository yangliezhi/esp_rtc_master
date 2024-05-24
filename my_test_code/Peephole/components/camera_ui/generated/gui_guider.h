/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *main;
	bool main_del;
	lv_obj_t *main_imgbtn_door;
	lv_obj_t *main_imgbtn_door_label;
	lv_obj_t *main_imgbtn_recording;
	lv_obj_t *main_imgbtn_recording_label;
	lv_obj_t *main_imgbtn_face_recognition;
	lv_obj_t *main_imgbtn_face_recognition_label;
	lv_obj_t *main_imgbtn_sr;
	lv_obj_t *main_imgbtn_sr_label;
	lv_obj_t *main_imgbtn_remote_monior;
	lv_obj_t *main_imgbtn_remote_monior_label;
	lv_obj_t *main_imgbtn_setting;
	lv_obj_t *main_imgbtn_setting_label;
	lv_obj_t *door;
	bool door_del;
	lv_obj_t *door_imgbtn_call;
	lv_obj_t *door_imgbtn_call_label;
	lv_obj_t *door_imgbtn_retrun;
	lv_obj_t *door_imgbtn_retrun_label;
	lv_obj_t *face;
	bool face_del;
	lv_obj_t *face_imgbtn_recognition;
	lv_obj_t *face_imgbtn_recognition_label;
	lv_obj_t *face_imgbtn_motion;
	lv_obj_t *face_imgbtn_motion_label;
	lv_obj_t *face_imgbtn_retrun;
	lv_obj_t *face_imgbtn_retrun_label;
	lv_obj_t *face_imgbtn_save;
	lv_obj_t *face_imgbtn_save_label;
	lv_obj_t *recording;
	bool recording_del;
	lv_obj_t *recording_imgbtn_play;
	lv_obj_t *recording_imgbtn_play_label;
	lv_obj_t *recording_imgbtn_recording;
	lv_obj_t *recording_imgbtn_recording_label;
	lv_obj_t *recording_imgbtn_return;
	lv_obj_t *recording_imgbtn_return_label;
	lv_obj_t *voice;
	bool voice_del;
	lv_obj_t *voice_imgbtn_return;
	lv_obj_t *voice_imgbtn_return_label;
	lv_obj_t *voice_imgbtn_detect;
	lv_obj_t *voice_imgbtn_detect_label;
	lv_obj_t *voice_imgbtn_control;
	lv_obj_t *voice_imgbtn_control_label;
	lv_obj_t *remote;
	bool remote_del;
	lv_obj_t *remote_imgbtn_retrun;
	lv_obj_t *remote_imgbtn_retrun_label;
	lv_obj_t *remote_imgbtn_download;
	lv_obj_t *remote_imgbtn_download_label;
	lv_obj_t *remote_imgbtn_monior;
	lv_obj_t *remote_imgbtn_monior_label;
	lv_obj_t *setting;
	bool setting_del;
	lv_obj_t *setting_imgbtn_return;
	lv_obj_t *setting_imgbtn_return_label;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_main(lv_ui *ui);
void setup_scr_door(lv_ui *ui);
void setup_scr_face(lv_ui *ui);
void setup_scr_recording(lv_ui *ui);
void setup_scr_voice(lv_ui *ui);
void setup_scr_remote(lv_ui *ui);
void setup_scr_setting(lv_ui *ui);

LV_IMG_DECLARE(_maoyan_240x320);
LV_IMG_DECLARE(_door_bell_alpha_60x40);
LV_IMG_DECLARE(_door_bell_alpha_60x40);
LV_IMG_DECLARE(_recorde_alpha_60x40);
LV_IMG_DECLARE(_recorde_alpha_60x40);
LV_IMG_DECLARE(_face_alpha_60x49);
LV_IMG_DECLARE(_face_alpha_60x49);
LV_IMG_DECLARE(_voice_alpha_60x48);
LV_IMG_DECLARE(_voice_alpha_60x48);
LV_IMG_DECLARE(_remote_monitor_alpha_48x39);
LV_IMG_DECLARE(_remote_monitor_alpha_48x39);
LV_IMG_DECLARE(_setting_icon_alpha_48x40);
LV_IMG_DECLARE(_setting_alpha_48x40);

LV_IMG_DECLARE(_keshimenling_240x320);
LV_IMG_DECLARE(_door_dell_off_alpha_78x51);
LV_IMG_DECLARE(_door_dell_off_alpha_78x51);
LV_IMG_DECLARE(_door_dell_on_alpha_78x51);
LV_IMG_DECLARE(_door_dell_on_alpha_78x51);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);

LV_IMG_DECLARE(_face_recognition_240x320);
LV_IMG_DECLARE(_face_alpha_44x35);
LV_IMG_DECLARE(_face_alpha_44x35);
LV_IMG_DECLARE(_face_1_alpha_44x35);
LV_IMG_DECLARE(_face_1_alpha_44x35);
LV_IMG_DECLARE(_people_move_1_alpha_44x35);
LV_IMG_DECLARE(_people_move_1_alpha_44x35);
LV_IMG_DECLARE(_people_move_alpha_44x35);
LV_IMG_DECLARE(_people_move_alpha_44x35);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_save_1_alpha_44x35);
LV_IMG_DECLARE(_save_1_alpha_44x35);
LV_IMG_DECLARE(_save_alpha_44x35);
LV_IMG_DECLARE(_save_alpha_44x35);

LV_IMG_DECLARE(_recording_240x320);
LV_IMG_DECLARE(_vedio_play_alpha_57x40);
LV_IMG_DECLARE(_vedio_play_alpha_57x40);
LV_IMG_DECLARE(_vedio_play_1_alpha_57x40);
LV_IMG_DECLARE(_vedio_play_1_alpha_57x40);
LV_IMG_DECLARE(_vedio_record_1_alpha_57x40);
LV_IMG_DECLARE(_vedio_record_1_alpha_57x40);
LV_IMG_DECLARE(_vedio_record_alpha_57x40);
LV_IMG_DECLARE(_vedio_record_alpha_57x40);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);

LV_IMG_DECLARE(_yuyinshibie_240x320);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_voice_detect_1_alpha_45x34);
LV_IMG_DECLARE(_voice_detect_1_alpha_45x34);
LV_IMG_DECLARE(_voice_detect_alpha_45x34);
LV_IMG_DECLARE(_voice_detect_alpha_45x34);
LV_IMG_DECLARE(_voice_control_1_alpha_45x34);
LV_IMG_DECLARE(_voice_control_1_alpha_45x34);
LV_IMG_DECLARE(_voice_control_alpha_45x34);
LV_IMG_DECLARE(_voice_control_alpha_45x34);

LV_IMG_DECLARE(_yuanchengjiankong_240x320);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_remote_d0_alpha_47x36);
LV_IMG_DECLARE(_remote_d0_alpha_47x36);
LV_IMG_DECLARE(_remote_d1_alpha_47x36);
LV_IMG_DECLARE(_remote_d1_alpha_47x36);
LV_IMG_DECLARE(_remote_mo_alpha_47x36);
LV_IMG_DECLARE(_remote_mo_alpha_47x36);
LV_IMG_DECLARE(_remote_m1_alpha_47x36);
LV_IMG_DECLARE(_remote_m1_alpha_47x36);

LV_IMG_DECLARE(_setting_240x320);
LV_IMG_DECLARE(_return_alpha_49x30);
LV_IMG_DECLARE(_return_alpha_49x30);

LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
