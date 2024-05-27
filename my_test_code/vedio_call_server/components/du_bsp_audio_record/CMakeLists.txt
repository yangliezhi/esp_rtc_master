
idf_component_register(SRCS "du_bsp_audio_record.c" "my_codec.c"
                        INCLUDE_DIRS "include"
                       PRIV_REQUIRES main esp_codec_dev
                       )
