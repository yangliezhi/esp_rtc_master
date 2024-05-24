/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "file_manager.h"

static const char *TAG = "file manager";

#define FLN_MAX CONFIG_FATFS_MAX_LFN

#ifndef CONFIG_EXAMPLE_USE_SDMMC_HOST
#define USE_SPI_MODE
#else
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32S3
#include "driver/sdmmc_host.h"
static sdmmc_card_t *mount_card = NULL;
#endif // define USE_SPI_MODE /* To enable SPI mode, uncomment this line*/
#endif // end define CONFIG_EXAMPLE_USE_SDMMC_HOST

esp_err_t fm_sdcard_init(void)
{
    ESP_LOGI(TAG, "Initializing SD card");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;
    slot_config.width = 1;
    slot_config.clk = 15;
    slot_config.cmd = 7;
    slot_config.d0 = 4;
    slot_config.d1 = -1;
    slot_config.d2 = -1;
    slot_config.d3 = -1;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {

        .format_if_mount_failed = true,

        .max_files = 10,
        .allocation_unit_size = 32 * 1024,
    };

    sdmmc_card_t *card;
    esp_err_t ret = esp_vfs_fat_sdmmc_mount(SD_CARD_MOUNT_POINT, &host, &slot_config, &mount_config, &card);
    mount_card = card;

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                          "If you want the card to be formatted, set format_if_mount_failed = true.");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                          "Make sure SD card lines have pull-up resistors in place.",
                     esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, card);
    return ESP_OK;
}

esp_err_t fm_unmount_sdcard(void)
{
#ifdef USE_SPI_MODE
    esp_err_t err = esp_vfs_fat_sdcard_unmount(SD_CARD_MOUNT_POINT, mount_card);
#else
    esp_err_t err = esp_vfs_fat_sdmmc_unmount();
#endif
    ESP_ERROR_CHECK(err);
#ifdef USE_SPI_MODE
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    err = spi_bus_free(host.slot);
#endif
    ESP_ERROR_CHECK(err);

    return err;
}

esp_err_t fm_spiffs_init(void)
{
    esp_err_t ret;
    ESP_LOGI(TAG, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = SPIFFS_MOUNT_POINT,
        .partition_label = NULL,
        .max_files = 5, // This decides the maximum number of files that can be created on the storage
        .format_if_mount_failed = true};

    ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        }
        else
        {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);

    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);

    return ESP_OK;
}

static void TraverseDir(char *direntName, int level, int indent)
{
    DIR *p_dir = NULL;
    struct dirent *p_dirent = NULL;

    p_dir = opendir(direntName);

    if (p_dir == NULL)
    {
        printf("opendir error\n");
        return;
    }

    while ((p_dirent = readdir(p_dir)) != NULL)
    {
        char *backupDirName = NULL;

        if (p_dirent->d_name[0] == '.')
        {
            continue;
        }

        int i;

        for (i = 0; i < indent; i++)
        {
            // printf("|");
            printf("     ");
        }

        printf("|--- %s", p_dirent->d_name);

        /* Itme is a file */
        if (p_dirent->d_type == DT_REG)
        {
            int curDirentNameLen = strlen(direntName) + strlen(p_dirent->d_name) + 2;

            // prepare next path
            backupDirName = (char *)malloc(curDirentNameLen);
            struct stat *st = NULL;
            st = malloc(sizeof(struct stat));

            if (NULL == backupDirName || NULL == st)
            {
                goto _err;
            }

            memset(backupDirName, 0, curDirentNameLen);
            memcpy(backupDirName, direntName, strlen(direntName));

            strcat(backupDirName, "/");
            strcat(backupDirName, p_dirent->d_name);

            int statok = stat(backupDirName, st);

            if (0 == statok)
            {
                printf("[%dB]\n", (int)st->st_size);
            }
            else
            {
                printf("\n");
            }

            free(backupDirName);
            backupDirName = NULL;
        }
        else
        {
            printf("\n");
        }

        /* Itme is a directory */
        if (p_dirent->d_type == DT_DIR)
        {
            int curDirentNameLen = strlen(direntName) + strlen(p_dirent->d_name) + 2;

            // prepare next path
            backupDirName = (char *)malloc(curDirentNameLen);

            if (NULL == backupDirName)
            {
                goto _err;
            }

            memset(backupDirName, 0, curDirentNameLen);
            memcpy(backupDirName, direntName, curDirentNameLen);

            strcat(backupDirName, "/");
            strcat(backupDirName, p_dirent->d_name);

            if (level > 0)
            {
                TraverseDir(backupDirName, level - 1, indent + 1);
            }

            free(backupDirName);
            backupDirName = NULL;
        }
    }

_err:
    closedir(p_dir);
}

void fm_print_dir(char *direntName, int level)
{
    printf("Traverse directory %s\n", direntName);
    TraverseDir(direntName, level, 0);
    printf("\r\n");
}

const char *fm_get_basepath(void)
{
    return SPIFFS_MOUNT_POINT;
}

esp_err_t fm_file_table_create(char ***list_out, uint16_t *files_number, const char *filter_suffix)
{
    DIR *p_dir = NULL;
    struct dirent *p_dirent = NULL;

    p_dir = opendir(SPIFFS_MOUNT_POINT);

    if (p_dir == NULL)
    {
        ESP_LOGE(TAG, "opendir error");
        return ESP_FAIL;
    }

    uint16_t f_num = 0;
    while ((p_dirent = readdir(p_dir)) != NULL)
    {
        if (p_dirent->d_type == DT_REG)
        {
            f_num++;
        }
    }

    rewinddir(p_dir);

    *list_out = calloc(f_num, sizeof(char *));
    if (NULL == (*list_out))
    {
        goto _err;
    }
    for (size_t i = 0; i < f_num; i++)
    {
        (*list_out)[i] = malloc(FLN_MAX);
        if (NULL == (*list_out)[i])
        {
            ESP_LOGE(TAG, "malloc failed at %d", i);
            fm_file_table_free(list_out, f_num);
            goto _err;
        }
    }

    uint16_t index = 0;
    while ((p_dirent = readdir(p_dir)) != NULL)
    {
        if (p_dirent->d_type == DT_REG)
        {
            if (NULL != filter_suffix)
            {
                if (strstr(p_dirent->d_name, filter_suffix))
                {
                    strncpy((*list_out)[index], p_dirent->d_name, FLN_MAX - 1);
                    (*list_out)[index][FLN_MAX - 1] = '\0';
                    index++;
                }
            }
            else
            {
                strncpy((*list_out)[index], p_dirent->d_name, FLN_MAX - 1);
                (*list_out)[index][FLN_MAX - 1] = '\0';
                index++;
            }
        }
    }
    (*files_number) = index;

    closedir(p_dir);
    return ESP_OK;
_err:
    closedir(p_dir);

    return ESP_FAIL;
}

esp_err_t fm_file_table_free(char ***list, uint16_t files_number)
{
    for (size_t i = 0; i < files_number; i++)
    {
        free((*list)[i]);
    }
    free((*list));
    return ESP_OK;
}

const char *fm_get_filename(const char *file)
{
    const char *p = file + strlen(file);
    while (p > file)
    {
        if ('/' == *p)
        {
            return (p + 1);
        }
        p--;
    }
    return file;
}

size_t fm_get_file_size(const char *filepath)
{
    struct stat siz = {0};
    stat(filepath, &siz);
    return siz.st_size;
}
