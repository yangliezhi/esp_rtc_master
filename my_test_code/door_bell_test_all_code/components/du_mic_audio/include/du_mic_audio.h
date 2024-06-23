#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "esp_idf_version.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "esp_codec_dev_os.h"
#include "audio_player.h"

#define FUNC_I2C_EN (1)
#define I2C_NUM (0)
#define I2C_CLK (100000)
#define GPIO_I2C_SCL (GPIO_NUM_18)
#define GPIO_I2C_SDA (GPIO_NUM_17)

#define FUNC_I2S_EN (1)
#define GPIO_I2S_LRCK (GPIO_NUM_45)
#define GPIO_I2S_MCLK (GPIO_NUM_16)
#define GPIO_I2S_SCLK (GPIO_NUM_9)
#define GPIO_I2S_SDIN (GPIO_NUM_10)
#define GPIO_I2S_DOUT (GPIO_NUM_8)

#define RECORD_VOLUME (70.0)
/**
 * @brief player configurations
 *
 */
#define PLAYER_VOLUME (100)

/**
 * @brief ESP32-S3-HMI-DevKit power control IO
 *
 * @note Some power control pins might not be listed yet
 *
 */
#define FUNC_PWR_CTRL (1)
#define GPIO_PWR_CTRL (GPIO_NUM_48)
#define GPIO_PWR_ON_LEVEL (1)

#define I2S_CONFIG_DEFAULT(sample_rate, channel_fmt, bits_per_chan)                \
    {                                                                              \
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),                              \
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(32, I2S_SLOT_MODE_STEREO), \
        .gpio_cfg = {                                                              \
            .mclk = GPIO_I2S_MCLK,                                                 \
            .bclk = GPIO_I2S_SCLK,                                                 \
            .ws = GPIO_I2S_LRCK,                                                   \
            .dout = GPIO_I2S_DOUT,                                                 \
            .din = GPIO_I2S_SDIN,                                                  \
        },                                                                         \
    }

#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t bsp_board_init(uint32_t sample_rate, int channel_format, int bits_per_chan);

    esp_err_t bsp_audio_play(const int16_t *data, int length, TickType_t ticks_to_wait);

    esp_err_t bsp_get_feed_data(bool is_get_raw_channel, int16_t *buffer, int buffer_len);
    esp_err_t bsp_i2s_read(void *audio_buffer, size_t len, size_t *bytes_read, uint32_t timeout_ms);
    esp_err_t bsp_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms);
    esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting);

#ifdef __cplusplus
}
#endif
