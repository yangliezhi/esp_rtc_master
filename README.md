# ESP32S3_rtc

#### 介绍
ESP32万能开发板测试例子 QQ群 26875961

#### 软件架构
软件架构说明


#### 安装教程

电路板已经开源 可以免费打板。代码会逐渐更新到这里。互相交流学习

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

这个是万能开发板ESP32S3芯片的ADF例子的测试代码 代码都测试通过 
用的是IDF5.2版本测试 。有问题进群留言交流

如果ADF 喇叭没播放 修改ADF库的文件如下 
#include "tca9554.h"

static const char *TAG = "AUDIO_BOARD";

static audio_board_handle_t board_handle = 0;

audio_board_handle_t audio_board_init(void)
{

    if (board_handle)
    {
        ESP_LOGW(TAG, "The board has already been initialized!");
        return board_handle;
    }
    board_handle = (audio_board_handle_t)audio_calloc(1, sizeof(struct audio_board_handle));
    AUDIO_MEM_CHECK(TAG, board_handle, return NULL);
    board_handle->audio_hal = audio_board_codec_init();
    board_handle->adc_hal = audio_board_adc_init();
    esp_tca9554_config_t pca_cfg = {
        .i2c_scl = GPIO_NUM_18,
        .i2c_sda = GPIO_NUM_17,
        .interrupt_output = -1,
    };
    // 这里是修改ESP32 RTC 3.0 板子
    tca9554_init(&pca_cfg);
    tca9554_set_io_config(BIT(0), TCA9554_IO_OUTPUT);
    tca9554_set_output_state(BIT(0), TCA9554_IO_HIGH);
    return board_handle;
}
