#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief
     *
     * @param key_state_i
     * @param event_o
     */
    void register_event(const QueueHandle_t key_state_i, const QueueHandle_t event_o);

#ifdef __cplusplus
}
#endif
