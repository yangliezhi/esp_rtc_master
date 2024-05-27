#ifndef __DU_BSP_ES7010__
#define __DU_BSP_ES7010__
#include "esp_log.h"
#include "esp_check.h"
#include "driver/i2s_tdm.h"
#include "es7210.h"



/* I2S configurations */
#define EXAMPLE_I2S_TDM_FORMAT (ES7210_I2S_FMT_I2S)
#define EXAMPLE_I2S_CHAN_NUM (4)
#define EXAMPLE_I2S_SAMPLE_RATE (48000)
#define EXAMPLE_I2S_MCLK_MULTIPLE (I2S_MCLK_MULTIPLE_256)
#define EXAMPLE_I2S_SAMPLE_BITS (I2S_DATA_BIT_WIDTH_16BIT)
#define EXAMPLE_I2S_TDM_SLOT_MASK (I2S_TDM_SLOT0 | I2S_TDM_SLOT1 | I2S_TDM_SLOT2 | I2S_TDM_SLOT3)

/* ES7210 configurations */
#define EXAMPLE_ES7210_I2C_ADDR (0x40)
#define EXAMPLE_ES7210_I2C_CLK (100000)
#define EXAMPLE_ES7210_MIC_GAIN (ES7210_MIC_GAIN_30DB)
#define EXAMPLE_ES7210_MIC_BIAS (ES7210_MIC_BIAS_2V87)
#define EXAMPLE_ES7210_ADC_VOLUME (0)

void es7210_codec_init(void);
esp_err_t record_wav(i2s_chan_handle_t i2s_rx_chan);
#endif