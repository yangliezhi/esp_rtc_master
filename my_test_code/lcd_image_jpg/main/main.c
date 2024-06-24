#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "du_bsp_tca9554.h"

#include "du_bsp_spiffs.h"

#include "du_bsp_lcd.h"

#include "du_decode_jpg.h"
extern esp_lcd_panel_handle_t panel_handle;

void app_main(void)
{
    // ESP_ERROR_CHECK(bsp_board_init(16000, 1, 16));
    bsp_spiffs_mount();
    // mount_sdcard();
    // tca9554_init();
    du_bsp_lcd_init();
    pretty_effect_init("/spiffs/image.jpg");
    display_pretty_colors(panel_handle);
    // lv_obj_clean(lv_scr_act()); // 清空当前屏幕
    // du_display_png("A:/spiffs/cat1.png");

    // du_sr_speech(true);
}
