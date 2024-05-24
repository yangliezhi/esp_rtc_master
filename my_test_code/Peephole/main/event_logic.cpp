#include <stdio.h>
#include "event_logic.hpp"
#include "who_button.h"
#include "who_human_face_recognition.hpp"
#include "esp_log.h"

static const char *TAG = "event_logic";
// typedef enum
// {
//     MENU = 1,
//     PLAY,
//     UP,
//     DOWN
// } key_name_t;
typedef enum
{
    REC = 1,
    MUTE,
    PLAY,
    SET,
    VOL_DOWN,
    VOL_UP,
} key_name_t;

static QueueHandle_t xQueueKeyStateI = NULL;
static QueueHandle_t xQueueEventO = NULL;
static key_state_t key_state;
static key_name_t adc_button_name;
static recognizer_state_t recognizer_state;

void event_generate(void *arg)
{

    while (1)
    {
        xQueueReceive(xQueueKeyStateI, &key_state, portMAX_DELAY);

        switch (key_state)
        {
        case KEY_SHORT_PRESS:
            // ESP_LOGI(TAG, "test test.............................%d", key_state);
            recognizer_state = RECOGNIZE;
            break;

        case KEY_LONG_PRESS:
            recognizer_state = ENROLL;
            break;

        case KEY_DOUBLE_CLICK:
            recognizer_state = DELETE;
            break;

        default:
            recognizer_state = DETECT;
            break;
        }
        xQueueSend(xQueueEventO, &recognizer_state, portMAX_DELAY);
        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void event_generate_from_adc_button(void *arg)
{
    int touch_button_name = -1;
    int previous_state = -1;
    while (1)
    {
        xQueueReceive(xQueueKeyStateI, &touch_button_name, portMAX_DELAY);
        // ESP_LOGI(TAG, "test test.............................%d", adc_button_name);
        switch (touch_button_name)
        {
        case 1:
            recognizer_state = DOOR_BELL;

            break;

        case 6:
            recognizer_state = SR_DETECT;
            break;

        case 5:
            recognizer_state = SR_COMMAND;
            break;

        case 3:
            recognizer_state = RECOGNIZE;
            break;
        case 2:
            recognizer_state = ENROLL;
            break;

        case 4:
            recognizer_state = DELETE;
            break;
        default:
            recognizer_state = DETECT;
            break;
        }
       
        if (recognizer_state != previous_state) {
            xQueueSend(xQueueEventO, &recognizer_state, portMAX_DELAY);
            previous_state = recognizer_state;
        }
    }
}

void register_event(const QueueHandle_t key_state_i, const QueueHandle_t event_o)
{
    xQueueKeyStateI = key_state_i;
    xQueueEventO = event_o;
    xTaskCreatePinnedToCore(event_generate_from_adc_button, "event_logic_task", 1024 * 4, NULL, 5, NULL, 0);
}