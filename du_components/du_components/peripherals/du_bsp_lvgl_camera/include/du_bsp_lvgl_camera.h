#ifndef __LVGL_CAMERA__
#define __LVGL_CAMERA__
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"

typedef struct
{
    uint8_t *data;
    uint32_t len;
    uint64_t pts;
} av_frame_t;

#define FUNC_CAMERA_EN (1)
#define CAM_PIN_PWDN -1
#define CAM_PIN_RESET -1
#define CAM_PIN_XCLK GPIO_NUM_40
#define CAM_PIN_SIOD GPIO_NUM_17
#define CAM_PIN_SIOC GPIO_NUM_18

#define CAM_PIN_D7 GPIO_NUM_39
#define CAM_PIN_D6 GPIO_NUM_41
#define CAM_PIN_D5 GPIO_NUM_42
#define CAM_PIN_D4 GPIO_NUM_12
#define CAM_PIN_D3 GPIO_NUM_3
#define CAM_PIN_D2 GPIO_NUM_14
#define CAM_PIN_D1 GPIO_NUM_47
#define CAM_PIN_D0 GPIO_NUM_13
#define CAM_PIN_VSYNC GPIO_NUM_21
#define CAM_PIN_HREF GPIO_NUM_38
#define CAM_PIN_PCLK GPIO_NUM_11
esp_err_t init_camera();
int camera_read(av_frame_t *frame);
void camera_return(void);
#endif