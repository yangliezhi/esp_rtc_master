/*
 * @Author: dujianmin@qq:20130527
 * @Date: 2024-04-26 01:22:33
 * @Last Modified by: dujianmin
 * @Last Modified time: 2024-04-26 01:24:41
 */
#include <stdio.h>
#include "du_bsp_motor_mcpwm.h"

const static char *TAG = "du_bsp_motor_mcpwm";

mcpwm_cmpr_handle_t comparators[4];


MotorSpeeds mySpeeds = {{100, 200, 300, 400}};

void du_set_motor_speed(const MotorSpeeds *speeds)
{
    for (size_t i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparators[i], speeds->values[i]));
    }
}
void du_bsp_mcpwm_init(void)
{
    ESP_LOGI(TAG, "Create timers");
    mcpwm_timer_handle_t timers[4];
    mcpwm_timer_config_t timer_config = {
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .group_id = 0,
        .resolution_hz = EXAMPLE_TIMER_RESOLUTION_HZ,
        .period_ticks = EXAMPLE_TIMER_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    for (int i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timers[i]));
    }

    ESP_LOGI(TAG, "Create operators");
    mcpwm_oper_handle_t operators[4];
    mcpwm_operator_config_t operator_config = {
        .group_id = 0, // operator should be in the same group of the above timers
    };
    for (int i = 0; i < 4; ++i)
    {
        ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &operators[i]));
    }

    ESP_LOGI(TAG, "Connect timers and operators with each other");
    for (int i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operators[i], timers[i]));
    }

    ESP_LOGI(TAG, "Create comparators");

    mcpwm_comparator_config_t compare_config = {
        .flags.update_cmp_on_tez = true,
    };
    for (int i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_new_comparator(operators[i], &compare_config, &comparators[i]));
        // init compare for each comparator
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparators[i], 0));
    }

    ESP_LOGI(TAG, "Create generators");
    mcpwm_gen_handle_t generators[4];
    const int gen_gpios[4] = {EXAMPLE_GEN_GPIO0, EXAMPLE_GEN_GPIO1, EXAMPLE_GEN_GPIO2, EXAMPLE_GEN_GPIO3};
    mcpwm_generator_config_t gen_config = {};
    for (int i = 0; i < 4; i++)
    {
        gen_config.gen_gpio_num = gen_gpios[i];
        ESP_ERROR_CHECK(mcpwm_new_generator(operators[i], &gen_config, &generators[i]));
    }

    ESP_LOGI(TAG, "Set generator actions on timer and compare event");
    for (int i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generators[i],
                                                                  // when the timer value is zero, and is counting up, set output to high
                                                                  MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
        ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generators[i],
                                                                    // when compare event happens, and timer is counting up, set output to low
                                                                    MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparators[i], MCPWM_GEN_ACTION_LOW)));
    }

    ESP_LOGI(TAG, "Start timers one by one, so they are not synced");
    for (int i = 0; i < 4; i++)
    {
        ESP_ERROR_CHECK(mcpwm_timer_enable(timers[i]));
        ESP_ERROR_CHECK(mcpwm_timer_start_stop(timers[i], MCPWM_TIMER_START_NO_STOP));
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}