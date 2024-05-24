/*
 * @Author: 都建民 
 * @Date: 2024-03-20 18:57:46 
 * @Last Modified by:   dujianmin qq群 26875961 
 * @Last Modified time: 2024-03-20 18:57:46 
 */


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void events_init(lv_ui *ui);

void events_init_main(lv_ui *ui);
void events_init_door(lv_ui *ui);
void events_init_face(lv_ui *ui);
void events_init_recording(lv_ui *ui);
void events_init_voice(lv_ui *ui);
void events_init_remote(lv_ui *ui);
void events_init_setting(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
