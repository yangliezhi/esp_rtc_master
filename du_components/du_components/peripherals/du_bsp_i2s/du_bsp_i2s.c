#include <stdio.h>
#include "du_bsp_i2s.h"
#include "driver/gpio.h"
#include "es7210.h"
#include "driver/i2s_tdm.h"

static const char *TAG = "DI_BSP_I2S";

#define CONFIG_BSP_I2S_NUM 1

/* Audio */
#define BSP_I2S_SCLK (GPIO_NUM_9)
#define BSP_I2S_MCLK (GPIO_NUM_16)
#define BSP_I2S_LCLK (GPIO_NUM_45)
#define BSP_I2S_DOUT (GPIO_NUM_8)  // To Codec ES8311
#define BSP_I2S_DSIN (GPIO_NUM_10) // From ADC ES7210
#define BSP_POWER_AMP_IO (GPIO_NUM_46)
#define BSP_MUTE_STATUS (GPIO_NUM_1)

i2s_chan_handle_t i2s_tx_chan = NULL;
i2s_chan_handle_t i2s_rx_chan = NULL;

#define BSP_I2S_GPIO_CFG       \
    {                          \
        .mclk = BSP_I2S_MCLK,  \
        .bclk = BSP_I2S_SCLK,  \
        .ws = BSP_I2S_LCLK,    \
        .dout = BSP_I2S_DOUT,  \
        .din = BSP_I2S_DSIN,   \
        .invert_flags = {      \
            .mclk_inv = false, \
            .bclk_inv = false, \
            .ws_inv = false,   \
        },                     \
    }


#define BSP_I2S_DUPLEX_MONO_CFG(_sample_rate)                                                         \
    {                                                                                                 \
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(_sample_rate),                                          \
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO), \
        .gpio_cfg = BSP_I2S_GPIO_CFG,                                                                 \
    }

esp_err_t bsp_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms)
{
    esp_err_t ret = ESP_OK;
    ret = i2s_channel_write(i2s_tx_chan, (char *)audio_buffer, len, bytes_written, timeout_ms);
    return ret;
}

esp_err_t bsp_i2s_reconfig_clk(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch)
{
    esp_err_t ret = ESP_OK;
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(rate),
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG((i2s_data_bit_width_t)bits_cfg, (i2s_slot_mode_t)ch),
        .gpio_cfg = BSP_I2S_GPIO_CFG,
    };

    ret |= i2s_channel_disable(i2s_tx_chan);
    ret |= i2s_channel_reconfig_std_clock(i2s_tx_chan, &std_cfg.clk_cfg);
    ret |= i2s_channel_reconfig_std_slot(i2s_tx_chan, &std_cfg.slot_cfg);
    ret |= i2s_channel_enable(i2s_tx_chan);
    return ret;
}

esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting)
{
    ESP_LOGI(TAG, "mute setting %d", setting);
    return ESP_OK;
}

esp_err_t bsp_audio_init(const i2s_std_config_t *i2s_config, i2s_chan_handle_t *tx_channel, i2s_chan_handle_t *rx_channel)
{
    /* Setup I2S peripheral */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(CONFIG_BSP_I2S_NUM, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true; // Auto clear the legacy data in the DMA buffer
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, tx_channel, rx_channel));

    /* Setup I2S channels */
    const i2s_std_config_t std_cfg_default = BSP_I2S_DUPLEX_MONO_CFG(22050);
    const i2s_std_config_t *p_i2s_cfg = &std_cfg_default;
    if (i2s_config != NULL)
    {
        p_i2s_cfg = i2s_config;
    }

    if (tx_channel != NULL)
    {
        ESP_ERROR_CHECK(i2s_channel_init_std_mode(*tx_channel, p_i2s_cfg));
        ESP_ERROR_CHECK(i2s_channel_enable(*tx_channel));
    }
    if (rx_channel != NULL)
    {
        ESP_ERROR_CHECK(i2s_channel_init_std_mode(*rx_channel, p_i2s_cfg));
        ESP_ERROR_CHECK(i2s_channel_enable(*rx_channel));
    }

    /* Setup power amplifier pin */
    const gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = BIT64(BSP_POWER_AMP_IO),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLDOWN_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    return ESP_OK;
}
// #include "du_bsp_es7010.h"
// static i2s_chan_handle_t es7210_i2s_init(void)
// {
//     i2s_chan_handle_t i2s_rx_chan = NULL;
//     ESP_LOGI(TAG, "Create I2S receive channel");
//     i2s_chan_config_t i2s_rx_conf = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
//     ESP_ERROR_CHECK(i2s_new_channel(&i2s_rx_conf, NULL, &i2s_rx_chan));

//     ESP_LOGI(TAG, "Configure I2S receive channel to TDM mode");
//     i2s_tdm_config_t i2s_tdm_rx_conf = {
// #if EXAMPLE_I2S_FORMAT == ES7210_I2S_FMT_I2S
//         .slot_cfg = I2S_TDM_PHILIPS_SLOT_DEFAULT_CONFIG(EXAMPLE_I2S_SAMPLE_BITS, I2S_SLOT_MODE_STEREO, EXAMPLE_I2S_TDM_SLOT_MASK),
// #elif EXAMPLE_I2S_FORMAT == ES7210_I2S_FMT_LJ
//         .slot_cfg = I2S_TDM_MSB_SLOT_DEFAULT_CONFIG(EXAMPLE_I2S_SAMPLE_BITS, I2S_SLOT_MODE_STEREO, EXAMPLE_I2S_TDM_SLOT_MASK),
// #elif EXAMPLE_I2S_FORMAT == ES7210_I2S_FMT_DSP_A
//         .slot_cfg = I2S_TDM_PCM_SHORT_SLOT_DEFAULT_CONFIG(EXAMPLE_I2S_SAMPLE_BITS, I2S_SLOT_MODE_STEREO, EXAMPLE_I2S_TDM_SLOT_MASK),
// #elif EXAMPLE_I2S_FORMAT == ES7210_I2S_FMT_DSP_B
//         .slot_cfg = I2S_TDM_PCM_LONG_SLOT_DEFAULT_CONFIG(EXAMPLE_I2S_SAMPLE_BITS, I2S_SLOT_MODE_STEREO, EXAMPLE_I2S_TDM_SLOT_MASK),
// #endif
//         .clk_cfg = {
//             .clk_src = I2S_CLK_SRC_DEFAULT,
//             .sample_rate_hz = EXAMPLE_I2S_SAMPLE_RATE,
//             .mclk_multiple = EXAMPLE_I2S_MCLK_MULTIPLE},
//         .gpio_cfg = {.mclk = BSP_I2S_MCLK, .bclk = BSP_I2S_SCLK, .ws = BSP_I2S_LCLK,
//                      .dout = -1, // ES7210 only has ADC capability
//                      .din = BSP_I2S_DSIN},
//     };

//     ESP_ERROR_CHECK(i2s_channel_init_tdm_mode(i2s_rx_chan, &i2s_tdm_rx_conf));

//     return i2s_rx_chan;
// }
