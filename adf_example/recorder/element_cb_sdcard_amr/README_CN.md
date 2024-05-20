# 使用回调函数方式录制 AMR 文件到 microSD 卡例程

- [English Version](./README.md)
- 例程难度：![alt text](../../../docs/_static/level_basic.png "初级")


## 例程简介

本例程使用回调函数方式录制 10 秒的 AMR 音频文件，然后写入 microSD 卡中。此外，也可以使用消息队列处理事件，如 [pipeline_recording_to_sdcard](../pipeline_recording_to_sdcard/README_CN.md) 示例。

AMR 支持 AMR-NB、AMR-WB 两种种音频编码器。默认选择 AMR-NB 编码器录制音频，并保存在 microSD 卡中。

AMR 录音例程的管道如下所示：

```
[mic] ---> codec_chip ---> i2s_stream_reader ---> ringbuf1 ---> amr_encoder ---> ringbuf2 ---> fatfs_stream_writer ---> [amr_file]
                                                                    ▲
                                                            ┌───────┴────────┐
                                                            │  AMRNB_ENCODER │
                                                            │  AMRWB_ENCODER │
                                                            └────────────────┘
```

## 环境配置

### 硬件要求

本例程支持的开发板在 `$ADF_PATH/examples/README_CN.md` 文档中[例程与乐鑫音频开发板的兼容性表格](../../README_CN.md#例程与乐鑫音频开发板的兼容性)中有标注，表格中标有绿色复选框的开发板均可运行本例程。请记住，如下面的 [配置](#配置) 一节所述，可以在 `menuconfig` 中选择开发板。


## 编译和下载

### IDF 默认分支

本例程支持 IDF release/v3.3 及以后的分支，例程默认使用 ADF 的內建分支 `$ADF_PATH/esp-idf`。

### 配置

本例程需要准备一张 microSD 卡，并预先插入开发板中备用。

本例程默认选择的开发板是 `ESP32-Lyrat V4.3`，如果需要在其他的开发板上运行此例程，则需要在 menuconfig 中选择开发板的配置，例如选择 `ESP32-Lyrat-Mini V1.1`。

```
menuconfig > Audio HAL > ESP32-Lyrat-Mini V1.1
```

本例程默认的编码是 `AMRNB`，如果更改为 `AMRWB` 编码，需要在 `menuconfig` 中选择。

```
menuconfig > Example configuration > Audio encoder file type  > amrwb
```

### 编译和下载

请先编译版本并烧录到开发板上，然后运行 monitor 工具来查看串口输出（替换 PORT 为端口名称）：

```
idf.py -p PORT flash monitor
```

退出调试界面使用 ``Ctrl-]``。

有关配置和使用 ESP-IDF 生成项目的完整步骤，请参阅 [《ESP-IDF 编程指南》](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v4.2/esp32/index.html)。

## 如何使用例程

### 功能和用法

例程开始运行后，会提示录音开始，并打印录音读秒时间。日志如下：

```c
rst:0x1 (POWERON_RESET),boot:0x1f (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:7556
load:0x40078000,len:14368
ho 0 tail 12 room 4
load:0x40080400,len:5360
0x40080400: _init at ??:?

entry 0x40080710
I (29) boot: ESP-IDF v4.2.2-1-g379ca2123 2nd stage bootloader
I (29) boot: compile time 11:36:36
I (29) boot: chip revision: 3
I (33) boot_comm: chip revision: 3, min. bootloader chip revision: 0
I (40) qio_mode: Enabling default flash chip QIO
I (45) boot.esp32: SPI Speed      : 80MHz
I (50) boot.esp32: SPI Mode       : QIO
I (55) boot.esp32: SPI Flash Size : 2MB
I (59) boot: Enabling RNG early entropy source...
I (65) boot: Partition Table:
I (68) boot: ## Label            Usage          Type ST Offset   Length
I (75) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (83) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (90) boot:  2 factory          factory app      00 00 00010000 00100000
I (98) boot: End of partition table
I (102) boot_comm: chip revision: 3, min. application chip revision: 0
I (109) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f400020 size=0x45cd8 (285912) map
I (213) esp_image: segment 1: paddr=0x00055d00 vaddr=0x3ffb0000 size=0x023cc (  9164) load
I (217) esp_image: segment 2: paddr=0x000580d4 vaddr=0x40080000 size=0x07f44 ( 32580) load
0x40080000: _WindowOverflow4 at /hengyongchao/esp-idfs/esp-idf-v4.2.2-psram/components/freertos/xtensa/xtensa_vectors.S:1730

I (232) esp_image: segment 3: paddr=0x00060020 vaddr=0x400d0020 size=0x40244 (262724) map
0x400d0020: _stext at ??:?

I (320) esp_image: segment 4: paddr=0x000a026c vaddr=0x40087f44 size=0x0b574 ( 46452) load
0x40087f44: __sfvwrite_r at /builds/idf/crosstool-NG/.build/xtensa-esp32-elf/src/newlib/newlib/libc/stdio/fvwrite.c:166

I (349) boot: Loaded app from partition at offset 0x10000
I (349) boot: Disabling RNG early entropy source...
I (349) psram: This chip is ESP32-D0WD
I (354) spiram: Found 64MBit SPI RAM device
I (358) spiram: SPI RAM mode: flash 80m sram 80m
I (364) spiram: PSRAM initialized, cache is in low/high (2-core) mode.
I (371) cpu_start: Pro cpu up.
I (375) cpu_start: Application information:
I (380) cpu_start: Project name:     record_amr_cb
I (385) cpu_start: App version:      v2.2-239-g107e8c39
I (391) cpu_start: Compile time:     Nov 18 2021 11:36:30
I (397) cpu_start: ELF file SHA256:  7e65979c30bc4358...
I (403) cpu_start: ESP-IDF:          v4.2.2-1-g379ca2123
I (409) cpu_start: Starting app cpu, entry point is 0x40081e48
0x40081e48: call_start_cpu1 at /hengyongchao/esp-idfs/esp-idf-v4.2.2-psram/components/esp32/cpu_start.c:287

I (0) cpu_start: App cpu up.
I (912) spiram: SPI SRAM memory test OK
I (912) heap_init: Initializing. RAM available for dynamic allocation:
I (912) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (919) heap_init: At 3FFB2E20 len 0002D1E0 (180 KiB): DRAM
I (925) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (931) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (938) heap_init: At 400934B8 len 0000CB48 (50 KiB): IRAM
I (944) cpu_start: Pro cpu start user code
I (949) spiram: Adding pool of 4096K of external SPI memory to heap allocator
I (969) spi_flash: detected chip: gd
I (969) spi_flash: flash io: qio
W (969) spi_flash: Detected size(8192k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (980) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (990) spiram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1000) REC_AMR_SDCARD: [1.0] Mount sdcard
I (1500) REC_AMR_SDCARD: [2.0] Start codec chip
E (1500) gpio: gpio_install_isr_service(438): GPIO isr service already installed
I (1520) REC_AMR_SDCARD: [3.0] Create fatfs stream to write data to sdcard
I (1520) REC_AMR_SDCARD: [3.1] Create i2s stream to read audio data from codec chip
I (1520) REC_AMR_SDCARD: [3.2] Create amr encoder to encode amr format
I (1530) REC_AMR_SDCARD: [3.3] Create a ringbuffer and insert it between i2s reader and amr encoder
I (1540) REC_AMR_SDCARD: [3.4] Create a ringbuffer and insert it between amr encoder and fatfs_stream_writer
I (1550) REC_AMR_SDCARD: [3.5] Set up  uri (file as fatfs_stream, amr as amr encoder)
I (1560) REC_AMR_SDCARD: [4.0] Set callback function for audio_elements
I (1560) REC_AMR_SDCARD: [5.0] Start audio elements
I (1570) REC_AMR_SDCARD: Audio event 8 from iis element
I (1580) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (1580) REC_AMR_SDCARD: Audio event 8 from amr element
I (1590) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (1590) REC_AMR_SDCARD: [6.0] Record audio for 10 seconds
I (1770) REC_AMR_SDCARD: Audio event 8 from file element
I (1770) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (2650) REC_AMR_SDCARD: [ * ] Recorded 1 seconds...
I (3650) REC_AMR_SDCARD: [ * ] Recorded 2 seconds...
I (4660) REC_AMR_SDCARD: [ * ] Recorded 3 seconds...
I (5710) REC_AMR_SDCARD: [ * ] Recorded 4 seconds...
I (6740) REC_AMR_SDCARD: [ * ] Recorded 5 seconds...
I (7750) REC_AMR_SDCARD: [ * ] Recorded 6 seconds...
I (8790) REC_AMR_SDCARD: [ * ] Recorded 7 seconds...
I (9800) REC_AMR_SDCARD: [ * ] Recorded 8 seconds...
I (10820) REC_AMR_SDCARD: [ * ] Recorded 9 seconds...
I (11870) REC_AMR_SDCARD: [ * ] Recorded 10 seconds...
I (11880) REC_AMR_SDCARD: [7.0] Stop elements and release resources.
W (11880) AUDIO_ELEMENT: IN-[amr] AEL_IO_ABORT
I (11880) REC_AMR_SDCARD: Audio event 11 from amr element
I (11890) REC_AMR_SDCARD: Audio event 8 from amr element
I (11900) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
I (12040) REC_AMR_SDCARD: Audio event 11 from iis element
I (12040) REC_AMR_SDCARD: Audio event 8 from iis element
I (12040) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
I (12040) REC_AMR_SDCARD: Audio event 8 from amr element
I (12050) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
E (12050) AUDIO_ELEMENT: [amr] Element already stopped
W (12060) AUDIO_ELEMENT: IN-[file] AEL_IO_ABORT
I (12070) REC_AMR_SDCARD: Audio event 9 from file element
I (12070) REC_AMR_SDCARD: Audio event 8 from file element
I (12080) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
```


### 日志输出

以下为例程的完整日志。

```c
rst:0x1 (POWERON_RESET),boot:0x1f (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:7556
load:0x40078000,len:14368
ho 0 tail 12 room 4
load:0x40080400,len:5360
0x40080400: _init at ??:?

entry 0x40080710
I (29) boot: ESP-IDF v4.2.2-1-g379ca2123 2nd stage bootloader
I (29) boot: compile time 11:36:36
I (29) boot: chip revision: 3
I (33) boot_comm: chip revision: 3, min. bootloader chip revision: 0
I (40) qio_mode: Enabling default flash chip QIO
I (45) boot.esp32: SPI Speed      : 80MHz
I (50) boot.esp32: SPI Mode       : QIO
I (55) boot.esp32: SPI Flash Size : 2MB
I (59) boot: Enabling RNG early entropy source...
I (65) boot: Partition Table:
I (68) boot: ## Label            Usage          Type ST Offset   Length
I (75) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (83) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (90) boot:  2 factory          factory app      00 00 00010000 00100000
I (98) boot: End of partition table
I (102) boot_comm: chip revision: 3, min. application chip revision: 0
I (109) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f400020 size=0x45cd8 (285912) map
I (213) esp_image: segment 1: paddr=0x00055d00 vaddr=0x3ffb0000 size=0x023cc (  9164) load
I (217) esp_image: segment 2: paddr=0x000580d4 vaddr=0x40080000 size=0x07f44 ( 32580) load
0x40080000: _WindowOverflow4 at /hengyongchao/esp-idfs/esp-idf-v4.2.2-psram/components/freertos/xtensa/xtensa_vectors.S:1730

I (232) esp_image: segment 3: paddr=0x00060020 vaddr=0x400d0020 size=0x40244 (262724) map
0x400d0020: _stext at ??:?

I (320) esp_image: segment 4: paddr=0x000a026c vaddr=0x40087f44 size=0x0b574 ( 46452) load
0x40087f44: __sfvwrite_r at /builds/idf/crosstool-NG/.build/xtensa-esp32-elf/src/newlib/newlib/libc/stdio/fvwrite.c:166

I (349) boot: Loaded app from partition at offset 0x10000
I (349) boot: Disabling RNG early entropy source...
I (349) psram: This chip is ESP32-D0WD
I (354) spiram: Found 64MBit SPI RAM device
I (358) spiram: SPI RAM mode: flash 80m sram 80m
I (364) spiram: PSRAM initialized, cache is in low/high (2-core) mode.
I (371) cpu_start: Pro cpu up.
I (375) cpu_start: Application information:
I (380) cpu_start: Project name:     record_amr_cb
I (385) cpu_start: App version:      v2.2-239-g107e8c39
I (391) cpu_start: Compile time:     Nov 18 2021 11:36:30
I (397) cpu_start: ELF file SHA256:  7e65979c30bc4358...
I (403) cpu_start: ESP-IDF:          v4.2.2-1-g379ca2123
I (409) cpu_start: Starting app cpu, entry point is 0x40081e48
0x40081e48: call_start_cpu1 at /hengyongchao/esp-idfs/esp-idf-v4.2.2-psram/components/esp32/cpu_start.c:287

I (0) cpu_start: App cpu up.
I (912) spiram: SPI SRAM memory test OK
I (912) heap_init: Initializing. RAM available for dynamic allocation:
I (912) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (919) heap_init: At 3FFB2E20 len 0002D1E0 (180 KiB): DRAM
I (925) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (931) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (938) heap_init: At 400934B8 len 0000CB48 (50 KiB): IRAM
I (944) cpu_start: Pro cpu start user code
I (949) spiram: Adding pool of 4096K of external SPI memory to heap allocator
I (969) spi_flash: detected chip: gd
I (969) spi_flash: flash io: qio
W (969) spi_flash: Detected size(8192k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (980) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (990) spiram: Reserving pool of 32K of internal memory for DMA/internal allocations
I (1000) REC_AMR_SDCARD: [1.0] Mount sdcard
I (1500) REC_AMR_SDCARD: [2.0] Start codec chip
E (1500) gpio: gpio_install_isr_service(438): GPIO isr service already installed
I (1520) REC_AMR_SDCARD: [3.0] Create fatfs stream to write data to sdcard
I (1520) REC_AMR_SDCARD: [3.1] Create i2s stream to read audio data from codec chip
I (1520) REC_AMR_SDCARD: [3.2] Create amr encoder to encode amr format
I (1530) REC_AMR_SDCARD: [3.3] Create a ringbuffer and insert it between i2s reader and amr encoder
I (1540) REC_AMR_SDCARD: [3.4] Create a ringbuffer and insert it between amr encoder and fatfs_stream_writer
I (1550) REC_AMR_SDCARD: [3.5] Set up  uri (file as fatfs_stream, amr as amr encoder)
I (1560) REC_AMR_SDCARD: [4.0] Set callback function for audio_elements
I (1560) REC_AMR_SDCARD: [5.0] Start audio elements
I (1570) REC_AMR_SDCARD: Audio event 8 from iis element
I (1580) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (1580) REC_AMR_SDCARD: Audio event 8 from amr element
I (1590) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (1590) REC_AMR_SDCARD: [6.0] Record audio for 10 seconds
I (1770) REC_AMR_SDCARD: Audio event 8 from file element
I (1770) REC_AMR_SDCARD: AEL_STATUS_STATE_RUNNING
I (2650) REC_AMR_SDCARD: [ * ] Recorded 1 seconds...
I (3650) REC_AMR_SDCARD: [ * ] Recorded 2 seconds...
I (4660) REC_AMR_SDCARD: [ * ] Recorded 3 seconds...
I (5710) REC_AMR_SDCARD: [ * ] Recorded 4 seconds...
I (6740) REC_AMR_SDCARD: [ * ] Recorded 5 seconds...
I (7750) REC_AMR_SDCARD: [ * ] Recorded 6 seconds...
I (8790) REC_AMR_SDCARD: [ * ] Recorded 7 seconds...
I (9800) REC_AMR_SDCARD: [ * ] Recorded 8 seconds...
I (10820) REC_AMR_SDCARD: [ * ] Recorded 9 seconds...
I (11870) REC_AMR_SDCARD: [ * ] Recorded 10 seconds...
I (11880) REC_AMR_SDCARD: [7.0] Stop elements and release resources.
W (11880) AUDIO_ELEMENT: IN-[amr] AEL_IO_ABORT
I (11880) REC_AMR_SDCARD: Audio event 11 from amr element
I (11890) REC_AMR_SDCARD: Audio event 8 from amr element
I (11900) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
I (12040) REC_AMR_SDCARD: Audio event 11 from iis element
I (12040) REC_AMR_SDCARD: Audio event 8 from iis element
I (12040) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
I (12040) REC_AMR_SDCARD: Audio event 8 from amr element
I (12050) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED
E (12050) AUDIO_ELEMENT: [amr] Element already stopped
W (12060) AUDIO_ELEMENT: IN-[file] AEL_IO_ABORT
I (12070) REC_AMR_SDCARD: Audio event 9 from file element
I (12070) REC_AMR_SDCARD: Audio event 8 from file element
I (12080) REC_AMR_SDCARD: AEL_STATUS_STATE_STOPPED


```

## 技术支持
请按照下面的链接获取技术支持：

- 技术支持参见 [esp32.com](https://esp32.com/viewforum.php?f=20) 论坛
- 故障和新功能需求，请创建 [GitHub issue](https://github.com/espressif/esp-adf/issues)

我们会尽快回复。
