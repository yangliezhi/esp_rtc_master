set(APP_DIR ./app)
file(GLOB_RECURSE APP_SRCS ${APP_DIR}/*.c)

idf_component_register(SRCS  "app_main.cpp"  "event_logic.cpp"                            
                                ${APP_SRCS}
                    INCLUDE_DIRS "."  ${APP_DIR}
                    EMBED_FILES "favicon.ico" "upload_script.html")
