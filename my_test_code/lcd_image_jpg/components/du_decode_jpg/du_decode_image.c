/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-06-19 22:51:53
 * @Last Modified by:   dujianmin
 * @Last Modified time: 2024-06-19 22:51:53
 */

#include "du_decode_image.h"
#include "esp_log.h"
// #include "esp_jpeg_dec.h"
// #include "esp_jpeg_common.h"
#include "esp_heap_caps.h"

#include "esp_log.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "jpeg_decoder.h"
#include "esp_spiffs.h"
const char *TAG = "ImageDec";

// 定义全局变量用于存放图片数据的指针和长度
uint8_t *image_data_ptr = NULL;
int image_data_len = 0;

static void read_image_from_spiffs(const char *filename)
{

    // Open image file
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("Failed to open file for reading\n");
        return;
    }

    // Read image data
    fseek(f, 0, SEEK_END);
    image_data_len = ftell(f);
    fseek(f, 0, SEEK_SET);

    image_data_ptr = (uint8_t *)malloc(image_data_len);
    fread(image_data_ptr, 1, image_data_len, f);

    // Clean up
    fclose(f);
    // esp_vfs_spiffs_unregister(NULL);
}

// int decode_image(uint16_t **pixels, const char *filename)
// {
//     read_image_from_spiffs(filename);
//     // Generate default configuration
//     jpeg_dec_config_t config = DEFAULT_JPEG_DEC_CONFIG();
//     config.output_type = JPEG_RAW_TYPE_RGB565_BE;
//     // Empty handle to jpeg_decoder
//     jpeg_dec_handle_t jpeg_dec = NULL;
//     // Create jpeg_dec
//     jpeg_dec = jpeg_dec_open(&config);
//     // Create io_callback handle
//     jpeg_dec_io_t *jpeg_io = calloc(1, sizeof(jpeg_dec_io_t));
//     if (jpeg_io == NULL)
//     {
//         return ESP_FAIL;
//     }

//     // Create out_info handle
//     jpeg_dec_header_info_t *out_info = calloc(1, sizeof(jpeg_dec_header_info_t));
//     if (out_info == NULL)
//     {
//         return ESP_FAIL;
//     }

//     // Set input buffer and buffer len to io_callback
//     jpeg_io->inbuf = image_data_ptr;
//     jpeg_io->inbuf_len = image_data_len;

//     int ret = 0;
//     // Parse jpeg picture header and get picture for user and decoder
//     ret = jpeg_dec_parse_header(jpeg_dec, jpeg_io, out_info);
//     if (ret < 0)
//     {
//         ESP_LOGE(TAG, "Got an error by jpeg_dec_parse_header, ret:%d", ret);
//         return ret;
//     }
//     // Calloc out_put data buffer and update inbuf ptr and inbuf_len
//     int outbuf_len;
//     if (config.output_type == JPEG_RAW_TYPE_RGB565_LE || config.output_type == JPEG_RAW_TYPE_RGB565_BE)
//     {
//         outbuf_len = out_info->height * out_info->width * 2;
//     }
//     else if (config.output_type == JPEG_RAW_TYPE_RGB888)
//     {
//         outbuf_len = out_info->height * out_info->width * 3;
//     }
//     else
//     {
//         return ESP_FAIL;
//     }
//     ESP_LOGI(TAG, "The image size is %d bytes, width:%d, height:%d", outbuf_len, out_info->width, out_info->height);
//     unsigned char *out_buf = jpeg_malloc_align(outbuf_len, 16);
//     jpeg_io->outbuf = out_buf;
//     int inbuf_consumed = jpeg_io->inbuf_len - jpeg_io->inbuf_remain;
//     jpeg_io->inbuf = (unsigned char *)(image_data_ptr + inbuf_consumed);
//     jpeg_io->inbuf_len = jpeg_io->inbuf_remain;

//     // Start decode jpeg raw data
//     ret = jpeg_dec_process(jpeg_dec, jpeg_io);
//     if (ret < 0)
//     {
//         ESP_LOGE(TAG, "Got an error by jpeg_dec_process, ret:%d", ret);
//         return ret;
//     }
//     *pixels = (uint16_t **)out_buf;
//     // Decoder deinitialize
//     jpeg_dec_close(jpeg_dec);
//     free(out_info);
//     free(jpeg_io);
//     return ESP_OK;
// }
extern const uint8_t image_jpg_start[] asm("_binary_image_jpg_start");
extern const uint8_t image_jpg_end[] asm("_binary_image_jpg_end");

esp_err_t decode_image(uint16_t **pixels, const char *filename)
{

    // read_image_from_spiffs(filename);
    esp_err_t ret = ESP_OK;

    // Alocate pixel memory. Each line is an array of IMAGE_W 16-bit pixels; the `*pixels` array itself contains pointers to these lines.
    // *pixels = calloc(240 * 320, sizeof(uint16_t));
    *pixels = heap_caps_malloc(320 *240 * sizeof(uint16_t), MALLOC_CAP_DMA);
    ESP_GOTO_ON_FALSE((*pixels), ESP_ERR_NO_MEM, err, TAG, "Error allocating memory for lines");

    // JPEG decode config
    esp_jpeg_image_cfg_t jpeg_cfg = {
        .indata = (uint8_t *)image_jpg_start,
        .indata_size = image_jpg_end - image_jpg_start,
        .outbuf = (uint8_t *)(*pixels),
        .outbuf_size = 320 * 240  *sizeof(uint16_t),
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
err:
    // Something went wrong! Exit cleanly, de-allocating everything we allocated.
    if (*pixels != NULL)
    {
        free(*pixels);
    }
    return ret;
}
