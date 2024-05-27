# idf_component_register(SRCS "du_bsp_audio_record.c"
#                     INCLUDE_DIRS "include")
idf_component_register(SRCS "du_bsp_audio_record.c" "my_codec.c"
                        INCLUDE_DIRS "include"
                       PRIV_REQUIRES unity esp_codec_dev main
                       )
