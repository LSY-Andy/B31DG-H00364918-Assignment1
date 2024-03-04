/**
 * @file main.c
 * @brief Special Signal Generator of DATA and SYNC for ESP32
 *
 * This program generates a sequence of signals based on the input from two buttons.
 * It uses the ESP-IDF framework to control GPIOs on an ESP32 board.
 * The timing of signals can be adjusted for production or debugging
 *
 * @author Shiyu Lu
 * @date 04-03-2024
 * @version 2.0.0
 *
 * Copyright (c) 2024 Shiyu Lu. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */



#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rom/ets_sys.h"
#include <esp_timer.h>

// Define GPIO pin numbers for signals and buttons
#define DATA 15 // Signal A
#define SYNC 21 // Signal B
#define Button1 22
#define Button2 23

// If comment this line the production mode will turn to DEBUG mode
#define PRODUCTION_TIMING

#ifdef PRODUCTION_TIMING
#define TIME_BASE 50
#else
#define TIME_BASE 50000
#endif

// Define constants for signal generation based on the TIME_BASE
const int A = 24 * TIME_BASE;
const int B = 12 * TIME_BASE;
const int C = 10;
const int D = 60 * TIME_BASE;
const int WAIT = 50;
const int SYNCON = 50;

static const char *TAG = "SignalGenerator"; // Tag for logging

// Defining global variables
int OUTPUT_ENABLE_FLAG = 0;
int OUTPUT_SELECT_FLAG = 0;

void generateSignals(int a, int c) {
    int i;

    ESP_LOGD(TAG, "SYNC pulse generated");
    // Create SYNC (Signal B) Trigger waveform
    gpio_set_level(SYNC, 1);
    ets_delay_us(SYNCON);
    gpio_set_level(SYNC, 0);

    // Create iterative sequence of pulses for DATA (Signal A)
    for (i = 0; i < c; i++) {
        gpio_set_level(DATA, 1);
        ets_delay_us(a);
        gpio_set_level(DATA, 0);
        ets_delay_us(B);
        a += TIME_BASE; // Increase the pulse duration for every next iteration
        ESP_LOGD(TAG, "DATA pulse %d generated with duration %d", i+1, a);
    }
    ets_delay_us(D); // Wait for D microseconds for each full waveform
}

void setup() {
    // Reset and configure the GPIO pins for buttons and signals
    gpio_reset_pin(Button1);
    gpio_reset_pin(Button2);
    gpio_reset_pin(DATA);
    gpio_reset_pin(SYNC);

    gpio_set_direction(Button1,GPIO_MODE_INPUT);
    gpio_set_direction(Button2,GPIO_MODE_INPUT);
    gpio_set_direction(DATA,GPIO_MODE_OUTPUT);
    gpio_set_direction(SYNC,GPIO_MODE_OUTPUT);

    gpio_pulldown_en(Button1);
    gpio_pulldown_en(Button2);
}


void app_main() {
    ESP_LOGI(TAG, "Starting main loop");
    setup();
    while (1) {
        int a = A; // Local pulse duration variable
        int c = C; // Local pulse quantity variable

        // Read button states
        if (gpio_get_level(Button1)==1) {
            OUTPUT_ENABLE_FLAG += 1;
            vTaskDelay(TIME_BASE/portTICK_PERIOD_MS);
        }

        if (gpio_get_level(Button2)==1) {
            OUTPUT_SELECT_FLAG += 1;
            vTaskDelay(TIME_BASE/portTICK_PERIOD_MS);
        }

        if (OUTPUT_ENABLE_FLAG % 2 == 1) {
            if (OUTPUT_SELECT_FLAG % 2 == 1) {
                c += 3; // Mode3: Increment c by 3
                generateSignals(a, c);
            } else {
                generateSignals(a, c);
            }
        } else if (OUTPUT_ENABLE_FLAG % 2 == 0) {
            gpio_set_level(DATA, 0);
            gpio_set_level(SYNC, 0);
        }
    }
}
