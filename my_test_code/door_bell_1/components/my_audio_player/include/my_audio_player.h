#ifndef __MY_AUDIO_PLAYER__
#define __MY_AUDIO_PLAYER__

#include "driver/gpio.h"

/* I2C */
#define BSP_I2C_SCL (GPIO_NUM_18)
#define BSP_I2C_SDA (GPIO_NUM_17)

/* Audio */
#define BSP_I2S_SCLK (GPIO_NUM_9)
#define BSP_I2S_MCLK (GPIO_NUM_16)
#define BSP_I2S_LCLK (GPIO_NUM_45)
#define BSP_I2S_DOUT (GPIO_NUM_8)  // To Codec ES7210
#define BSP_I2S_DSIN (GPIO_NUM_10) // From ADC ES8311
#define BSP_POWER_AMP_IO (GPIO_NUM_48)

/* uSD card */
#define BSP_SD_D0 (GPIO_NUM_4)
#define BSP_SD_CMD (GPIO_NUM_7)
#define BSP_SD_CLK (GPIO_NUM_15)
#define BSP_I2C_NUM I2C_NUM_0
#define BSP_SPIFFS_MOUNT_POINT "/spiffs"

esp_err_t bsp_codec_volume_set(int volume, int *volume_set);
void my_audio_play_test(void);
void my_lcd_led(bool led_on_off);
#endif