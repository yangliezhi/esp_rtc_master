#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "esp_camera.h"

#define CAMERA_MODULE_NAME "ESP_S3_KORVO2"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET -1

#define CAMERA_PIN_VSYNC 21
#define CAMERA_PIN_HREF 38
#define CAMERA_PIN_PCLK 11
#define CAMERA_PIN_XCLK 40

#define CAMERA_PIN_SIOD 17
#define CAMERA_PIN_SIOC 18

#define CAMERA_PIN_D0 13
#define CAMERA_PIN_D1 47
#define CAMERA_PIN_D2 14
#define CAMERA_PIN_D3 3
#define CAMERA_PIN_D4 12
#define CAMERA_PIN_D5 42
#define CAMERA_PIN_D6 41
#define CAMERA_PIN_D7 39

#define XCLK_FREQ_HZ 10000000

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Initialize camera
     * 
     * @param pixformat    One of
     *                     - PIXFORMAT_RGB565
     *                     - PIXFORMAT_YUV422
     *                     - PIXFORMAT_GRAYSC
     *                     - PIXFORMAT_JPEG
     *                     - PIXFORMAT_RGB888
     *                     - PIXFORMAT_RAW
     *                     - PIXFORMAT_RGB444
     *                     - PIXFORMAT_RGB555
     * @param frame_size   One of
     *                     - FRAMESIZE_96X96,    // 96x96
     *                     - FRAMESIZE_QQVGA,    // 160x120
     *                     - FRAMESIZE_QCIF,     // 176x144
     *                     - FRAMESIZE_HQVGA,    // 240x176
     *                     - FRAMESIZE_240X240,  // 240x240
     *                     - FRAMESIZE_QVGA,     // 320x240
     *                     - FRAMESIZE_CIF,      // 400x296
     *                     - FRAMESIZE_HVGA,     // 480x320
     *                     - FRAMESIZE_VGA,      // 640x480
     *                     - FRAMESIZE_SVGA,     // 800x600
     *                     - FRAMESIZE_XGA,      // 1024x768
     *                     - FRAMESIZE_HD,       // 1280x720
     *                     - FRAMESIZE_SXGA,     // 1280x1024
     *                     - FRAMESIZE_UXGA,     // 1600x1200
     *                     - FRAMESIZE_FHD,      // 1920x1080
     *                     - FRAMESIZE_P_HD,     //  720x1280
     *                     - FRAMESIZE_P_3MP,    //  864x1536
     *                     - FRAMESIZE_QXGA,     // 2048x1536
     *                     - FRAMESIZE_QHD,      // 2560x1440
     *                     - FRAMESIZE_WQXGA,    // 2560x1600
     *                     - FRAMESIZE_P_FHD,    // 1080x1920
     *                     - FRAMESIZE_QSXGA,    // 2560x1920
     * @param fb_count     Number of frame buffers to be allocated. If more than one, then each frame will be acquired (double speed)
     */
    void register_camera(const pixformat_t pixel_fromat,
                         const framesize_t frame_size,
                         const uint8_t fb_count,
                         const QueueHandle_t frame_o);

#ifdef __cplusplus
}
#endif
