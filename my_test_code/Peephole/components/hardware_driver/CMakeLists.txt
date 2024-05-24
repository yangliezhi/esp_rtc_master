
list(APPEND BSP_BOARD_SRC "./boards/esp32s3-korvo-2")

idf_component_register(
    SRC_DIRS
        ./
        ${BSP_BOARD_SRC}
    INCLUDE_DIRS
        "include"
        "boards/include"
    REQUIRES
        main
        driver
        fatfs
        spiffs
        )

component_compile_options(-w)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
