智能可视门铃  
 界面设计用GUI-GUIDER

程序设计 调用ESP32 最新的组件 直接调用API就可以了

dependencies:
//lvgl可以驱动LCD触摸屏组件
  esp_lvgl_port:
    public: true
    version: ^1
  esp_lcd_ili9341:
    version: ^1    
  esp_lcd_touch_gt911:
    version: ^1    

//声音组件  可以驱动麦克风和喇叭  ES7210  ES8311  
  esp_codec_dev:
    public: true
    version: ^1.0.3   
//播放音乐WAV  MP3格式的文件组件
  chmorgan/esp-audio-player: "1.0.5"
  chmorgan/esp-file-iterator: "1.0.0"
  esp_codec_dev:
    version: "^1.0.2"
    public: true    

//按键组件
  button:
    public: true
    version: '>=2.5'

//tca9554组件 驱动IO扩展   
  espressif/esp_io_expander_tca9554:
    version: "^1.0.1"

这个修改为测试代码 可以测试全套硬件是否正常的代码
功能简介
嗨 乐鑫  唤醒后 你有5秒钟录制声音 然后回放你的声音的功能 这样可以测试麦克风和喇叭是否正常。点击屏幕按键 可以显示摄像头图像 测试摄像头功能  触摸功能 和屏幕功能。