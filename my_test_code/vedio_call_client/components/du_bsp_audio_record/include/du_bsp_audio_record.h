/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _TEST_BOARD_H_
#define _TEST_BOARD_H_

#include "driver/i2c.h"
#include "esp_idf_version.h"
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "driver/i2s_std.h"
#include "driver/i2s_tdm.h"
#include "soc/soc_caps.h"
#else
#include "driver/i2s.h"
#endif
#include "esp_codec_dev.h"
#include "esp_codec_dev_defaults.h"

#include "du_bsp_udp_client.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Codec configuration by ESP32S3_KORVO2_V3
 */
#define TEST_BOARD_I2C_SDA_PIN (17)
#define TEST_BOARD_I2C_SCL_PIN (18)

#define TEST_BOARD_I2S_BCK_PIN (9)
#define TEST_BOARD_I2S_MCK_PIN (16)
#define TEST_BOARD_I2S_DATA_IN_PIN (10)
#define TEST_BOARD_I2S_DATA_OUT_PIN (8)
#define TEST_BOARD_I2S_DATA_WS_PIN (45)

#define TEST_BOARD_PA_PIN (48)

extern esp_codec_dev_handle_t play_dev;
extern esp_codec_dev_handle_t record_dev;

int ut_i2c_init(uint8_t port);
void audio_recorded_init(void);

#ifdef __cplusplus
}
#endif

#endif
