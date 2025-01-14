# ESP-RTC example

- [English Version](./README.md)
- 例程难度：![alt text](../../../docs/_static/level_complex.png "高级")

## 例程简介

ESP RTC 是一个基于标准 SIP 协议的视频通话客户端，可以用于音视频通话等场景。

## 环境配置

### 硬件要求

本例程支持的开发板在 `$ADF_PATH/examples/README_CN.md` 文档中[例程与乐鑫音频开发板的兼容性表格](../../README_CN.md#例程与乐鑫音频开发板的兼容性)中有标注，表格中标有绿色复选框的开发板均可运行本例程。请记住，如下面的 [配置](#配置) 一节所述，可以在 `menuconfig` 中选择开发板。

本例程需要使用两块开发板来运行音视频对讲功能，同时建议您使用 `ESP32-S3-Korvo-2L` 开发板来运行本例程，以支持 UVC 和 UAC。

### 其他要求

- 您可以使用 Example 乐鑫自建的服务器来测试，具体测试账号可以联系乐鑫来获取。

- 或者您也可以搭建如下的任意 SIP PBX 服务器：

  - [Asterisk FreePBX](https://www.freepbx.org/downloads/)

  - [Asterisk for Raspberry Pi](http://www.raspberry-asterisk.org/)

  - [Freeswitch](https://freeswitch.org/confluence/display/FREESWITCH/Installation)
      - 建议关闭服务器事件通知 `NOTIFY`，可以通过在 `conf/sip_profiles/internal.xml` 中设置 `<param name="send-message-query-on-register" value="false"/>` 关闭通知。

      - 建议关闭服务器 timer，可以通过在 `conf/sip_profiles/internal.xml` 中设置 `<param name="enable-timer" value="false"/>` 来关闭。

      - 建议在 `conf/vars.xml` 中打开 PCMA、PCMU、VP8、H264。

- 我们建议搭建 Freeswitch 服务器来测试。

## 编译和下载

### IDF 默认分支

本例程支持 IDF release/v4.4 及以后的分支，例程默认使用 ADF 的內建分支 `$ADF_PATH/esp-idf`。

本例程还需给 IDF 合入 1 个 patch，合入命令如下：

```
cd $IDF_PATH
git apply $ADF_PATH/idf_patches/idf_v4.4_freertos.patch
```

### 配置

打开配置选项 `make menuconfig` 或 `idf.py menuconfig`

- 在 `menuconfig` > `Audio HAL` 中选择合适的开发板。
- 在 `ESP-RTC App Configuration` > `WiFi SSID` 和 `WiFi Password`。
- 在 `ESP-RTC App Configuration` > `SIP Codec` 中选择想要的编解码器。
- 在 `ESP-RTC App Configuration` > `SIP_URI` 中配置 SIP 登陆相关信息 (Transport://user:password@server:port)。
  - 例如：`tcp://100:100@192.168.1.123:5060`

### 编译和下载

请先编译版本并烧录到开发板上，然后运行 monitor 工具来查看串口输出（替换 PORT 为端口名称）：

```
idf.py -p PORT flash monitor
```

退出调试界面使用 ``Ctrl-]``

有关配置和使用 ESP-IDF 生成项目的完整步骤，请参阅 [《ESP-IDF 编程指南》](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v4.4/get-started/index.html)。

### 下载 flash 提示音

- 此应用额外需要下载一个提示音的 bin 到 flash 中：

```
python $ADF_PATH/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x210000 ../components/audio_flash_tone/bin/audio-esp.bin
```

## 如何使用例程

### 开发板功能和用法

- 例程开始运行后，在网络连接成功并且服务器也连接成功后会播放服务器已连接提示音。
- 按下 `PLAY` 键对您默认设置的对端号码进行拨号。
- 当来电铃声响起的时候，您可以按下 `REC` 键来进行接听。
- 通话时，您可以按下 `MUTE` 键来进行挂断或者取消拨号。
- 当您使用 Freeswitch 或者其它支持会议的服务器时，您可以按下 `SET` 键来进入默认会议房间进行测试。
- `Vol+` 和 `Vol-` 键可以调节开发板的通话音量。

### esp-rtc APK功能和用法

- 您需要一台 Android 手机来安装 `esp-rtc.apk`。
- 配置 Server 和 Account 信息，Buddy 为对端设备的账号。
- 按下 `CALL` 会对 Buddy 进行呼叫和通信
- 这里设备端到手机端图像是单向的，如需双向视频通信可使用2块开发来测试。
- 当配置为 H264 软件编码时，支持 linphone 和 microsip 进行单向视频通信。

## 技术支持
请按照下面的链接获取技术支持：

- 技术支持参见 [esp32.com](https://esp32.com/viewforum.php?f=20) 论坛
- 故障和新功能需求，请创建 [GitHub issue](https://github.com/espressif/esp-adf/issues)


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