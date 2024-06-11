/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_check.h"
#include "bsp/esp-bsp.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "settings.h"

static const char *TAG = "settings";

#define NAME_SPACE "sys_param"
#define KEY "param"

static sys_param_t g_sys_param = {0};

static const sys_param_t g_default_sys_param = {
    .need_hint = true,
    .sr_lang = SR_LANG_EN,
    .volume = 4, // default volume is 70%
    .standby_time = 0, //15sec
    .brightness = 60,
};

esp_err_t settings_factory_reset(void)
{
    ESP_LOGW(TAG, "Set to default");
    memcpy(&g_sys_param, &g_default_sys_param, sizeof(sys_param_t));

    // wifi_config_t wifi_cfg;
    // if (esp_wifi_get_config(WIFI_IF_STA, &wifi_cfg) != ESP_OK) {
    //     ESP_LOGW(TAG, "ssid|password:[%s:%s]", DEFAULT_ESP_WIFI_SSID, DEFAULT_ESP_WIFI_PASS);
    //     memcpy(&g_sys_param.ssid[0], DEFAULT_ESP_WIFI_SSID, strlen(DEFAULT_ESP_WIFI_SSID));
    //     memcpy(&g_sys_param.password[0], DEFAULT_ESP_WIFI_PASS, strlen(DEFAULT_ESP_WIFI_PASS));
    // } else {
    //     memcpy(&g_sys_param.ssid[0], wifi_cfg.sta.ssid, sizeof(wifi_cfg.sta.ssid) - 1);
    //     memcpy(&g_sys_param.password[0], wifi_cfg.sta.password, sizeof(wifi_cfg.sta.password) - 1);
    //     ESP_LOGI(TAG, "ssid|password:[%s:%s]", wifi_cfg.sta.ssid, wifi_cfg.sta.password);
    // }
    ESP_LOGW(TAG, "ssid|password:[%s:%s]", DEFAULT_ESP_WIFI_SSID, DEFAULT_ESP_WIFI_PASS);
    memcpy(&g_sys_param.ssid[0], DEFAULT_ESP_WIFI_SSID, strlen(DEFAULT_ESP_WIFI_SSID));
    memcpy(&g_sys_param.password[0], DEFAULT_ESP_WIFI_PASS, strlen(DEFAULT_ESP_WIFI_PASS));

    g_sys_param.password_len = strlen(g_sys_param.password);
    g_sys_param.ssid_len = strlen(g_sys_param.ssid);
    settings_write_parameter_to_nvs();

    return ESP_OK;
}

static esp_err_t settings_check(sys_param_t *param)
{
    esp_err_t ret;
    ESP_GOTO_ON_FALSE(param->sr_lang < SR_LANG_MAX, ESP_ERR_INVALID_ARG, reset, TAG, "language incorrect");
    ESP_GOTO_ON_FALSE(param->volume <= 5, ESP_ERR_INVALID_ARG, reset, TAG, "volume incorrect");
    ESP_GOTO_ON_FALSE(param->standby_time <= 3, ESP_ERR_INVALID_ARG, reset, TAG, "standby_time incorrect");
    ESP_GOTO_ON_FALSE(param->brightness <= 100, ESP_ERR_INVALID_ARG, reset, TAG, "brightness incorrect");

    if (((0 == param->ssid_len) || (param->ssid_len > 32)) || \
            ((0 == param->password_len) || (param->password_len > 64)) || \
            (param->ssid_len != strlen(param->ssid)) || \
            (param->password_len != strlen(param->password))) {
        ESP_LOGI(TAG, "ssid | password incorrect, [%d.%d, %d.%d]", \
                 param->ssid_len, strlen(param->ssid), param->password_len, strlen(param->password));
        goto reset;
    }

    return ret;
reset:
    settings_factory_reset();
    return ret;
}

esp_err_t settings_read_parameter_from_nvs(void)
{
    nvs_handle_t my_handle = 0;
    esp_err_t ret = nvs_open(NAME_SPACE, NVS_READONLY, &my_handle);
    if (ESP_ERR_NVS_NOT_FOUND == ret) {
        ESP_LOGW(TAG, "Not found, Set to default");
        memcpy(&g_sys_param, &g_default_sys_param, sizeof(sys_param_t));
        memcpy(&g_sys_param.ssid[0], DEFAULT_ESP_WIFI_SSID, strlen(DEFAULT_ESP_WIFI_SSID));
        memcpy(&g_sys_param.password[0], DEFAULT_ESP_WIFI_PASS, strlen(DEFAULT_ESP_WIFI_PASS));
        g_sys_param.ssid_len = strlen(DEFAULT_ESP_WIFI_SSID);
        g_sys_param.password_len = strlen(DEFAULT_ESP_WIFI_PASS);

        settings_write_parameter_to_nvs();
        return ESP_OK;
    }

    ESP_GOTO_ON_FALSE(ESP_OK == ret, ret, err, TAG, "nvs open failed (0x%x)", ret);

    size_t len = sizeof(sys_param_t);
    ret = nvs_get_blob(my_handle, KEY, &g_sys_param, &len);
    ESP_GOTO_ON_FALSE(ESP_OK == ret, ret, err, TAG, "can't read param");
    nvs_close(my_handle);

    settings_check(&g_sys_param);
    return ret;
err:
    if (my_handle) {
        nvs_close(my_handle);
    }
    return ret;
}

esp_err_t settings_write_parameter_to_nvs(void)
{
    ESP_LOGI(TAG, "Saving settings");
    settings_check(&g_sys_param);
    nvs_handle_t my_handle = {0};
    esp_err_t err = nvs_open(NAME_SPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGI(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        err = nvs_set_blob(my_handle, KEY, &g_sys_param, sizeof(sys_param_t));
        err |= nvs_commit(my_handle);
        nvs_close(my_handle);
    }
    return ESP_OK == err ? ESP_OK : ESP_FAIL;
}

sys_param_t *settings_get_parameter(void)
{
    return &g_sys_param;
}
