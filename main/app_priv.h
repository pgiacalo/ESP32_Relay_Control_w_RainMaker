/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#pragma once
#include <stdint.h>
#include <stdbool.h>

// GPIO pins for the two relays
// These pins are compatible with both ESP32 (0-33 output range) and ESP32C6 (0-30 output range)
#define RELAY_1_GPIO    15  // First relay control output
#define RELAY_2_GPIO    19  // Second relay control output

// Default states (HIGH = relay open, LOW = relay closed)
#define DEFAULT_RELAY_1_STATE  false   // LOW by default (relay closed)
#define DEFAULT_RELAY_2_STATE  false   // LOW by default (relay closed)

extern esp_rmaker_device_t *relay1_device;
extern esp_rmaker_device_t *relay2_device;

void app_driver_init(void);
int app_driver_set_relay1_state(bool state);
int app_driver_set_relay2_state(bool state);
bool app_driver_get_relay1_state(void);
bool app_driver_get_relay2_state(void);
