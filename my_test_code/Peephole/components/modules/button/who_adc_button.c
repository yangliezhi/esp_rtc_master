/* ADC1 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_oneshot.h"
#include "who_adc_button.h"


static const char *TAG = "ADC SINGLE";

static QueueHandle_t xQueueKeyStateO = NULL;

extern int select_switch;
static void touch_button_task(void *arg)
{

    while (1)
    {
        
        if (select_switch == 2 || select_switch == 3 || select_switch == 4)
        {
            xQueueOverwrite(xQueueKeyStateO, &select_switch);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void register_adc_button(const QueueHandle_t key_state_o)
{
    xQueueKeyStateO = key_state_o;

    xTaskCreatePinnedToCore(touch_button_task, "adc_button_scan_task", 3 * 1024, NULL, 5, NULL, 0);
}