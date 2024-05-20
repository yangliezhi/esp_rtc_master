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

