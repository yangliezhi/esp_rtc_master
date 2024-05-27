#ifndef __du_bsp_udp__
#define __du_bsp_udp__

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "du_bsp_audio_record.h"
typedef struct
{
    uint8_t *video_data; // 摄像头数据指针
    uint8_t *audio_data; // 声音数据指针
    uint32_t video_len;  // 摄像头数据长度
    uint32_t audio_len;  // 声音数据长度
} multimedia_data_t;

void udp_server_task(void *pvParameters);

#endif