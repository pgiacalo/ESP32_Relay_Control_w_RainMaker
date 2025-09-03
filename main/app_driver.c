/* Dual Relay Controller implementation using two relays
   
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sdkconfig.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_standard_devices.h>

#include <app_reset.h>
#include <ws2812_led.h>
#include "app_priv.h"

// External declarations for device pointers
extern esp_rmaker_device_t *relay1_device;
extern esp_rmaker_device_t *relay2_device;

static const char *TAG = "app_driver";

/* These values correspond to H,S,V = 120,100,10 */
#define DEFAULT_RED     0
#define DEFAULT_GREEN   25
#define DEFAULT_BLUE    0

// Global state variables - track current relay states
static bool g_relay1_state = DEFAULT_RELAY_1_STATE;
static bool g_relay2_state = DEFAULT_RELAY_2_STATE;

static void app_indicator_set(bool state)
{
    if (state) {
        ws2812_led_set_rgb(DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
    } else {
        ws2812_led_clear();
    }
}

static void app_indicator_init(void)
{
    ws2812_led_init();
    // Show indicator based on relay states (ON if either relay is closed)
    app_indicator_set(g_relay1_state || g_relay2_state);
}

void app_driver_init()
{
    // Set GPIO pins to default states immediately to prevent relay activation during startup
    gpio_set_level(RELAY_1_GPIO, !DEFAULT_RELAY_1_STATE);  // Invert since HIGH = relay open
    gpio_set_level(RELAY_2_GPIO, !DEFAULT_RELAY_2_STATE);  // Invert since HIGH = relay open
    
    /* Configure GPIO pins for both relays */
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 1,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };
    
    // Configure Relay 1 GPIO
    io_conf.pin_bit_mask = ((uint64_t)1 << RELAY_1_GPIO);
    gpio_config(&io_conf);
    
    // Configure Relay 2 GPIO
    io_conf.pin_bit_mask = ((uint64_t)1 << RELAY_2_GPIO);
    gpio_config(&io_conf);
    
    // Set initial states again (HIGH = relay open, LOW = relay closed) - double safety
    gpio_set_level(RELAY_1_GPIO, !g_relay1_state);  // Invert since HIGH = relay open
    gpio_set_level(RELAY_2_GPIO, !g_relay2_state);  // Invert since HIGH = relay open
    
    // Add a small delay to ensure pins are stable
    vTaskDelay(pdMS_TO_TICKS(100));
    
    app_indicator_init();
}

int IRAM_ATTR app_driver_set_relay1_state(bool state)
{
    ESP_LOGI(TAG, "Relay 1: Setting relay to %s (GPIO %d %s)", 
             state ? "CLOSED" : "OPEN", 
             RELAY_1_GPIO, 
             state ? "LOW" : "HIGH");
    
    // Update global state
    g_relay1_state = state;
    
    // Set GPIO level (HIGH = relay open, LOW = relay closed)
    gpio_set_level(RELAY_1_GPIO, !state);
    
    // Update indicator
    app_indicator_set(g_relay1_state || g_relay2_state);
    
    return ESP_OK;
}

int IRAM_ATTR app_driver_set_relay2_state(bool state)
{
    ESP_LOGI(TAG, "Relay 2: Setting relay to %s (GPIO %d %s)", 
             state ? "CLOSED" : "OPEN", 
             RELAY_2_GPIO, 
             state ? "LOW" : "HIGH");
    
    // Update global state
    g_relay2_state = state;
    
    // Set GPIO level (HIGH = relay open, LOW = relay closed)
    gpio_set_level(RELAY_2_GPIO, !state);
    
    // Update indicator
    app_indicator_set(g_relay1_state || g_relay2_state);
    
    return ESP_OK;
}

bool app_driver_get_relay1_state(void)
{
    return g_relay1_state;
}

bool app_driver_get_relay2_state(void)
{
    return g_relay2_state;
}
