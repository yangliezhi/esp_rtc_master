/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-06-19 22:51:48
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-06-19 23:02:28
 */
#include <stdio.h>
#include <math.h>
#include "esp_log.h"

#include "esp_heap_caps.h"

#include "du_decode_jpg.h"
#include "du_decode_image.h"

#define PARALLEL_LINES 16

uint16_t *pixels ;
static int8_t xofs[320], yofs[240];
static int8_t xcomp[320], ycomp[240];
static uint16_t *s_lines[2];
static inline uint16_t get_bgnd_pixel(int x, int y)
{
    return *(((uint16_t *)pixels) + y * 320 + x);
}

static void pretty_effect_calc_lines(uint16_t *dest, int line, int linect)
{

    // 不进行任何偏移
    for (int x = 0; x < 320; x++)
    {
        xofs[x] = 0;
        xcomp[x] = 0;
    }
    for (int y = 0; y < 240; y++)
    {
        yofs[y] = 0;
        ycomp[y] = 0;
    }

    for (int y = line; y < line + linect; y++)
    {
        for (int x = 0; x < 320; x++)
        {
            *dest++ = get_bgnd_pixel(x + yofs[y] + xcomp[x], y + xofs[x] + ycomp[y]);
        }
    }
}
esp_err_t pretty_effect_init(const char *filename)
{
    return decode_image(&pixels, filename);
}

void display_pretty_colors(esp_lcd_panel_handle_t panel_handle)
{
    // Indexes of the line currently being sent to the LCD and the line we're calculating
    int sending_line = 0;
    int calc_line = 0;
    static bool first_loop = true; // 添加一个静态的标志变量

    if (first_loop)
    {
        for (int i = 0; i < 2; i++)
        {
            s_lines[i] = heap_caps_malloc(LCD_H_RES * PARALLEL_LINES * sizeof(uint16_t), MALLOC_CAP_DMA);
            assert(s_lines[i] != NULL);
        }
        first_loop = false; // 设置标志变量，确保循环只执行一次
    }

    for (int y = 0; y < LCD_V_RES; y += PARALLEL_LINES)
    {
        // Calculate a line
        pretty_effect_calc_lines(s_lines[calc_line], y, PARALLEL_LINES);
        sending_line = calc_line;
        calc_line = !calc_line;
        // Send the calculated data
        esp_lcd_panel_draw_bitmap(panel_handle, 0, y, 0 + LCD_H_RES, y + PARALLEL_LINES, s_lines[sending_line]);
    }
}
