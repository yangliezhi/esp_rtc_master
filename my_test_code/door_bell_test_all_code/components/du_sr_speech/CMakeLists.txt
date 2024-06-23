idf_component_register(SRCS  "du_sr_speech.c" "du_sr.c"
                    INCLUDE_DIRS "include"
                    REQUIRES "main" )
component_compile_options(-Wno-error=format= -Wno-format)   