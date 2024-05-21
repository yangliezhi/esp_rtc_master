修改地方如下
增加了针脚TCA9554代码 主要是RTC3.0版本的电路板

audio_hal_handle_t audio_hal_init(audio_hal_codec_config_t *audio_hal_conf, audio_hal_func_t *audio_hal_func)
{
    esp_err_t ret = 0;
    audio_hal_handle_t audio_hal = (audio_hal_handle_t)audio_calloc(1, sizeof(audio_hal_func_t));
    AUDIO_MEM_CHECK(TAG, audio_hal, return NULL);
    memcpy(audio_hal, audio_hal_func, sizeof(audio_hal_func_t));
    audio_hal->audio_hal_lock = mutex_create();

    AUDIO_MEM_CHECK(TAG, audio_hal->audio_hal_lock, {
        audio_free(audio_hal);
        return NULL;
    });
    mutex_lock(audio_hal->audio_hal_lock);
    ret = audio_hal->audio_codec_initialize(audio_hal_conf);
    if (ret == ESP_FAIL)
    {
        audio_free(audio_hal);
        if (audio_hal_func->handle)
        {
            return audio_hal_func->handle;
        }
        else
        {
            ESP_LOGE(TAG, "codec init failed!");
            return NULL;
        }
    }
    ret |= audio_hal->audio_codec_config_iface(audio_hal_conf->codec_mode, &audio_hal_conf->i2s_iface);
    ret |= audio_hal->audio_codec_set_volume(AUDIO_HAL_VOL_DEFAULT);
    AUDIO_RET_ON_FALSE(TAG, ret, return NULL, "audio_hal_init failed");
    audio_hal->handle = audio_hal;
    audio_hal_func->handle = audio_hal;
    mutex_unlock(audio_hal->audio_hal_lock);
    // 这里是修改ESP32 RTC 3.0 板子
    esp_tca9554_config_t pca_cfg = {
        .i2c_scl = GPIO_NUM_18,
        .i2c_sda = GPIO_NUM_17,
        .interrupt_output = -1,
    };
    tca9554_init(&pca_cfg);
    tca9554_set_io_config(BIT(0), TCA9554_IO_OUTPUT);
    tca9554_set_output_state(BIT(0), TCA9554_IO_HIGH);

    return audio_hal;
}
