#include <stdio.h>
#include "du_bsp_decode_jpeg.h"

#include "jpeg_decoder.h"
#include "esp_log.h"
#include "esp_check.h"
#include <string.h>
#include "freertos/FreeRTOS.h"

// Reference the binary-included jpeg file
extern const uint8_t image_jpg_start[] asm("_binary_image_jpg_start");
extern const uint8_t image_jpg_end[] asm("_binary_image_jpg_end");
// Define the height and width of the jpeg file. Make sure this matches the actual jpeg
// dimensions.

const char *TAG = "ImageDec";

// Decode the embedded image into pixel lines that can be used with the rest of the logic.
esp_err_t decode_image(uint16_t **pixels)
{

    esp_err_t ret = ESP_OK;
    esp_jpeg_image_cfg_t jpeg_cfg = {
        .indata = (uint8_t *)image_jpg_start,
        .indata_size = image_jpg_end - image_jpg_start,
        .outbuf = (uint8_t *)(*pixels),
        .outbuf_size = IMAGE_W * IMAGE_H * sizeof(uint16_t),
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


esp_err_t du_bsp_decode_image(const uint16_t *input_data, size_t input_size, uint16_t *output_pixels)
{
    esp_err_t ret = ESP_OK;

    // JPEG decode config
    esp_jpeg_image_cfg_t jpeg_cfg = {
        .indata = input_data,
        .indata_size = input_size,
        .outbuf = (uint8_t *)output_pixels,
        .outbuf_size = IMAGE_W * IMAGE_H * sizeof(uint16_t),
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
