/*
 * @Author: 都建民
 * @Date: 2024-03-20 00:16:02
 * @Last Modified by: dujianmin qq群 26875961
 * @Last Modified time: 2024-03-20 00:26:13
 */

#ifndef _APP_I2C_H_
#define _APP_I2C_H_
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#ifdef __cplusplus
extern "C"
{
#endif

    esp_err_t my_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif
