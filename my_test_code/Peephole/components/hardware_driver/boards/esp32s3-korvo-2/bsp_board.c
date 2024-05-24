/*
 * @Author: 都建民 
 * @Date: 2024-03-20 17:45:29 
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-05-17 15:29:13
 */

#include "string.h"
#include "bsp_board.h"
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
#include "driver/i2s_std.h"
#include "driver/i2s_tdm.h"
#include "soc/soc_caps.h"
#else
#include "driver/i2s.h"
#endif
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "esp_rom_sys.h"
#include "esp_check.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#if ((SOC_SDMMC_HOST_SUPPORTED) && (FUNC_SDMMC_EN))
#include "driver/sdmmc_host.h"
#endif /* ((SOC_SDMMC_HOST_SUPPORTED) && (FUNC_SDMMC_EN)) */

#include "file_iterator.h"
#include "audio_player.h"

#define GPIO_MUTE_NUM GPIO_NUM_1
#define GPIO_MUTE_LEVEL 1
#define ACK_CHECK_EN 0x1 /*!< I2C master will check ack from slave*/
#define ADC_I2S_CHANNEL 4
static sdmmc_card_t *card;
static const char *TAG = "board";
static int s_play_sample_rate = 16000;
static int s_play_channel_format = 1;
static int s_bits_per_chan = 16;

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
static i2s_chan_handle_t tx_handle = NULL; // I2S tx channel handler
static i2s_chan_handle_t rx_handle = NULL; // I2S rx channel handler
#endif
static audio_codec_data_if_t *record_data_if = NULL;
static audio_codec_ctrl_if_t *record_ctrl_if = NULL;
static audio_codec_if_t *record_codec_if = NULL;
static esp_codec_dev_handle_t record_dev = NULL;

static audio_codec_data_if_t *play_data_if = NULL;
static audio_codec_ctrl_if_t *play_ctrl_if = NULL;
static audio_codec_gpio_if_t *play_gpio_if = NULL;
static audio_codec_if_t *play_codec_if = NULL;
static esp_codec_dev_handle_t play_dev = NULL;

esp_err_t bsp_codec_adc_init(int sample_rate)
{
    esp_err_t ret_val = ESP_OK;

    // Do initialize of related interface: data_if, ctrl_if and gpio_if
    audio_codec_i2s_cfg_t i2s_cfg = {
        .port = I2S_NUM_1,
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
        .rx_handle = rx_handle,
        .tx_handle = NULL,
#endif
    };
    record_data_if = audio_codec_new_i2s_data(&i2s_cfg);

    audio_codec_i2c_cfg_t i2c_cfg = {.addr = ES7210_CODEC_DEFAULT_ADDR};
    record_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
    // New input codec interface
    es7210_codec_cfg_t es7210_cfg = {
        .ctrl_if = record_ctrl_if,
        .mic_selected = ES7120_SEL_MIC1 | ES7120_SEL_MIC2 | ES7120_SEL_MIC3 | ES7120_SEL_MIC4,
    };
    record_codec_if = es7210_codec_new(&es7210_cfg);
    // New input codec device
    esp_codec_dev_cfg_t dev_cfg = {
        .codec_if = record_codec_if,
        .data_if = record_data_if,
        .dev_type = ESP_CODEC_DEV_TYPE_IN,
    };
    record_dev = esp_codec_dev_new(&dev_cfg);

    esp_codec_dev_sample_info_t fs = {
        .sample_rate = 16000,
        .channel = 2,
        .bits_per_sample = 32,
    };
    esp_codec_dev_open(record_dev, &fs);
    // esp_codec_dev_set_in_gain(record_dev, RECORD_VOLUME);
    esp_codec_dev_set_in_channel_gain(record_dev, ESP_CODEC_DEV_MAKE_CHANNEL_MASK(0), RECORD_VOLUME);
    esp_codec_dev_set_in_channel_gain(record_dev, ESP_CODEC_DEV_MAKE_CHANNEL_MASK(1), RECORD_VOLUME);
    esp_codec_dev_set_in_channel_gain(record_dev, ESP_CODEC_DEV_MAKE_CHANNEL_MASK(2), RECORD_VOLUME);
    esp_codec_dev_set_in_channel_gain(record_dev, ESP_CODEC_DEV_MAKE_CHANNEL_MASK(3), RECORD_VOLUME);

    return ret_val;
}
// #include "my_audio_player.h"

esp_err_t bsp_codec_dac_init(int sample_rate, int channel_format, int bits_per_chan)
{
    esp_err_t ret_val = ESP_OK;

    // Do initialize of related interface: data_if, ctrl_if and gpio_if
    audio_codec_i2s_cfg_t i2s_cfg = {
        .port = I2S_NUM_1,
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
        .rx_handle = NULL,
        .tx_handle = tx_handle,
#endif
    };
    play_data_if = audio_codec_new_i2s_data(&i2s_cfg);

    audio_codec_i2c_cfg_t i2c_cfg = {.addr = ES8311_CODEC_DEFAULT_ADDR};
    play_ctrl_if = audio_codec_new_i2c_ctrl(&i2c_cfg);
    play_gpio_if = audio_codec_new_gpio();
    // New output codec interface
    es8311_codec_cfg_t es8311_cfg = {
        .codec_mode = ESP_CODEC_DEV_WORK_MODE_DAC,
        .ctrl_if = play_ctrl_if,
        .gpio_if = play_gpio_if,
        .pa_pin = GPIO_PWR_CTRL,
        .use_mclk = false,
    };
    play_codec_if = es8311_codec_new(&es8311_cfg);
    // New output codec device
    esp_codec_dev_cfg_t dev_cfg = {
        .codec_if = play_codec_if,
        .data_if = play_data_if,
        .dev_type = ESP_CODEC_DEV_TYPE_OUT,
    };
    play_dev = esp_codec_dev_new(&dev_cfg);

    esp_codec_dev_sample_info_t fs = {
        .bits_per_sample = bits_per_chan,
        .sample_rate = sample_rate,
        .channel = channel_format,
    };
    esp_codec_dev_set_out_vol(play_dev, PLAYER_VOLUME);
    esp_codec_dev_open(play_dev, &fs);

    // bsp_codec_set_play_dev_handle(play_dev);
    return ret_val;
}

static esp_err_t bsp_codec_adc_deinit()
{
    esp_err_t ret_val = ESP_OK;

    if (record_dev)
    {
        esp_codec_dev_close(record_dev);
        esp_codec_dev_delete(record_dev);
        record_dev = NULL;
    }

    // Delete codec interface
    if (record_codec_if)
    {
        audio_codec_delete_codec_if(record_codec_if);
        record_codec_if = NULL;
    }

    // Delete codec control interface
    if (record_ctrl_if)
    {
        audio_codec_delete_ctrl_if(record_ctrl_if);
        record_ctrl_if = NULL;
    }

    // Delete codec data interface
    if (record_data_if)
    {
        audio_codec_delete_data_if(record_data_if);
        record_data_if = NULL;
    }

    return ret_val;
}

static esp_err_t bsp_codec_dac_deinit()
{
    esp_err_t ret_val = ESP_OK;

    if (play_dev)
    {
        esp_codec_dev_close(play_dev);
        esp_codec_dev_delete(play_dev);
        play_dev = NULL;
    }

    // Delete codec interface
    if (play_codec_if)
    {
        audio_codec_delete_codec_if(play_codec_if);
        play_codec_if = NULL;
    }

    // Delete codec control interface
    if (play_ctrl_if)
    {
        audio_codec_delete_ctrl_if(play_ctrl_if);
        play_ctrl_if = NULL;
    }

    if (play_gpio_if)
    {
        audio_codec_delete_gpio_if(play_gpio_if);
        play_gpio_if = NULL;
    }

    // Delete codec data interface
    if (play_data_if)
    {
        audio_codec_delete_data_if(play_data_if);
        play_data_if = NULL;
    }

    return ret_val;
}

esp_err_t bsp_audio_set_play_vol(int volume)
{
    if (!play_dev)
    {
        ESP_LOGE(TAG, "DAC codec init fail");
        return ESP_FAIL;
    }
    esp_codec_dev_set_out_vol(play_dev, volume);
    return ESP_OK;
}

esp_err_t bsp_audio_get_play_vol(int *volume)
{
    if (!play_dev)
    {
        ESP_LOGE(TAG, "DAC codec init fail");
        return ESP_FAIL;
    }
    esp_codec_dev_get_out_vol(play_dev, volume);
    return ESP_OK;
}

// static esp_err_t bsp_i2s_init(i2s_port_t i2s_num, uint32_t sample_rate, i2s_channel_fmt_t channel_format, i2s_bits_per_chan_t bits_per_chan)
static esp_err_t bsp_i2s_init(i2s_port_t i2s_num, uint32_t sample_rate, int channel_format, int bits_per_chan)
{
    esp_err_t ret_val = ESP_OK;

    i2s_slot_mode_t channel_fmt = I2S_SLOT_MODE_STEREO;
    if (channel_format == 1)
    {
        channel_fmt = I2S_SLOT_MODE_MONO;
    }
    else if (channel_format == 2)
    {
        channel_fmt = I2S_SLOT_MODE_STEREO;
    }
    else
    {
        ESP_LOGE(TAG, "Unable to configure channel_format %d", channel_format);
        channel_format = 1;
        channel_fmt = I2S_SLOT_MODE_MONO;
    }

    if (bits_per_chan != 16 && bits_per_chan != 32)
    {
        ESP_LOGE(TAG, "Unable to configure bits_per_chan %d", bits_per_chan);
        bits_per_chan = 32;
    }

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(i2s_num, I2S_ROLE_MASTER);
    ret_val |= i2s_new_channel(&chan_cfg, &tx_handle, &rx_handle);
    i2s_std_config_t std_cfg = I2S_CONFIG_DEFAULT(sample_rate, channel_fmt, bits_per_chan);
    ret_val |= i2s_channel_init_std_mode(tx_handle, &std_cfg);
    ret_val |= i2s_channel_init_std_mode(rx_handle, &std_cfg);
    ret_val |= i2s_channel_enable(tx_handle);
    ret_val |= i2s_channel_enable(rx_handle);

    return ret_val;
}

static esp_err_t bsp_i2s_deinit(i2s_port_t i2s_num)
{
    esp_err_t ret_val = ESP_OK;

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    if (i2s_num == I2S_NUM_1 && rx_handle)
    {
        ret_val |= i2s_channel_disable(rx_handle);
        ret_val |= i2s_del_channel(rx_handle);
        rx_handle = NULL;
    }
    else if (i2s_num == I2S_NUM_0 && tx_handle)
    {
        ret_val |= i2s_channel_disable(tx_handle);
        ret_val |= i2s_del_channel(tx_handle);
        tx_handle = NULL;
    }
#else
    ret_val |= i2s_stop(i2s_num);
    ret_val |= i2s_driver_uninstall(i2s_num);
#endif

    return ret_val;
}

static esp_err_t bsp_codec_init(int adc_sample_rate, int dac_sample_rate, int dac_channel_format, int dac_bits_per_chan)
{
    esp_err_t ret_val = ESP_OK;

    ret_val |= bsp_codec_adc_init(adc_sample_rate);
    ret_val |= bsp_codec_dac_init(dac_sample_rate, dac_channel_format, dac_bits_per_chan);

    return ret_val;
}

static esp_err_t bsp_codec_deinit()
{
    esp_err_t ret_val = ESP_OK;

    ret_val |= bsp_codec_adc_deinit();
    ret_val |= bsp_codec_dac_deinit();
    return ret_val;
}

esp_err_t bsp_audio_play(const int16_t *data, int length, TickType_t ticks_to_wait)
{
    size_t bytes_write = 0;
    esp_err_t ret = ESP_OK;
    if (!play_dev)
    {
        return ESP_FAIL;
    }

    int out_length = length;
    int audio_time = 1;
    audio_time *= (16000 / s_play_sample_rate);
    audio_time *= (2 / s_play_channel_format);

    int *data_out = NULL;
    if (s_bits_per_chan != 32)
    {
        out_length = length * 2;
        data_out = malloc(out_length);
        for (int i = 0; i < length / sizeof(int16_t); i++)
        {
            int ret = data[i];
            data_out[i] = ret << 16;
        }
    }

    int *data_out_1 = NULL;
    if (s_play_channel_format != 2 || s_play_sample_rate != 16000)
    {
        out_length *= audio_time;
        data_out_1 = malloc(out_length);
        int *tmp_data = NULL;
        if (data_out != NULL)
        {
            tmp_data = data_out;
        }
        else
        {
            tmp_data = data;
        }

        for (int i = 0; i < out_length / (audio_time * sizeof(int)); i++)
        {
            for (int j = 0; j < audio_time; j++)
            {
                data_out_1[audio_time * i + j] = tmp_data[i];
            }
        }
        if (data_out != NULL)
        {
            free(data_out);
            data_out = NULL;
        }
    }

    if (data_out != NULL)
    {
        ret = esp_codec_dev_write(play_dev, (void *)data_out, out_length);
        free(data_out);
    }
    else if (data_out_1 != NULL)
    {
        ret = esp_codec_dev_write(play_dev, (void *)data_out_1, out_length);
        free(data_out_1);
    }
    else
    {
        ret = esp_codec_dev_write(play_dev, (void *)data, length);
    }

    return ret;
}

esp_err_t bsp_get_feed_data(bool is_get_raw_channel, int16_t *buffer, int buffer_len)
{
    esp_err_t ret = ESP_OK;
    size_t bytes_read;
    int audio_chunksize = buffer_len / (sizeof(int16_t) * ADC_I2S_CHANNEL);

    ret = esp_codec_dev_read(record_dev, (void *)buffer, buffer_len);
    if (!is_get_raw_channel)
    {
        for (int i = 0; i < audio_chunksize; i++)
        {
            int16_t ref = buffer[4 * i + 0];
            buffer[3 * i + 0] = buffer[4 * i + 1];
            buffer[3 * i + 1] = buffer[4 * i + 3];
            buffer[3 * i + 2] = ref;
        }
    }

    return ret;
}

int bsp_get_feed_channel(void)
{
    return ADC_I2S_CHANNEL;
}

esp_err_t bsp_board_init(uint32_t sample_rate, int channel_format, int bits_per_chan)
{
    /*!< Initialize I2C bus, used for audio codec*/
    // bsp_i2c_init(I2C_NUM, I2C_CLK);
    s_play_sample_rate = sample_rate;

    if (channel_format != 2 && channel_format != 1)
    {
        ESP_LOGE(TAG, "Unable to configure channel_format");
        channel_format = 2;
    }
    s_play_channel_format = channel_format;

    if (bits_per_chan != 32 && bits_per_chan != 16)
    {
        ESP_LOGE(TAG, "Unable to configure bits_per_chan");
        bits_per_chan = 32;
    }
    s_bits_per_chan = bits_per_chan;

    bsp_i2s_init(I2S_NUM_1, 16000, 2, 32);
    bsp_codec_init(16000, 16000, 2, 32);
    esp_sr_audio_play();
    return ESP_OK;
}

static esp_err_t app_codec_mute_set(bool enable)
{
    esp_err_t ret = ESP_OK;
    ret = esp_codec_dev_set_out_mute(play_dev, enable);
    return ret;
}
static esp_err_t app_codec_volume_set(int volume, int *volume_set)
{
    esp_err_t ret = ESP_OK;
    float v = volume;
    ret = esp_codec_dev_set_out_vol(play_dev, (int)v);
    return ret;
}

static esp_err_t audio_mute_function(AUDIO_PLAYER_MUTE_SETTING setting)
{

    app_codec_mute_set(false);

    return ESP_OK;
}
static esp_err_t app_i2s_write(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms)
{
    esp_err_t ret = ESP_OK;
    ret = esp_codec_dev_write(play_dev, audio_buffer, len);
    *bytes_written = len;
    return ret;
}
static esp_err_t app_codec_set_fs(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch)
{
    esp_err_t ret = ESP_OK;

    esp_codec_dev_sample_info_t fs = {
        .sample_rate = rate,
        .channel = ch,
        .bits_per_sample = bits_cfg,
    };

    if (play_dev)
    {
        ret |= esp_codec_dev_open(play_dev, &fs);
    }

    return ret;
}

void esp_sr_audio_play(void)
{
    audio_player_config_t config = {.mute_fn = audio_mute_function,
                                    .write_fn = app_i2s_write,
                                    .clk_set_fn = app_codec_set_fs,
                                    .priority = 1};
    ESP_ERROR_CHECK(audio_player_new(config));
    app_codec_volume_set(70, NULL);
}

void app_play_index(int index)
{
    ESP_LOGI(TAG, "play_index(%d)", index);
    bsp_codec_init(16000, 16000, 1, 16);

    file_iterator_instance_t *file_iterator = file_iterator_new("/spiffs");
    assert(file_iterator != NULL);
    char filename[128];
    int retval = file_iterator_get_full_path_from_index(file_iterator, index, filename, sizeof(filename));
    if (retval == 0)
    {
        // ESP_LOGE(TAG, "unable to retrieve filename");
        return;
    }
    // ESP_LOGI(TAG, "RECEIVE FILENAME: %s", filename);
    FILE *fp = fopen(filename, "rb");
    if (fp)
    {
        // ESP_LOGI(TAG, "Playing '%s'", filename);
        audio_player_play(fp);
    }
    else
    {
        // ESP_LOGE(TAG, "unable to open index %d, filename '%s'", index, filename);
    }
}

void app_stop_index(void)
{
    audio_player_stop();
    // audio_player_pause();
    bsp_codec_init(16000, 16000, 2, 32);
}
