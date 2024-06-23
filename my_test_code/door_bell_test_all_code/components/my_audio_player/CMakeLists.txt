idf_component_register(SRCS "my_audio_player.c" "ui_audio.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES unity  
                    REQUIRES "main" "esp_codec_dev"
                    EMBED_TXTFILES gs-16b-1c-44100hz.mp3)
