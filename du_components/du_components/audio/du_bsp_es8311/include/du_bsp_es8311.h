#ifndef __DU_BSP_ES8311__
#define __DU_BSP_ES8311__
#include "esp_log.h"
#include "esp_check.h"

#define EXAMPLE_RECV_BUF_SIZE (2400)
#define EXAMPLE_SAMPLE_RATE (22050)
#define EXAMPLE_MCLK_MULTIPLE (256) // If not using 24-bit data width, 256 should be enough
#define EXAMPLE_MCLK_FREQ_HZ (EXAMPLE_SAMPLE_RATE * EXAMPLE_MCLK_MULTIPLE)
#define EXAMPLE_VOICE_VOLUME 70
esp_err_t es8311_codec_init(void);


#endif
