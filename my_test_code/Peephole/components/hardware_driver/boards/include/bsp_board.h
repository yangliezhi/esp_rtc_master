/*
 * @Author: 都建民 
 * @Date: 2024-03-20 17:45:14 
 * @Last Modified by:   dujianmin qq群 26875961 
 * @Last Modified time: 2024-03-20 17:45:14 
 */


#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "esp32_s3_korvo_2_v3_board.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Power module of dev board. This can be expanded in the future.
     *
     */
    typedef enum
    {
        POWER_MODULE_LCD = 1,    /*!< LCD power control */
        POWER_MODULE_AUDIO,      /*!< Audio PA power control */
        POWER_MODULE_ALL = 0xff, /*!< All module power control */
    } power_module_t;

    /**
     * @brief Special config for dev board
     *
     * @return
     *    - ESP_OK: Success
     *    - Others: Fail
     */
    esp_err_t bsp_board_init(uint32_t sample_rate, int channel_format, int bits_per_chan);

    esp_err_t bsp_audio_play(const int16_t *data, int length, TickType_t ticks_to_wait);

    /**
     * @brief Get the record pcm data.
     *
     * @param is_get_raw_channel Whether to get the recording data of the original number of channels.
     *                           Otherwise, the corresponding number of channels will be filtered based on the board.
     * @param buffer The buffer where the data is stored.
     * @param buffer_len The buffer length.
     * @return
     *    - ESP_OK                  Success
     *    - Others                  Fail
     */
    esp_err_t bsp_get_feed_data(bool is_get_raw_channel, int16_t *buffer, int buffer_len);

    int bsp_get_feed_channel(void);

    /**
     * @brief Set play volume
     *
     * @return
     *    - ESP_OK: Success
     *    - Others: Fail
     */
    esp_err_t bsp_audio_set_play_vol(int volume);

    /**
     * @brief Get play volume
     *
     * @return
     *    - ESP_OK: Success
     *    - Others: Fail
     */
    esp_err_t bsp_audio_get_play_vol(int *volume);

    void esp_sr_audio_play(void);
    void app_play_index(int index);
    void app_stop_index(void);

#ifdef __cplusplus
}
#endif
