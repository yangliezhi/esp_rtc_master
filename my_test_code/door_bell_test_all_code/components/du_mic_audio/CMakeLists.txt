idf_component_register(SRCS "du_mic_audio.c"
                    INCLUDE_DIRS "include"
                    REQUIRES
                    driver
                    fatfs
                    spiffs
                    main)
