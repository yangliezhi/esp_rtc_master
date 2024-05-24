/*
 * @Author: 都建民 
 * @Date: 2024-03-21 12:16:08 
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 21:55:42
 */
#pragma once
#include "who_camera.h"
#include "who_motion_detection.hpp"
#include "who_human_face_detection.hpp"
#include "who_human_face_recognition.hpp"
#include "who_lcd.h"

#define FACE_RECOGNITION_TASK_STOP (1 << 8) // 人脸识别和录像的切换标志位
#define FACE_RECOGNITION_TASK_BIT (1 << 6) // 人脸识别和录像的切换标志位
#define RECORDING_TASK_BIT (1 << 7) // 人脸识别和录像的切换标志位
#ifdef __cplusplus
extern "C"
{
#endif

void app_face_recognition_task(void *arg);

#ifdef __cplusplus
}
#endif
