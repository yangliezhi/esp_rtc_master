#include "du_led.h"
#include "led_strip.h"

static const char *TAG = "du_led";

static int g_left_led_state = 0;
static int g_right_led_state = 0;
static led_strip_handle_t g_strip_handle = NULL;

void app_led_init(void)
{
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &g_strip_handle));
    /* Set all LED off to clear all pixels */
    led_strip_clear(g_strip_handle);
}
void app_led_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    led_strip_set_pixel(g_strip_handle, 0, red, green, blue);
    led_strip_refresh(g_strip_handle);
}
void light_gpio_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LEFT_LED_PIN) | (1ULL << RIGHT_LED_PIN) | (1ULL << BRAKE_LED_PIN) | (1ULL << REVERSE_LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);
    gpio_set_level(LEFT_LED_PIN, 0);
    gpio_set_level(RIGHT_LED_PIN, 0);
    gpio_set_level(BRAKE_LED_PIN, 0);
    gpio_set_level(REVERSE_LED_PIN, 0);
}

void light_control_task(void *pvParameters)
{
    app_led_init();
    light_gpio_init();
    while (1)
    {
        if (g_left_led_state == 1)
        {
            ESP_LOGI(TAG, "About to turn left.");
            gpio_set_level(LEFT_LED_PIN, 1);
            gpio_set_level(RIGHT_LED_PIN, 0);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LEFT_LED_PIN, 0);
            gpio_set_level(RIGHT_LED_PIN, 0);
            vTaskDelay(400 / portTICK_PERIOD_MS);
        }
        else if (g_right_led_state == 1)
        {
            ESP_LOGI(TAG, "About to turn right.");
            gpio_set_level(LEFT_LED_PIN, 0);
            gpio_set_level(RIGHT_LED_PIN, 1);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            gpio_set_level(LEFT_LED_PIN, 0);
            gpio_set_level(RIGHT_LED_PIN, 0);
            vTaskDelay(400 / portTICK_PERIOD_MS);
        }
        else
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
}
