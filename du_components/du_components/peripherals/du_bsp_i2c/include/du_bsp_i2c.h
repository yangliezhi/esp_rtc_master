#ifndef __DU_BSP_I2C__
#define __DU_BSP_I2C__
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_check.h"

#define I2C_NUM (0)
#define DU_I2C_SCL       (GPIO_NUM_18)
#define DU_I2C_SDA       (GPIO_NUM_17)
#define TOUCH_GPIO_INT      (-1)

esp_err_t du_i2c_init();


#endif