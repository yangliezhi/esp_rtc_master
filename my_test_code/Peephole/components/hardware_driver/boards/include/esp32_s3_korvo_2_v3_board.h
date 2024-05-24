
#pragma once

#include "driver/gpio.h"
#include "esp_idf_version.h"
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"
#include "esp_codec_dev_os.h"

/**
 * @brief ESP32-S3-KORVO-2-V3.0 I2C GPIO defineation
 *
 */
#define FUNC_I2C_EN (1)
#define I2C_NUM (0)
#define I2C_CLK (100000)
#define GPIO_I2C_SCL (GPIO_NUM_18)
#define GPIO_I2C_SDA (GPIO_NUM_17)

/**
 * @brief ESP32-S3-KORVO-2-V3.0 SDMMC GPIO defination
 *
 * @note Only avaliable when PMOD connected
 */
#define FUNC_SDMMC_EN (1)
#define SDMMC_BUS_WIDTH (1)
#define GPIO_SDMMC_CLK (GPIO_NUM_15)
#define GPIO_SDMMC_CMD (GPIO_NUM_7)
#define GPIO_SDMMC_D0 (GPIO_NUM_4)
#define GPIO_SDMMC_D1 (GPIO_NUM_NC)
#define GPIO_SDMMC_D2 (GPIO_NUM_NC)
#define GPIO_SDMMC_D3 (GPIO_NUM_NC)
#define GPIO_SDMMC_DET (GPIO_NUM_NC)

/**
 * @brief ESP32-S3-KORVO-2-V3.0 SDSPI GPIO definationv
 *
 */
#define FUNC_SDSPI_EN (0)
#define SDSPI_HOST (SPI2_HOST)
#define GPIO_SDSPI_CS (GPIO_NUM_NC)
#define GPIO_SDSPI_SCLK (GPIO_NUM_NC)
#define GPIO_SDSPI_MISO (GPIO_NUM_NC)
#define GPIO_SDSPI_MOSI (GPIO_NUM_NC)

/**
 * @brief ESP32-S3-KORVO-2-V3.0 I2S GPIO defination
 *
 */
#define FUNC_I2S_EN (1)
#define GPIO_I2S_LRCK (GPIO_NUM_45)
#define GPIO_I2S_MCLK (GPIO_NUM_16)
#define GPIO_I2S_SCLK (GPIO_NUM_9)
#define GPIO_I2S_SDIN (GPIO_NUM_10)
#define GPIO_I2S_DOUT (GPIO_NUM_8)

/**
 * @brief ESP32-S3-KORVO-2-V3.0 I2S GPIO defination
 *
 */
#define FUNC_I2S0_EN (0)
#define GPIO_I2S0_LRCK (GPIO_NUM_NC)
#define GPIO_I2S0_MCLK (GPIO_NUM_NC)
#define GPIO_I2S0_SCLK (GPIO_NUM_NC)
#define GPIO_I2S0_SDIN (GPIO_NUM_NC)
#define GPIO_I2S0_DOUT (GPIO_NUM_NC)

#define RECORD_VOLUME (30.0)
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


