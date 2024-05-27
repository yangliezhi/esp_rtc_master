#include <stdio.h>
#include "du_ledc_motor.h"
#include "du_led.h"

static const char *TAG = "du_ledc_motor";
static void channel_pwm_output(ledc_channel_t channel, uint32_t duty)
{
    ESP_ERROR_CHECK(ledc_set_duty(PWM_MODE, channel, duty));
    ESP_ERROR_CHECK(ledc_update_duty(PWM_MODE, channel));
}
void example_pwm_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t pwm_timer = {
        .speed_mode = PWM_MODE,
        .timer_num = PWM_TIMER,
        .duty_resolution = PWM_DUTY_RES,
        .freq_hz = PWM_FREQUENCY, // Set output frequency at 5 kHz
        .clk_cfg = PWM_CLK_TYPE};
    ESP_ERROR_CHECK(ledc_timer_config(&pwm_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t pwm_channel_1 = {
        .speed_mode = PWM_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = PWM_TIMER,
        .intr_type = PWM_INTR_TYPE,
        .gpio_num = motor1_left_a,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};

    ledc_channel_config_t pwm_channel_2 = {
        .speed_mode = PWM_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = PWM_TIMER,
        .intr_type = PWM_INTR_TYPE,
        .gpio_num = motor1_left_b,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};
    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t pwm_channel_3 = {
        .speed_mode = PWM_MODE,
        .channel = LEDC_CHANNEL_2,
        .timer_sel = PWM_TIMER,
        .intr_type = PWM_INTR_TYPE,
        .gpio_num = motor1_right_a,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};

    ledc_channel_config_t pwm_channel_4 = {
        .speed_mode = PWM_MODE,
        .channel = LEDC_CHANNEL_3,
        .timer_sel = PWM_TIMER,
        .intr_type = PWM_INTR_TYPE,
        .gpio_num = motor1_right_b,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};

    ledc_channel_config_t pwm_channel_5 = {
        .speed_mode = PWM_MODE,
        .channel = LEDC_CHANNEL_4,
        .timer_sel = PWM_TIMER,
        .intr_type = PWM_INTR_TYPE,
        .gpio_num = servo1_gpio,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};

    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_1));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_2));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_3));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_4));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_5));
}
int cal_data_value = 14;
void remote_control(int ch1_value, int ch2_value, int ch3_value, int ch4_value, int ch5_value, int ch6_value, int ch7_value, int ch8_value)
{
    static int pre_ch1_value = 0;
    static int pre_ch2_value = 0;
    static int pre_ch3_value = 0;
    static int pre_ch4_value = 0;
    static int pre_ch5_value = 0;
    static int pre_ch7_value = 0;
    static int pre_ch8_value = 0;
    if (pre_ch1_value != ch1_value)
    {
        pre_ch1_value = ch1_value;
    }

    if (pre_ch2_value != ch2_value)
    {

        float throttle_value = ch2_value - 90.0 + cal_data_value;
        float ch2_duty = 0.0;
        if (throttle_value >= 0)
        {
            if (throttle_value > 5)
            {
                ESP_LOGI(TAG, "Forward.");
            }
            gpio_set_level(REVERSE_LED_PIN, 0);
            ch2_duty = throttle_value * 10.0;
            channel_pwm_output(LEDC_CHANNEL_0, (int)ch2_duty);
            channel_pwm_output(LEDC_CHANNEL_1, 0);
        }
        else
        {
            if (throttle_value < -5)
            {
                gpio_set_level(REVERSE_LED_PIN, 1);
                ESP_LOGI(TAG, "Backward.");
            }
            ch2_duty = -throttle_value * 6.0;
            channel_pwm_output(LEDC_CHANNEL_1, (int)ch2_duty);
            channel_pwm_output(LEDC_CHANNEL_0, 0);
        }

        pre_ch2_value = ch2_value;
    }

    if (pre_ch3_value != ch3_value)
    {
        float steer_value = (ch3_value + 8) / 2.8;
        float ch3_duty = ((steer_value / 90.0 + 0.5) / 20.0) * 1024;
        channel_pwm_output(LEDC_CHANNEL_4, (int)ch3_duty);
        if (ch3_value > 100)
        {
            // g_right_led_state = 0;
            ESP_LOGI(TAG, "Turn right.");
        }
        else if (ch3_value < 80)
        {
            // g_left_led_state = 0;
            ESP_LOGI(TAG, "Turn left.");
        }
        pre_ch3_value = ch3_value;
    }

    if (pre_ch4_value != ch4_value)
    {
        pre_ch4_value = ch4_value;
    }

    if (pre_ch5_value != ch5_value)
    {
        pre_ch5_value = ch5_value;
    }

    if (ch6_value == 1)
    {
        ESP_LOGI(TAG, "Braking...");
        gpio_set_level(BRAKE_LED_PIN, 1);
        channel_pwm_output(LEDC_CHANNEL_0, 0);
        channel_pwm_output(LEDC_CHANNEL_1, 0);
    }
    else
    {
        gpio_set_level(BRAKE_LED_PIN, 0);
    }

    if (pre_ch7_value != ch7_value)
    {
        // g_left_led_state = !g_left_led_state;
        // g_right_led_state = 0;
        pre_ch7_value = ch7_value;
    }

    if (pre_ch8_value != ch8_value)
    {
        // g_left_led_state = 0;
        // g_right_led_state = !g_right_led_state;
        pre_ch8_value = ch8_value;
    }
}

void du_remote_control(int ch1_value, int ch2_value, int ch3_value, int ch4_value, int ch5_value, int ch6_value, int ch7_value, int ch8_value)
{
    static int pre_ch1_value = 0;
    static int pre_ch2_value = 0;
    static int pre_ch3_value = 0;
    static int pre_ch4_value = 0;
    static int pre_ch5_value = 0;
    static int pre_ch6_value = 0;
    static int pre_ch7_value = 0;
    static int pre_ch8_value = 0;
    if (pre_ch1_value != ch1_value)
    {
        float throttle_value = ch1_value - 90.0;
        float ch1_duty = 0.0;
        if (throttle_value >= 0)
        {
            if (throttle_value > 5)
            {
                ESP_LOGI(TAG, "Forward.");
            }
            gpio_set_level(REVERSE_LED_PIN, 0);
            ch1_duty = throttle_value * 10.0;
            channel_pwm_output(LEDC_CHANNEL_2, (int)ch1_duty);
            channel_pwm_output(LEDC_CHANNEL_3, 0);
        }
        else
        {
            if (throttle_value < -5)
            {
                gpio_set_level(REVERSE_LED_PIN, 1);
                ESP_LOGI(TAG, "Backward.");
            }
            ch1_duty = -throttle_value * 6.0;
            channel_pwm_output(LEDC_CHANNEL_3, (int)ch1_duty);
            channel_pwm_output(LEDC_CHANNEL_2, 0);
        }

        pre_ch1_value = ch1_value;
    }

    if (pre_ch2_value != ch2_value)
    {
        float throttle_value = ch2_value - 90.0;
        float ch2_duty = 0.0;
        if (throttle_value >= 0)
        {
            if (throttle_value > 5)
            {
                ESP_LOGI(TAG, "Forward.");
            }
            gpio_set_level(REVERSE_LED_PIN, 0);
            ch2_duty = throttle_value * 10.0;
            channel_pwm_output(LEDC_CHANNEL_0, (int)ch2_duty);
            channel_pwm_output(LEDC_CHANNEL_1, 0);
        }
        else
        {
            if (throttle_value < -5)
            {
                gpio_set_level(REVERSE_LED_PIN, 1);
                ESP_LOGI(TAG, "Backward.");
            }
            ch2_duty = -throttle_value * 6.0;
            channel_pwm_output(LEDC_CHANNEL_1, (int)ch2_duty);
            channel_pwm_output(LEDC_CHANNEL_0, 0);
        }

        pre_ch2_value = ch2_value;
    }

    if (pre_ch3_value != ch3_value)
    {
        float steer_value = (ch3_value + 8) / 2.8;
        float ch3_duty = ((steer_value / 90.0 + 0.5) / 20.0) * 1024;
        channel_pwm_output(LEDC_CHANNEL_4, (int)ch3_duty);
        if (ch3_value > 100)
        {
            // g_right_led_state = 0;
            ESP_LOGI(TAG, "Turn right.");
        }
        else if (ch3_value < 80)
        {
            // g_left_led_state = 0;
            ESP_LOGI(TAG, "Turn left.");
        }
        pre_ch3_value = ch3_value;
    }

    if (pre_ch4_value != ch4_value)
    {
        pre_ch4_value = ch4_value;
    }

    if (pre_ch5_value != ch5_value)
    {
        pre_ch5_value = ch5_value;
    }

    if (pre_ch6_value != ch6_value)
    {
        pre_ch6_value = ch6_value;
    }

    if (pre_ch7_value != ch7_value)
    {

        pre_ch7_value = ch7_value;
    }

    if (pre_ch8_value != ch8_value)
    {

        pre_ch8_value = ch8_value;
    }
}