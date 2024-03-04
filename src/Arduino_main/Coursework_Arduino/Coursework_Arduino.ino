/**
 * @file Coursework_Arduino.ino
 * @brief Special Signal Generator of DATA and SYNC for ESP32
 *
 * This program generates a sequence of signals based on the input from two buttons.
 * It uses the Arduino to control GPIOs on an ESP32 board.
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


#define PRODUCTION_TIMING 
// This define will run the PRODUCTION_TIMING process
// If we comment this line, we will run DEBUG process

#ifdef PRODUCTION_TIMING
#define TIME_BASE 50
// If PRODUCTION_TIMING be defined we define the macro TIME BASE as 50

#else 
// If PRODUCTION_TIMING not be defined we define the macro TIME BASE as 50000, so we can turn to DRBUG process
#define TIME_BASE 50000
#endif

// Define pin numbers

#define DATA 15
// Signal A
#define SYNC 21
// Signal B
#define Button1 22
#define Button2 23

#define A 24*TIME_BASE
#define B 12*TIME_BASE
#define C 10
#define D 60*TIME_BASE
#define WAIT 50
#define SYNCON 50


// Defining global variables


int OUTPUT_ENABLE_FLAG = 0;
int OUTPUT_SELECT_FLAG = 0;
// Define the two variable that determine the current signal status


void setup() {
  // Set Pin Modes
  pinMode(Button1, INPUT_PULLDOWN); // Using internal pull-up resistors
  pinMode(Button2, INPUT_PULLDOWN); // Using internal pull-up resistors
  // In order to add resistor instead of manually connect two resistors
  pinMode(DATA, OUTPUT);
  pinMode(SYNC, OUTPUT);
}

void loop() {
  int a = A; // Local pulse duration variable
  char c = C; // Local pulse quantity variable, changed to global to maintain its state

  // Read button states

  if (digitalRead(Button1) == 1) {
    // delay(WAIT);
    // Stop for a short time after reading the button signal, so that the signal status can be updated more easily
    // In cases where the button element is not very sensitive, it is not actually needed
    OUTPUT_ENABLE_FLAG += 1;
  }

  if (digitalRead(Button2) == 1) {
    // delay(WAIT);
    OUTPUT_SELECT_FLAG += 1;
  }

  if (OUTPUT_ENABLE_FLAG % 2 == 1) {
    // Generate signals when Button1 is pressed by odd times
    // Check if Button2 is pressed
    if (OUTPUT_SELECT_FLAG % 2 == 1) {
      c += 3; // Mode3：Increment c by 3
      // run mode3 when Button2 is pressed by odd times
      generateSignals(a, c);
    }
    else{
      generateSignals(a, c);
      // if the output_select is not odd, we run the normal mode
    }

  } else if (OUTPUT_ENABLE_FLAG % 2 == 0) {
    // if the Button1 is pressed even times
    digitalWrite(DATA, LOW);
    digitalWrite(SYNC, LOW);
  }

  // Small delay to debounce button
  // It is not actually needed

  // delayMicroseconds(100);
}


void generateSignals(int a, char c) {
  char i; // Declare the counter variable locally

  // Create SYNC(Signal B) Trigger waveform
  digitalWrite(SYNC, HIGH);
  delayMicroseconds(SYNCON);
  digitalWrite(SYNC, LOW);

  // Create iterative sequence of pulses for DATA(Signal A)
  for (i = 0; i < c; i++) {
    // Create rectangular pulse
    digitalWrite(DATA, HIGH);
    delayMicroseconds(a);
    digitalWrite(DATA, LOW);

    delayMicroseconds(B);
    a += TIME_BASE; // Increase the pulse duration for every next iteration
  }

  delayMicroseconds(D); // Wait for D microsecond for each full waveform
}








