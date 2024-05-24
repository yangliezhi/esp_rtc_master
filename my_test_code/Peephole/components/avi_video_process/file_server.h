#pragma once
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "esp_err.h"
#include "esp_log.h"



#ifdef __cplusplus
extern "C" {
#endif

esp_err_t start_file_server(const char *base_path);

#ifdef __cplusplus
}
#endif