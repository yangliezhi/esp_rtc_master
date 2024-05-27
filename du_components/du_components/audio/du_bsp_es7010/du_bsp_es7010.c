#include <stdio.h>
#include "du_bsp_es7010.h"
#include "du_bsp_i2c.h"

#include "es7210.h"
#include "driver/i2s_tdm.h"
#include "esp_check.h"

static const char *TAG = "du_bsp_es7010";

void es7210_codec_init(void)
{

    du_i2c_init();
    /* Create ES7210 device handle */
    es7210_dev_handle_t es7210_handle = NULL;
    es7210_i2c_config_t es7210_i2c_conf = {
        .i2c_port = I2C_NUM,
        .i2c_addr = EXAMPLE_ES7210_I2C_ADDR};
    ESP_ERROR_CHECK(es7210_new_codec(&es7210_i2c_conf, &es7210_handle));

    ESP_LOGI(TAG, "Configure ES7210 codec parameters");
    es7210_codec_config_t codec_conf = {
        .i2s_format = EXAMPLE_I2S_TDM_FORMAT,
        .mclk_ratio = EXAMPLE_I2S_MCLK_MULTIPLE,
        .sample_rate_hz = EXAMPLE_I2S_SAMPLE_RATE,
        .bit_width = (es7210_i2s_bits_t)EXAMPLE_I2S_SAMPLE_BITS,
        .mic_bias = EXAMPLE_ES7210_MIC_BIAS,
        .mic_gain = EXAMPLE_ES7210_MIC_GAIN,
        .flags.tdm_enable = true};
    ESP_ERROR_CHECK(es7210_config_codec(es7210_handle, &codec_conf));
    ESP_ERROR_CHECK(es7210_config_volume(es7210_handle, EXAMPLE_ES7210_ADC_VOLUME));
}
#include "format_wav.h"
/* SD card & recording configurations */
#define EXAMPLE_RECORD_TIME_SEC    (10)
#define EXAMPLE_SD_MOUNT_POINT     "/sdcard"
#define EXAMPLE_RECORD_FILE_PATH   "/RECORD.WAV"
esp_err_t record_wav(i2s_chan_handle_t i2s_rx_chan)
{
    ESP_RETURN_ON_FALSE(i2s_rx_chan, ESP_FAIL, TAG, "invalid i2s channel handle pointer");
    esp_err_t ret = ESP_OK;

    uint32_t byte_rate = EXAMPLE_I2S_SAMPLE_RATE * EXAMPLE_I2S_CHAN_NUM * EXAMPLE_I2S_SAMPLE_BITS / 8;
    uint32_t wav_size = byte_rate * EXAMPLE_RECORD_TIME_SEC;

    const wav_header_t wav_header =
        WAV_HEADER_PCM_DEFAULT(wav_size, EXAMPLE_I2S_SAMPLE_BITS, EXAMPLE_I2S_SAMPLE_RATE, EXAMPLE_I2S_CHAN_NUM);

    ESP_LOGI(TAG, "Opening file %s", EXAMPLE_RECORD_FILE_PATH);
    FILE *f = fopen(EXAMPLE_SD_MOUNT_POINT EXAMPLE_RECORD_FILE_PATH, "w");
    ESP_RETURN_ON_FALSE(f, ESP_FAIL, TAG, "error while opening wav file");

    /* Write wav header */
    ESP_GOTO_ON_FALSE(fwrite(&wav_header, sizeof(wav_header_t), 1, f), ESP_FAIL, err,
                      TAG, "error while writing wav header");

    /* Start recording */
    size_t wav_written = 0;
    static int16_t i2s_readraw_buff[4096];
    ESP_GOTO_ON_ERROR(i2s_channel_enable(i2s_rx_chan), err, TAG, "error while starting i2s rx channel");
    while (wav_written < wav_size) {
        if (wav_written % byte_rate < sizeof(i2s_readraw_buff)) {
            ESP_LOGI(TAG, "Recording: %"PRIu32"/%ds", wav_written / byte_rate + 1, EXAMPLE_RECORD_TIME_SEC);
        }
        size_t bytes_read = 0;
        /* Read RAW samples from ES7210 */
        ESP_GOTO_ON_ERROR(i2s_channel_read(i2s_rx_chan, i2s_readraw_buff, sizeof(i2s_readraw_buff), &bytes_read,
                                           pdMS_TO_TICKS(1000)), err, TAG, "error while reading samples from i2s");
        /* Write the samples to the WAV file */
        ESP_GOTO_ON_FALSE(fwrite(i2s_readraw_buff, bytes_read, 1, f), ESP_FAIL, err,
                          TAG, "error while writing samples to wav file");
        wav_written += bytes_read;
    }

err:
    i2s_channel_disable(i2s_rx_chan);
    ESP_LOGI(TAG, "Recording done! Flushing file buffer");
    fclose(f);

    return ret;
}