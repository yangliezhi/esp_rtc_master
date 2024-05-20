输入声音文件

python .\esptool\esptool.py --chip esp32s3 --port COM3 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x110000 ./tools/audio-esp.bin