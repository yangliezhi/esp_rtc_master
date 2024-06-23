#pragma once
#include <stdbool.h>
#include <sys/queue.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_afe_sr_models.h"
#include "esp_mn_models.h"

#include "du_sr.h"

esp_err_t du_sr_speech(bool record_en);