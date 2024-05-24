如果运行有问题 修改如下
void *audio_board_lcd_init(esp_periph_set_handle_t set, void *cb)
{
    esp_tca9554_config_t pca_cfg = {
        .i2c_scl = GPIO_NUM_18,
        .i2c_sda = GPIO_NUM_17,
        .interrupt_output = -1,
    };
    tca9554_init(&pca_cfg);
    // Set LCD_BL_CTRL output
    tca9554_set_io_config(LCD_CTRL_GPIO, TCA9554_IO_OUTPUT);
    // Set LCD_RST output
    tca9554_set_io_config(LCD_RST_GPIO, TCA9554_IO_OUTPUT);
    // Set LCD_CS pin output
    // tca9554_set_io_config(LCD_CS_GPIO, TCA9554_IO_OUTPUT);

    // tca9554_set_output_state(LCD_CTRL_GPIO, TCA9554_IO_HIGH);
    // tca9554_set_output_state(LCD_CS_GPIO, TCA9554_IO_HIGH);
    // vTaskDelay(10 / portTICK_PERIOD_MS);
    // tca9554_set_output_state(LCD_CS_GPIO, TCA9554_IO_LOW);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    spi_bus_config_t buscfg = {
        .sclk_io_num = LCD_CLK_GPIO,
        .mosi_io_num = LCD_MOSI_GPIO,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_V_RES * LCD_H_RES * 2,
        .intr_flags = ESP_INTR_FLAG_SHARED | ESP_INTR_FLAG_LOWMED
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_DC_GPIO,
        .cs_gpio_num = 46,
        .pclk_hz = 60 * 1000 * 1000,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = cb,
        .user_ctx = NULL,
    };
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = -1,
        .color_space = ESP_LCD_COLOR_SPACE_BGR,
        .bits_per_pixel = 16,
    };
    periph_lcd_cfg_t cfg = {
        .io_bus = (void *)SPI3_HOST,
        .new_panel_io = _get_lcd_io_bus,
        .lcd_io_cfg = &io_config,
        .new_lcd_panel = esp_lcd_new_panel_st7789,
        .lcd_dev_cfg = &panel_config,
        .rest_cb = _lcd_rest,
        .rest_cb_ctx = NULL,
        .lcd_swap_xy = LCD_SWAP_XY,
        .lcd_mirror_x = LCD_MIRROR_X,
        .lcd_mirror_y = LCD_MIRROR_Y,
        .lcd_color_invert = LCD_COLOR_INV,
    };
    esp_periph_handle_t periph_lcd = periph_lcd_init(&cfg);
    AUDIO_NULL_CHECK(TAG, periph_lcd, return NULL);
    esp_periph_start(set, periph_lcd);
    return (void *)periph_lcd_get_panel_handle(periph_lcd);
}