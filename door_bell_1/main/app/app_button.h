#ifndef __APP_BUTTON__
#define __APP_BUTTON__

typedef enum
{

    BSP_BUTTON_VOLUP = 0,
    BSP_BUTTON_VOLDOWN,
    BSP_BUTTON_SET,
    BSP_BUTTON_PLAY,
    BSP_BUTTON_MUTE,
    BSP_BUTTON_REC,
    BSP_BUTTON_MAIN,
    BSP_BUTTON_NUM,
} bsp_button_t;

void esp32_s3_adc_button(void);
#endif