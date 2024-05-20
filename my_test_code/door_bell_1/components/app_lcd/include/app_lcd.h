#pragma once
#include "lvgl.h"
#include "esp_err.h"
#include "esp_log.h"
#define EXAMPLE_LCD_H_RES   (240)
#define EXAMPLE_LCD_V_RES   (320)
/* LCD settings */
#define EXAMPLE_LCD_SPI_NUM         (SPI3_HOST)
#define EXAMPLE_LCD_PIXEL_CLK_HZ    (40 * 1000 * 1000)
#define EXAMPLE_LCD_CMD_BITS        (8)
#define EXAMPLE_LCD_PARAM_BITS      (8)
#define EXAMPLE_LCD_COLOR_SPACE     (ESP_LCD_COLOR_SPACE_RGB)
#define EXAMPLE_LCD_BITS_PER_PIXEL  (16)
#define EXAMPLE_LCD_DRAW_BUFF_DOUBLE (1)
#define EXAMPLE_LCD_DRAW_BUFF_HEIGHT (50)
#define EXAMPLE_LCD_BL_ON_LEVEL     (1)

/* LCD pins */
#define EXAMPLE_LCD_GPIO_SCLK       (GPIO_NUM_1)
#define EXAMPLE_LCD_GPIO_MOSI       (GPIO_NUM_0)
#define EXAMPLE_LCD_GPIO_RST        (-1)
#define EXAMPLE_LCD_GPIO_DC         (GPIO_NUM_2)
#define EXAMPLE_LCD_GPIO_CS         (GPIO_NUM_46)
#define EXAMPLE_LCD_GPIO_BL         (GPIO_NUM_45)

/* Touch settings */
#define EXAMPLE_TOUCH_I2C_NUM       (0)
#define EXAMPLE_TOUCH_I2C_CLK_HZ    (100000)

/* LCD touch pins */
#define EXAMPLE_TOUCH_I2C_SCL       (GPIO_NUM_18)
#define EXAMPLE_TOUCH_I2C_SDA       (GPIO_NUM_17)
// #define EXAMPLE_TOUCH_GPIO_INT      (GPIO_NUM_3)
#define EXAMPLE_TOUCH_GPIO_INT      (-1)

extern lv_disp_t *lvgl_disp;
esp_err_t app_lcd_init(void);
esp_err_t app_touch_init(void);
esp_err_t app_lvgl_init(void);
void app_lcd_run(void);