#include <stdio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rom/ets_sys.h"

// Define pin numbers

#define PRODUCTION_TIMING

#ifdef PRODUCTION_TIMING
#define TIME_BASE 50
#else 
#define TIME_BASE 50000
#endif


#define SignalA 15
#define SignalB 21
#define Button1 22
#define Button2 23

#define A 24*TIME_BASE
#define B 12*TIME_BASE
#define C 10
#define D 60*TIME_BASE
#define WAIT 50

// Defining global variables


int FLAG1 = 0;
int FLAG2 = 0;

// Defining global variables
// char switch1; // Button 1 read state
// char switch2; // Button 2 read state
void generateSignals(int a, char c) {
  char i; // Declare the counter variable locally

  // Create Signal B Trigger waveform
  gpio_set_level(SignalB,1);
  // delayMicroseconds(50);
  ets_delay_us(TIME_BASE);
  gpio_set_level(SignalB,0);

  // Serial.println("Signal B happened");

  // Create iterative sequence of pulses for Signal A
  for (i = 0; i < c; i++) {
    // Create rectangular pulse
    gpio_set_level(SignalA,1);
    ets_delay_us(a);
    gpio_set_level(SignalA,0);
    ets_delay_us(B);
    a += TIME_BASE; // Increase the pulse duration for every next iteration
    // Serial.println("Signal A");
  }

  // Serial.println("One circle finished");
  ets_delay_us(D);
}



void app_main(void) {

  gpio_reset_pin(Button1);
  gpio_reset_pin(Button2);
  gpio_reset_pin(SignalA);
  gpio_reset_pin(SignalB);

  gpio_set_direction(Button1,GPIO_MODE_INPUT);
  gpio_set_direction(Button2,GPIO_MODE_INPUT);
  gpio_set_direction(SignalA,GPIO_MODE_OUTPUT);
  gpio_set_direction(SignalB,GPIO_MODE_OUTPUT);

  gpio_pulldown_en(Button1);
  gpio_pulldown_en(Button2);



  int a = A; // Local pulse duration variable
  char c = C; // Local pulse quantity variable, changed to global to maintain its state
  // generateSignals(a, c);
  
  // Read button states

  if (gpio_get_level(Button1) == 1) {
    ets_delay_us(WAIT);
    // 停的时间久一点 让我button更好读到
    FLAG1 += 1;
  }

  if (gpio_get_level(Button2) == 1) {
    ets_delay_us(WAIT);
    // 停的时间久一点 让我button更好读到
    FLAG2 += 1;
  }

  // Check if Button1 is pressed
  if (FLAG1 % 2 == 1) {
    // Serial.println("Press switch1");
    // Generate signals when Button1 is pressed
    // Check if Button2 is pressed
    if (FLAG2 % 2 == 1) {
      c += 3; // Increment c by 3
      // Generate signals when Button2 is pressed
      generateSignals(a, c);
    }
    else if (FLAG1 % 2 == 0) {
    // Serial.println("Zero status");
    gpio_set_level(SignalA,0);
    gpio_set_level(SignalB,0);
    // delay(WAIT);
    // // 停的时间久一点 让我button更好读到
    }
    else{
      generateSignals(a, c);
    }

  } else if (FLAG1 % 2 == 0) {
    // Serial.println("Zero status");
    gpio_set_level(SignalA,0);
    gpio_set_level(SignalB,0);
    // delay(WAIT);
    // // 停的时间久一点 让我button更好读到
  }


  // Small delay to debounce button
  ets_delay_us(100);
}












