#include <stdio.h>
#include "du_bsp_audio_record.h"
#include "du_bsp_tca9554.h"
#define I2S_MAX_KEEP SOC_I2S_NUM

esp_codec_dev_handle_t record_dev = NULL;
esp_codec_dev_handle_t play_dev = NULL;

static i2s_comm_mode_t i2s_in_mode = I2S_COMM_MODE_STD;
static i2s_comm_mode_t i2s_out_mode = I2S_COMM_MODE_STD;
static i2s_keep_t *i2s_keep[I2S_MAX_KEEP];

int ut_i2c_init(uint8_t port)
{
    i2c_config_t i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    i2c_cfg.sda_io_num = TEST_BOARD_I2C_SDA_PIN;
    i2c_cfg.scl_io_num = TEST_BOARD_I2C_SCL_PIN;
    esp_err_t ret = i2c_param_config(port, &i2c_cfg);
    if (ret != ESP_OK)
    {
        return -1;
    }
    return i2c_driver_install(port, i2c_cfg.mode, 0, 0, 0);
}

static int ut_i2c_deinit(uint8_t port)
{
    return i2c_driver_delete(port);
}

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
static void ut_set_i2s_mode(i2s_comm_mode_t out_mode, i2s_comm_mode_t in_mode)
{
    i2s_in_mode = in_mode;
    i2s_out_mode = out_mode;
}

static void ut_clr_i2s_mode(void)
{
    i2s_in_mode = I2S_COMM_MODE_STD;
    i2s_out_mode = I2S_COMM_MODE_STD;
}
#endif

static int ut_i2s_init(uint8_t port)
{

    if (port >= I2S_MAX_KEEP)
    {
        return -1;
    }
    // Already installed
    if (i2s_keep[port])
    {
        return 0;
    }
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(16, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = TEST_BOARD_I2S_MCK_PIN,
            .bclk = TEST_BOARD_I2S_BCK_PIN,
            .ws = TEST_BOARD_I2S_DATA_WS_PIN,
            .dout = TEST_BOARD_I2S_DATA_OUT_PIN,
            .din = TEST_BOARD_I2S_DATA_IN_PIN,
        },
    };
    i2s_keep[port] = (i2s_keep_t *)calloc(1, sizeof(i2s_keep_t));
    if (i2s_keep[port] == NULL)
    {
        return -1;
    }
    i2s_tdm_slot_mask_t slot_mask = I2S_TDM_SLOT0 | I2S_TDM_SLOT1 | I2S_TDM_SLOT2 | I2S_TDM_SLOT3;
    i2s_tdm_config_t tdm_cfg = {
        .slot_cfg = I2S_TDM_PHILIPS_SLOT_DEFAULT_CONFIG(16, I2S_SLOT_MODE_STEREO, slot_mask),
        .clk_cfg = I2S_TDM_CLK_DEFAULT_CONFIG(16000),
        .gpio_cfg = {
            .mclk = TEST_BOARD_I2S_MCK_PIN,
            .bclk = TEST_BOARD_I2S_BCK_PIN,
            .ws = TEST_BOARD_I2S_DATA_WS_PIN,
            .dout = TEST_BOARD_I2S_DATA_OUT_PIN,
            .din = TEST_BOARD_I2S_DATA_IN_PIN,
        },
    };
    tdm_cfg.slot_cfg.total_slot = 4;
    int ret = i2s_new_channel(&chan_cfg, &i2s_keep[port]->tx_handle, &i2s_keep[port]->rx_handle);

    if (i2s_out_mode == I2S_COMM_MODE_STD)
    {
        ret = i2s_channel_init_std_mode(i2s_keep[port]->tx_handle, &std_cfg);
    }
    else if (i2s_out_mode == I2S_COMM_MODE_TDM)
    {
        ret = i2s_channel_init_tdm_mode(i2s_keep[port]->tx_handle, &tdm_cfg);
    }

    if (i2s_in_mode == I2S_COMM_MODE_STD)
    {
        ret = i2s_channel_init_std_mode(i2s_keep[port]->rx_handle, &std_cfg);
    }
    else if (i2s_in_mode == I2S_COMM_MODE_TDM)
    {
        ret = i2s_channel_init_tdm_mode(i2s_keep[port]->rx_handle, &tdm_cfg);
    }

    // For tx master using duplex mode
    i2s_channel_enable(i2s_keep[port]->tx_handle);

    return ret;
}

static int ut_i2s_deinit(uint8_t port)
{

    if (port >= I2S_MAX_KEEP)
    {
        return -1;
    }
    // already installed
    if (i2s_keep[port] == NULL)
    {
        return 0;
    }
    i2s_channel_disable(i2s_keep[port]->tx_handle);
    i2s_channel_disable(i2s_keep[port]->rx_handle);
    i2s_del_channel(i2s_keep[port]->tx_handle);
    i2s_del_channel(i2s_keep[port]->rx_handle);
    free(i2s_keep[port]);
    i2s_keep[port] = NULL;

    return 0;
}

static int codec_max_sample(uint8_t *data, int size)
{
    int16_t *s = (int16_t *)data;
    size >>= 1;
    int i = 0, max = 0;
    while (i < size)
    {
        if (s[i] > max)
        {
            max = s[i];
        }
        i++;
    }
    return max;
}

void audio_recorded_init(void)
{
    int ret = ut_i2c_init(0);
    tca9554_init();
    ret = ut_i2s_init(0);

    // Do initialize of related interface: data_if, ctrl_if and gpio_if
    audio_codec_i2s_cfg_t i2s_cfg = {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
        .rx_handle = i2s_keep[0]->rx_handle,
        .tx_handle = i2s_keep[0]->tx_handle,
#endif
    };
    const audio_codec_data_if_t *data_if = audio_codec_new_i2s_data(&i2s_cfg);

    audio_codec_i2c_cfg_t i2c_cfg = {.addr = ES8311_CODEC_DEFAULT_ADDR};
    const audio_codec_ctrl_if_t *out_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);

    i2c_cfg.addr = ES7210_CODEC_DEFAULT_ADDR;
    const audio_codec_ctrl_if_t *in_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);

    const audio_codec_gpio_if_t *gpio_if = audio_codec_new_gpio();

    // New output codec interface
    es8311_codec_cfg_t es8311_cfg = {
        .codec_mode = ESP_CODEC_DEV_WORK_MODE_DAC,
        .ctrl_if = out_ctrl_if,
        .gpio_if = gpio_if,
        .pa_pin = TEST_BOARD_PA_PIN,
        .use_mclk = true,
    };
    const audio_codec_if_t *out_codec_if = es8311_codec_new(&es8311_cfg);

    // New input codec interface
    es7210_codec_cfg_t es7210_cfg = {
        .ctrl_if = in_ctrl_if,
        .mic_selected = ES7120_SEL_MIC1 | ES7120_SEL_MIC2};
    const audio_codec_if_t *in_codec_if = es7210_codec_new(&es7210_cfg);

    // New output codec device
    esp_codec_dev_cfg_t dev_cfg = {
        .codec_if = out_codec_if,
        .data_if = data_if,
        .dev_type = ESP_CODEC_DEV_TYPE_OUT,
    };
    play_dev = esp_codec_dev_new(&dev_cfg);

    // New input codec device
    dev_cfg.codec_if = in_codec_if;
    dev_cfg.dev_type = ESP_CODEC_DEV_TYPE_IN;
    record_dev = esp_codec_dev_new(&dev_cfg);

    ret = esp_codec_dev_set_out_vol(play_dev, 60.0);

    ret = esp_codec_dev_set_in_gain(record_dev, 90.0);

    esp_codec_dev_sample_info_t fs = {
        .sample_rate = 16000,
        .channel = 1,
        .bits_per_sample = 32,
    };
    ret = esp_codec_dev_open(play_dev, &fs);

    ret = esp_codec_dev_open(record_dev, &fs);
}
