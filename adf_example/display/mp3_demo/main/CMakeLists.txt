idf_component_register(
    SRCS 
        "mp3_demo.c"
        "ui_audio.c"
        "font/font_cn_gb1_16.c"
        "font/font_cn_gb1_28.c"
        "font/ui_font_SourceHanSansCN14.c"
    INCLUDE_DIRS
        "include")

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
