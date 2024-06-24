/*
 * @Author: dujianmin@qq:20130527 
 * @Date: 2024-06-19 22:23:49 
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-06-19 22:53:51
 */

#pragma once
#include <stdint.h>
#include "esp_err.h"
#include "esp_lcd_panel_ops.h"

esp_err_t pretty_effect_init(const char *filename);

void display_pretty_colors(esp_lcd_panel_handle_t panel_handle);