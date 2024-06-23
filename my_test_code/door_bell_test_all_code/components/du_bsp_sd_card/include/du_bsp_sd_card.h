#ifndef __DU_BSP_SD_CARD__
#define __DU_BSP_SD_CARD__
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

#define MOUNT_POINT "/sdcard"

#define EXAMPLE_MAX_CHAR_SIZE 64
#define ESP_SD_PIN_CLK GPIO_NUM_15
#define ESP_SD_PIN_CMD GPIO_NUM_7
#define ESP_SD_PIN_D0 GPIO_NUM_4
#define ESP_SD_PIN_D1 -1
#define ESP_SD_PIN_D2 -1
#define ESP_SD_PIN_D3 -1
#define ESP_SD_PIN_D4 -1
#define ESP_SD_PIN_D5 -1
#define ESP_SD_PIN_D6 -1
#define ESP_SD_PIN_D7 -1
#define ESP_SD_PIN_CD -1
#define ESP_SD_PIN_WP -1

esp_err_t s_example_write_file(const char *path, char *data);
esp_err_t s_example_read_file(const char *path);
sdmmc_card_t *mount_sdcard(void);

#endif