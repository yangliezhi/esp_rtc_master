idf_component_register(SRCS avi_recorder.c file_server.c file_manager.c stram_server.c
                       INCLUDE_DIRS .
                       PRIV_REQUIRES esp_timer
                       REQUIRES main)
