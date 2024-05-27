#include <stdio.h>
#include "du_bsp_udp_server.h"

#include "du_bsp_audio_record.h"
#include "du_bsp_lvgl_camera.h"
#include "jpeg_decoder.h"
#include "du_bsp_lcd.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"

static const char *TAG = "rtc_udp";

#define CONFIG_EXAMPLE_IPV4_ADDR "255.255.255.255"
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR
#define PORT 3333
#define MAX_UDP_PACKET_SIZE 1024
#define MAX_DISCARD_SIZE 1024 // 定义丢弃缓冲区的最大大小，根据实际情况进行调整

uint8_t discard_buffer[MAX_DISCARD_SIZE]; // 定义丢弃数据的缓冲区

// 定义同步信号
#define VEDIO_SYNC_SIGNAL 0xAA // 同步信号的数值
#define AUDIO_SYNC_SIGNAL 0xBB // 同步信号的数值
#define MAX_RECV_SIZE 1024

int sock = -1;
struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
socklen_t socklen = sizeof(source_addr);

static esp_err_t du_bsp_decode_image(const uint8_t *input_data, size_t input_size, uint16_t *output_pixels)
{
    esp_err_t ret = ESP_OK;

    // JPEG decode config
    esp_jpeg_image_cfg_t jpeg_cfg = {
        .indata = input_data,
        .indata_size = input_size,
        .outbuf = (uint8_t *)output_pixels,
        .outbuf_size = 320 * 240 * sizeof(uint16_t),
        .out_format = JPEG_IMAGE_FORMAT_RGB565,
        .out_scale = JPEG_IMAGE_SCALE_0,
        .flags = {
            .swap_color_bytes = 1,
        }};

    // JPEG decode
    esp_jpeg_image_output_t outimg;
    esp_jpeg_decode(&jpeg_cfg, &outimg);

    // ESP_LOGI(TAG, "JPEG image decoded! Size of the decoded image is: %dpx x %dpx", outimg.width, outimg.height);

    return ret;
}


static void receive_audio_data(multimedia_data_t *audio_video_data)
{
    while (1)
    {
        int received_len = recvfrom(sock, audio_video_data->audio_data, 1024, 0, (struct sockaddr *)&source_addr, &socklen);
        // ESP_LOGE(TAG, "receive data length.......:  %d", received_len);
        if (received_len > 0)
        {
            ESP_LOGE(TAG, "receive data length:  %d", received_len);
            esp_codec_dev_write(play_dev, audio_video_data->audio_data, 1024);
        }
        else
        {
            break;
        }
    }
}

// 将视频数据接受封装成一个函数
static void recieve_video_data(uint8_t *av_stream, multimedia_data_t *audio_video_data, int av_stream_size)
{
    int total_received = 0;
    while (total_received < av_stream_size)
    {
        int recv_size = (av_stream_size - total_received) > MAX_RECV_SIZE ? MAX_RECV_SIZE : (av_stream_size - total_received);
        int received_len = recvfrom(sock, av_stream + total_received, recv_size, 0, (struct sockaddr *)&source_addr, &socklen);
        if (received_len < 0)
        {
            ESP_LOGE(TAG, "Error receiving data: errno %d", errno);
            recvfrom(sock, discard_buffer, MAX_DISCARD_SIZE, 0, (struct sockaddr *)&source_addr, &socklen);
            vTaskDelay(30 / portTICK_PERIOD_MS); // 延时 15 毫秒
            // break;
        }
        else
        {
            total_received += received_len;
            vTaskDelay(10 / portTICK_PERIOD_MS); // 延时 15 毫秒
        }
    }
    du_bsp_decode_image(av_stream, total_received, audio_video_data->video_data);

    // udp_receive_lcd_show(pixels);
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 320, 240, audio_video_data->video_data);
}

void udp_server_task(void *pvParameters)
{
    multimedia_data_t *audio_video_data = (multimedia_data_t *)pvParameters;
    int ip_protocol = 0;
    struct sockaddr_in6 dest_addr;

    uint8_t *av_stream = calloc(9000, sizeof(uint8_t)); // 分配内存
    if (av_stream == NULL)
    {
        ESP_LOGE(TAG, "Failed to allocate memory");
    }

    while (1)
    {

        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(PORT);
        ip_protocol = IPPROTO_IP;

        sock = socket(AF_INET, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            // 创建socket失败，释放内存
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒再尝试
            continue;
        }
        ESP_LOGI(TAG, "Socket created");
        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0)
        {
            ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
            close(sock);                           // 关闭socket
            vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒再尝试
            continue;
        }

        while (1)
        {
            uint8_t received_sync_signal;
            if (recvfrom(sock, &received_sync_signal, sizeof(received_sync_signal), 0, NULL, NULL) < 0)
            {
                ESP_LOGE(TAG, "Failed to receive sync signal: errno %d", errno);
                continue; // 若未成功接收到同步信号，继续等待
            }
            // 判断是否收到了同步信号
            if (received_sync_signal == AUDIO_SYNC_SIGNAL)
            {
            }
            // 判断是否收到了同步信号
            if (received_sync_signal == VEDIO_SYNC_SIGNAL)
            {
                // 同步信号已接收，开始数据接收循环
                uint16_t data_len;
                if (recvfrom(sock, &data_len, sizeof(data_len), 0, NULL, NULL) < 0)
                {
                    ESP_LOGE(TAG, "Failed to receive data length: errno %d", errno);
                    continue; // 若未成功接收到数据长度，继续等待
                }
                recieve_video_data(av_stream, audio_video_data, data_len);
            }

            vTaskDelay(1000 / portTICK_PERIOD_MS); // 延时 100 毫秒
        }

        if (sock != -1)
        {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
}
