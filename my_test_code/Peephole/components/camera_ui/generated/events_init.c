/*
 * @Author: 都建民
 * @Date: 2024-03-20 18:57:39
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 22:10:06
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

// #include "my_audio_player.h"
#include "config.h"
extern int select_switch;
static void main_imgbtn_door_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.door_del == true)
			{
				// play_index(0);
				setup_scr_door(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.door, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void main_imgbtn_recording_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.recording_del == true)
			{
				setup_scr_recording(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.recording, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void main_imgbtn_face_recognition_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.face_del == true)
			{

				setup_scr_face(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.face, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void main_imgbtn_sr_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.voice_del == true)
			{
				setup_scr_voice(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.voice, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void main_imgbtn_remote_monior_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.remote_del == true)
			{
				setup_scr_remote(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.remote, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void main_imgbtn_setting_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.setting_del == true)
			{
				setup_scr_setting(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.setting, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.main_del = true;
		}
		break;
	}
	default:
		break;
	}
}
void events_init_main(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main_imgbtn_door, main_imgbtn_door_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_imgbtn_recording, main_imgbtn_recording_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_imgbtn_face_recognition, main_imgbtn_face_recognition_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_imgbtn_sr, main_imgbtn_sr_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_imgbtn_remote_monior, main_imgbtn_remote_monior_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_imgbtn_setting, main_imgbtn_setting_event_handler, LV_EVENT_ALL, NULL);
}
static void door_imgbtn_call_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 1)
		{
			select_switch = -1;
		}
		else
		{
			// audio_player_stop();
			switch_event_status(FACE_RECOGNITION_STATE); // 切换到人脸识别状态
			select_switch = 1;
		}

		lv_obj_set_style_bg_color(guider_ui.door_imgbtn_call, lv_color_hex(0xcac4c4), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void door_imgbtn_retrun_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.door_del = true;
		}
		break;
	}
	default:
		break;
	}
}
void events_init_door(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->door_imgbtn_call, door_imgbtn_call_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->door_imgbtn_retrun, door_imgbtn_retrun_event_handler, LV_EVENT_ALL, NULL);
}

static void face_imgbtn_recognition_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 3)
		{
			switch_event_status(FACE_RECOGNITION_STOP); // 切换到人脸识别停止状态
			select_switch = -1;
		}
		else
		{
			switch_event_status(FACE_RECOGNITION_STATE); // 切换到人脸识别状态
			select_switch = 3;
		}

		lv_obj_set_style_bg_color(guider_ui.face_imgbtn_recognition, lv_color_hex(0xc5b4b4), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void face_imgbtn_motion_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 4)
		{
			select_switch = -1;
		}
		else
		{
			select_switch = 4;
		}
		lv_obj_set_style_bg_color(guider_ui.face_imgbtn_motion, lv_color_hex(0xad9999), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void face_imgbtn_retrun_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.face_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void face_imgbtn_save_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 2)
		{
			select_switch = -1;
		}
		else
		{
			select_switch = 2;
		}
		lv_obj_set_style_bg_color(guider_ui.face_imgbtn_save, lv_color_hex(0xa69b9b), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
void events_init_face(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->face_imgbtn_recognition, face_imgbtn_recognition_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->face_imgbtn_motion, face_imgbtn_motion_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->face_imgbtn_retrun, face_imgbtn_retrun_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->face_imgbtn_save, face_imgbtn_save_event_handler, LV_EVENT_ALL, NULL);
}
static void recording_imgbtn_play_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_set_style_bg_color(guider_ui.recording_imgbtn_play, lv_color_hex(0xc2b2b2), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void recording_imgbtn_recording_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 5)
		{
			select_switch = -1;
		}
		else
		{
			select_switch = 5;
		}

		lv_obj_set_style_bg_color(guider_ui.recording_imgbtn_recording, lv_color_hex(0xc1b8b8), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void recording_imgbtn_return_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.recording_del = true;
		}
		break;
	}
	default:
		break;
	}
}
void events_init_recording(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->recording_imgbtn_play, recording_imgbtn_play_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->recording_imgbtn_recording, recording_imgbtn_recording_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->recording_imgbtn_return, recording_imgbtn_return_event_handler, LV_EVENT_ALL, NULL);
}
static void voice_imgbtn_return_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.voice_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void voice_imgbtn_detect_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_obj_set_style_bg_color(guider_ui.voice_imgbtn_detect, lv_color_hex(0xccb8b8), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}

#include "config.h"
static void voice_imgbtn_control_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		static bool isRecognizing = false; // 初始状态为非识别状态

		if (isRecognizing)
		{
			switch_event_status(VOICE_RECOGNITION_STOP); // 切换到语音停止状态
			// printf("------------voice imgbtn  stop------------\n");
			lv_obj_set_style_bg_color(guider_ui.voice_imgbtn_control, lv_color_hex(0x999999), LV_PART_MAIN);
		}
		else
		{
			switch_event_status(VOICE_RECOGNITION_STATE); // 切换到语音识别状态
			// printf("------------voice imgbtn  start------------\n");
			lv_obj_set_style_bg_color(guider_ui.voice_imgbtn_control, lv_color_hex(0xad9999), LV_PART_MAIN);
		}

		isRecognizing = !isRecognizing; // 切换状态
		break;
	}
	default:
		break;
	}
}
void events_init_voice(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->voice_imgbtn_return, voice_imgbtn_return_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->voice_imgbtn_detect, voice_imgbtn_detect_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->voice_imgbtn_control, voice_imgbtn_control_event_handler, LV_EVENT_ALL, NULL);
}
static void remote_imgbtn_retrun_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.remote_del = true;
		}
		break;
	}
	default:
		break;
	}
}
static void remote_imgbtn_download_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 6)
		{
			select_switch = -1;
		}
		else
		{
			select_switch = 6;
		}
		lv_obj_set_style_bg_color(guider_ui.remote_imgbtn_download, lv_color_hex(0xb6a5a5), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
static void remote_imgbtn_monior_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (select_switch == 7)
		{
			select_switch = -1;
		}
		else
		{
			select_switch = 7;
		}

		lv_obj_set_style_bg_color(guider_ui.remote_imgbtn_monior, lv_color_hex(0xccbdbd), LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
void events_init_remote(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->remote_imgbtn_retrun, remote_imgbtn_retrun_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->remote_imgbtn_download, remote_imgbtn_download_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->remote_imgbtn_monior, remote_imgbtn_monior_event_handler, LV_EVENT_ALL, NULL);
}
static void setting_imgbtn_return_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		// Write the load screen code.
		lv_obj_t *act_scr = lv_scr_act();
		lv_disp_t *d = lv_obj_get_disp(act_scr);
		if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
		{
			if (guider_ui.main_del == true)
			{
				setup_scr_main(&guider_ui);
			}
			lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
			guider_ui.setting_del = true;
		}
		break;
	}
	default:
		break;
	}
}
void events_init_setting(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->setting_imgbtn_return, setting_imgbtn_return_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{
}
