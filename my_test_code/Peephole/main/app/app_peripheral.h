/*
 * @Author: 都建民 
 * @Date: 2024-03-20 16:47:19 
 * @Last Modified by: dujianmin qq群 26875961
 * @Last Modified time: 2024-03-20 17:04:30
 */
#ifndef _APP_PERIPHERAL_H_
#define _APP_PERIPHERAL_H_
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_io_expander_tca9554.h"
#ifdef __cplusplus
extern "C" {
#endif
void tca9554_init(void);
esp_err_t bsp_spiffs_mount(void);

#ifdef __cplusplus
}
#endif

#endif
