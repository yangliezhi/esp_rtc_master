#include "my_audio_player.h"
#include "audio_player.h"
#include "ui_audio.h"
#include "file_iterator.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_spiffs.h"

#include "esp_codec_dev_defaults.h"
#include "esp_codec_dev.h"
#include "bsp_err_check.h"
#include "driver/i2s_std.h"

#include "esp_io_expander_tca9554.h"
#include "driver/i2c.h"
#include "esp_spiffs.h"

static const char *TAG = "my_audio_test";
#define CODEC_DEFAULT_SAMPLE_RATE (16000)
#define CODEC_DEFAULT_BIT_WIDTH (16)
#define CODEC_DEFAULT_ADC_VOLUME (24.0)
#define CODEC_DEFAULT_CHANNEL (2)
#define CONFIG_BSP_I2S_NUM 1

// extern esp_periph_set_handle_t set;
static esp_codec_dev_handle_t play_dev_handle;
static esp_codec_dev_handle_t record_dev_handle;

static bool i2c_initialized = false;
// static i2c_bus_handle_t i2c_handle;

static i2s_chan_handle_t i2s_tx_chan = NULL;
static i2s_chan_handle_t i2s_rx_chan = NULL;
static const audio_codec_data_if_t *i2s_data_if = NULL; /* Codec data interface */

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

/* This configuration is used by default in bsp_audio_init() */
#define BSP_I2S_DUPLEX_MONO_CFG(_sample_rate)                                                         \
    {                                                                                                 \
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(_sample_rate),                                          \
        .slot_cfg = I2S_STD_PHILIP_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO), \
        .gpio_cfg = BSP_I2S_GPIO_CFG,                                                                 \
    }
esp_err_t bsp_audio_init(const i2s_std_config_t *i2s_config)
{
    esp_err_t ret = ESP_FAIL;
    if (i2s_tx_chan && i2s_rx_chan)
    {
        /* Audio was initialized before */
        return ESP_OK;
    }

    /* Setup I2S peripheral */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(CONFIG_BSP_I2S_NUM, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true; // Auto clear the legacy data in the DMA buffer
    BSP_ERROR_CHECK_RETURN_ERR(i2s_new_channel(&chan_cfg, &i2s_tx_chan, &i2s_rx_chan));

    /* Setup I2S channels */
    const i2s_std_config_t std_cfg_default = BSP_I2S_DUPLEX_MONO_CFG(22050);
    const i2s_std_config_t *p_i2s_cfg = &std_cfg_default;
    if (i2s_config != NULL)
    {
        p_i2s_cfg = i2s_config;
    }

    if (i2s_tx_chan != NULL)
    {
        ESP_GOTO_ON_ERROR(i2s_channel_init_std_mode(i2s_tx_chan, p_i2s_cfg), err, TAG, "I2S channel initialization failed");
        ESP_GOTO_ON_ERROR(i2s_channel_enable(i2s_tx_chan), err, TAG, "I2S enabling failed");
    }
    if (i2s_rx_chan != NULL)
    {
        ESP_GOTO_ON_ERROR(i2s_channel_init_std_mode(i2s_rx_chan, p_i2s_cfg), err, TAG, "I2S channel initialization failed");
        ESP_GOTO_ON_ERROR(i2s_channel_enable(i2s_rx_chan), err, TAG, "I2S enabling failed");
    }

    audio_codec_i2s_cfg_t i2s_cfg = {
        .port = CONFIG_BSP_I2S_NUM,
        .rx_handle = i2s_rx_chan,
        .tx_handle = i2s_tx_chan,
    };
    i2s_data_if = audio_codec_new_i2s_data(&i2s_cfg);
    BSP_NULL_CHECK_GOTO(i2s_data_if, err);

    return ESP_OK;

err:
    if (i2s_tx_chan)
    {
        i2s_del_channel(i2s_tx_chan);
    }
    if (i2s_rx_chan)
    {
        i2s_del_channel(i2s_rx_chan);
    }

    return ret;
}

const audio_codec_data_if_t *bsp_audio_get_codec_itf(void)
{
    return i2s_data_if;
}

esp_codec_dev_handle_t bsp_audio_codec_speaker_init(void)
{
    const audio_codec_data_if_t *i2s_data_if = bsp_audio_get_codec_itf();
    if (i2s_data_if == NULL)
    {
        /* Initilize I2C */
        // BSP_ERROR_CHECK_RETURN_NULL(bsp_i2c_init_1());
        /* Configure I2S peripheral and Power Amplifier */
        BSP_ERROR_CHECK_RETURN_NULL(bsp_audio_init(NULL));
        i2s_data_if = bsp_audio_get_codec_itf();
    }
    assert(i2s_data_if);

    const audio_codec_gpio_if_t *gpio_if = audio_codec_new_gpio();

    audio_codec_i2c_cfg_t i2c_cfg = {
        .port = 0,
        .addr = ES8311_CODEC_DEFAULT_ADDR,
    };
    const audio_codec_ctrl_if_t *i2c_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
    BSP_NULL_CHECK(i2c_ctrl_if, NULL);

    esp_codec_dev_hw_gain_t gain = {
        .pa_voltage = 5.0,
        .codec_dac_voltage = 3.3,
    };

    es8311_codec_cfg_t es8311_cfg = {
        .ctrl_if = i2c_ctrl_if,
        .gpio_if = gpio_if,
        .codec_mode = ESP_CODEC_DEV_WORK_MODE_DAC,
        .pa_pin = BSP_POWER_AMP_IO,
        .pa_reverted = false,
        .master_mode = false,
        .use_mclk = true,
        .digital_mic = false,
        .invert_mclk = false,
        .invert_sclk = false,
        .hw_gain = gain,
    };
    const audio_codec_if_t *es8311_dev = es8311_codec_new(&es8311_cfg);
    BSP_NULL_CHECK(es8311_dev, NULL);

    esp_codec_dev_cfg_t codec_dev_cfg = {
        .dev_type = ESP_CODEC_DEV_TYPE_OUT,
        .codec_if = es8311_dev,
        .data_if = i2s_data_if,
    };
    return esp_codec_dev_new(&codec_dev_cfg);
}

esp_codec_dev_handle_t bsp_audio_codec_microphone_init(void)
{
    const audio_codec_data_if_t *i2s_data_if = bsp_audio_get_codec_itf();
    if (i2s_data_if == NULL)
    {
        /* Initilize I2C */
        // BSP_ERROR_CHECK_RETURN_NULL(bsp_i2c_init_1());
        /* Configure I2S peripheral and Power Amplifier */
        BSP_ERROR_CHECK_RETURN_NULL(bsp_audio_init(NULL));
        i2s_data_if = bsp_audio_get_codec_itf();
    }
    assert(i2s_data_if);

    audio_codec_i2c_cfg_t i2c_cfg = {
        .port = BSP_I2C_NUM,
        .addr = ES7210_CODEC_DEFAULT_ADDR,
    };
    const audio_codec_ctrl_if_t *i2c_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
    BSP_NULL_CHECK(i2c_ctrl_if, NULL);

    es7210_codec_cfg_t es7210_cfg = {
        .ctrl_if = i2c_ctrl_if,
    };
    const audio_codec_if_t *es7210_dev = es7210_codec_new(&es7210_cfg);
    BSP_NULL_CHECK(es7210_dev, NULL);

    esp_codec_dev_cfg_t codec_es7210_dev_cfg = {
        .dev_type = ESP_CODEC_DEV_TYPE_IN,
        .codec_if = es7210_dev,
        .data_if = i2s_data_if,
    };
    return esp_codec_dev_new(&codec_es7210_dev_cfg);
}

esp_err_t bsp_codec_volume_set(int volume, int *volume_set)
{
    esp_err_t ret = ESP_OK;
    float v = volume;
    ret = esp_codec_dev_set_out_vol(play_dev_handle, (int)v);
    return ret;
}

esp_err_t bsp_codec_mute_set(bool enable)
{
    esp_err_t ret = ESP_OK;
    ret = esp_codec_dev_set_out_mute(play_dev_handle, enable);
    return ret;
}

static esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting)
{

    uint8_t volume = get_sys_volume();

    bsp_codec_mute_set(setting == AUDIO_PLAYER_MUTE ? true : false);

    // restore the voice volume upon unmuting
    if (setting == AUDIO_PLAYER_UNMUTE)
    {
        bsp_codec_volume_set(volume, NULL);
    }

    return ESP_OK;
}
esp_err_t bsp_codec_set_fs(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch)
{
    esp_err_t ret = ESP_OK;

    esp_codec_dev_sample_info_t fs = {
        .sample_rate = rate,
        .channel = ch,
        .bits_per_sample = bits_cfg,
    };

    if (play_dev_handle)
    {
        // ret = esp_codec_dev_close(play_dev_handle);
        ret |= esp_codec_dev_open(play_dev_handle, &fs);
    }
    // if (record_dev_handle)
    // {
    //     ret |= esp_codec_dev_close(record_dev_handle);
    //     ret |= esp_codec_dev_set_in_gain(record_dev_handle, CODEC_DEFAULT_ADC_VOLUME);
    // }

    // if (record_dev_handle)
    // {
    //     ret |= esp_codec_dev_open(play_dev_handle, &fs);
    // }
    // if (record_dev_handle)
    // {
    //     ret |= esp_codec_dev_open(record_dev_handle, &fs);
    // }
    return ret;
}
static esp_err_t bsp_codec_init()
{
    play_dev_handle = bsp_audio_codec_speaker_init();
    assert((play_dev_handle) && "play_dev_handle not initialized");

    // record_dev_handle = bsp_audio_codec_microphone_init();
    // assert((record_dev_handle) && "record_dev_handle not initialized");

    // bsp_codec_set_fs(CODEC_DEFAULT_SAMPLE_RATE, CODEC_DEFAULT_BIT_WIDTH, CODEC_DEFAULT_CHANNEL);
    return ESP_OK;
}

static esp_err_t bsp_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms)
{
    esp_err_t ret = ESP_OK;
    ret = esp_codec_dev_write(play_dev_handle, audio_buffer, len);
    *bytes_written = len;
    return ret;
}

esp_err_t bsp_spiffs_mount(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",
        .max_files = 5,
        .format_if_mount_failed = true,

    };

    esp_err_t ret_val = esp_vfs_spiffs_register(&conf);

    size_t total = 0, used = 0;
    ret_val = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret_val != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret_val));
    }
    else
    {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    return ret_val;
}

esp_io_expander_handle_t io_expander = NULL;
bool is_tca9554_init = false;
static void tca9554_init(void)
{
    if (is_tca9554_init)
    {
        return;
    }

    if (ESP_OK == (esp_io_expander_new_i2c_tca9554(0, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000, &io_expander)))
    {
        ESP_LOGI("MY_TAG", "设备探测成功，无需额外操作");
    }
    else if (ESP_OK == (esp_io_expander_new_i2c_tca9554(0, ESP_IO_EXPANDER_I2C_TCA9554A_ADDRESS_000, &io_expander)))
    {
        ESP_LOGI("MY_TAG", "尝试另一种地址成功，继续其他操作");
        // 继续后续操作
    }
    else
    {
        ESP_LOGE("MY_TAG", "设备探测失败");
        return; // 最终返回
    }

    esp_io_expander_set_dir(io_expander, IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1 | IO_EXPANDER_PIN_NUM_7, IO_EXPANDER_OUTPUT);

    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_0, 0);
    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_1, 1);
    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_7, 1);
    is_tca9554_init = true;
}
void my_audio_play_test(void)
{
    tca9554_init();
    bsp_spiffs_mount();
    file_iterator_instance_t *file_iterator = file_iterator_new(BSP_SPIFFS_MOUNT_POINT);
    assert(file_iterator != NULL);
    bsp_codec_init();
    audio_player_config_t config = {.mute_fn = audio_mute_function,
                                    .write_fn = bsp_i2s_write,
                                    .clk_set_fn = bsp_codec_set_fs,
                                    .priority = 1};
    ESP_ERROR_CHECK(audio_player_new(config));
    my_audio_init(file_iterator);
    // ui_audio_start(file_iterator);
}
void my_lcd_led(bool led_on_off)
{
    esp_io_expander_set_level(io_expander, IO_EXPANDER_PIN_NUM_1, led_on_off);
}