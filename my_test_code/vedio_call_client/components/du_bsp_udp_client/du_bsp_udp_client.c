#include <stdio.h>

#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "du_bsp_udp_client.h"
#include "du_bsp_lvgl_camera.h"

#include "du_bsp_button.h"

static const char *TAG = "du_bsp_udp_client";

#define CONFIG_EXAMPLE_IPV4_ADDR "255.255.255.255"
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR
#define PORT 3333
#define MAX_UDP_PACKET_SIZE 1024

static int sock = -1;
static struct sockaddr_in dest_addr;
static struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
socklen_t socklen = sizeof(source_addr);

static uint8_t vedio_sync_signal = 0xAA; // 同步标志，可以是任意值，发送和接收端要约定一致
static uint8_t audio_sync_signal = 0xBB; // 同步标志，可以是任意值，发送和接收端要约定一致

static void udp_video_send_data(multimedia_data_t *udp_send_video_frame)
{
    bool continue_vedio = true;
    int btn_index = 0;
    while (continue_vedio)
    {
        uint16_t data_len = camera_read(udp_send_video_frame->video_data);
        int total_sent = 0;
        int btn_index = 0;

        // 发送同步标志
        sendto(sock, &vedio_sync_signal, sizeof(vedio_sync_signal), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        // 发送数据大小
        sendto(sock, &data_len, sizeof(data_len), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        while (total_sent < data_len)
        {
            int remaining_len = data_len - total_sent;
            int send_len = remaining_len > 1024 ? 1024 : remaining_len;

            int err = sendto(sock, udp_send_video_frame->video_data + total_sent, send_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

            if (err < 0)
            {
                ESP_LOGE(TAG, "Failed to send data. Error %d", errno);
                vTaskDelay(50 / portTICK_PERIOD_MS); // 延时 25 毫秒
                // break;
            }
            else
            {
                total_sent += send_len;
                vTaskDelay(30 / portTICK_PERIOD_MS); // 延时 25 毫秒
            }

            // ESP_LOGI(TAG, "camera read len is value.................................%d ", total_sent);
        }

        // ESP_LOGI(TAG, "total_sent is value :%d bytes len is value : %d ", total_sent, len);
        camera_return();
        if (xQueueReceive(audio_button_q, &btn_index, 0) == pdTRUE)
        {
            if (btn_index == 3)
            {
                continue_vedio = false; // 退出循环
            }
        }
    }
}
static void udp_audio_send_data(multimedia_data_t *av_stream)
{
    bool continue_recording = true;
    int btn_index = 0;
    // 发送同步标志
    sendto(sock, &audio_sync_signal, sizeof(audio_sync_signal), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    while (continue_recording)
    {

        esp_codec_dev_read(record_dev, av_stream->audio_data, 1024);
        sendto(sock, av_stream->audio_data, 1024, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)); // 发送录音数据

        if (xQueueReceive(audio_button_q, &btn_index, 0) == pdTRUE)
        {
            if (btn_index == 3)
            {
                continue_recording = false; // 退出循环
            }
        }
    }
}

void udp_client_task(void *pvParameters)
{
    int addr_family = 0;
    int ip_protocol = 0;
    int len = 0;

    multimedia_data_t *av_stream = (multimedia_data_t *)pvParameters;

    while (1)
    {

        dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;

        sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }

        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        while (1)
        {
            int btn_index = 0;

            if (xQueueReceive(audio_button_q, &btn_index, portMAX_DELAY) == pdTRUE)
            {

                if (btn_index == 2)
                {

                    ESP_LOGE(TAG, "receive vedio data key.......:  %d", btn_index);
                    udp_video_send_data(av_stream);
                }
                if (btn_index == 5)
                {
                    ESP_LOGE(TAG, "receive audio data key.......:  %d", btn_index);
                    udp_audio_send_data(av_stream);
                }
            }

            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        if (sock != -1)
        {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}
