#ifndef __DU_BSP_I2S__
#define __DU_BSP_I2S__
#include "esp_log.h"
#include "esp_check.h"
#include <stdio.h>

#include "audio_player.h"
extern i2s_chan_handle_t i2s_tx_chan;
extern i2s_chan_handle_t i2s_rx_chan;

esp_err_t bsp_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms);
esp_err_t bsp_i2s_reconfig_clk(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch);
esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting);
esp_err_t bsp_audio_init(const i2s_std_config_t *i2s_config, i2s_chan_handle_t *tx_channel, i2s_chan_handle_t *rx_channel);
#endif