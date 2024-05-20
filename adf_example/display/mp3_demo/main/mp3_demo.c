/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-05-12 01:01:51
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-12 01:43:11
 */

#include "audio_player.h"
#include "bsp/esp-bsp.h"
#include "esp_check.h"
#include "esp_log.h"
#include "file_iterator.h"
#include "ui_audio.h"
#include "bsp_board.h"

#include "bsp_gpio_out.h"
#include "du_bsp_tca9554.h"
#include "du_bsp_sd_card.h"

static esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting)
{
    // Volume saved when muting and restored when unmuting. Restoring volume is necessary
    // as es8311_set_voice_mute(true) results in voice volume (REG32) being set to zero.
    uint8_t volume = get_sys_volume();

    bsp_codec_mute_set(setting == AUDIO_PLAYER_MUTE ? true : false);

    // restore the voice volume upon unmuting
    if (setting == AUDIO_PLAYER_UNMUTE)
    {
        bsp_codec_volume_set(volume, NULL);
    }

    return ESP_OK;
}

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);
    /* Initialize I2C (for touch and audio) */
    bsp_i2c_init();
    tca9554_init();
    /* Initialize display and LVGL */
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_H_RES * CONFIG_BSP_LCD_DRAW_BUF_HEIGHT,
        .double_buffer = 0,
        .flags = {
            .buff_dma = true,
        }};
    bsp_display_start_with_config(&cfg);

    /* Set display brightness to 100% */
    bsp_display_backlight_on();

    bsp_spiffs_mount();
    mount_sdcard();
    file_iterator_instance_t *file_iterator = file_iterator_new(CONFIG_BSP_SD_MOUNT_POINT);
    // file_iterator_instance_t *file_iterator = file_iterator_new(BSP_SPIFFS_MOUNT_POINT);
    assert(file_iterator != NULL);

    /* Configure I2S peripheral and Power Amplifier */
    bsp_board_init();

    audio_player_config_t config = {.mute_fn = audio_mute_function,
                                    .write_fn = bsp_i2s_write,
                                    .clk_set_fn = bsp_codec_set_fs,
                                    .priority = 1};
    ESP_ERROR_CHECK(audio_player_new(config));

    ui_audio_start(file_iterator);
}
