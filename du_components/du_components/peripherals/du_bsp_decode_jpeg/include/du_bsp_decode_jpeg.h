/*
 * @Author: dujianmin@qq:20130527 
 * @Date: 2024-05-03 20:39:42 
 * @Last Modified by:   dujianmin 
 * @Last Modified time: 2024-05-03 20:39:42 
 */

#pragma once
#include <stdint.h>
#include "esp_err.h"

#define IMAGE_W 320
#define IMAGE_H 240


esp_err_t decode_image(uint16_t **pixels);
esp_err_t du_bsp_decode_image(const uint16_t *input_data, size_t input_size, uint16_t *output_pixels);