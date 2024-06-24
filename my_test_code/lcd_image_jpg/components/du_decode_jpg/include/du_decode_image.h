/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-06-19 22:51:59
 * @Last Modified by:   dujianmin
 * @Last Modified time: 2024-06-19 22:51:59
 */

#pragma once
#include <stdint.h>
#include "esp_err.h"
#define LCD_H_RES 320
#define LCD_V_RES 240

esp_err_t decode_image(uint16_t **pixels, const char *filename);
