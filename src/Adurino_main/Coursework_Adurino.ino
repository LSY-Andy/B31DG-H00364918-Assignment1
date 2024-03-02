// Define pin numbers

// #define PRODUCTION_TIMING

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

void setup() {
  // Serial.begin(9600);
  // Set Pin Modes
  pinMode(Button1, INPUT_PULLDOWN); // Using internal pull-up resistors
  pinMode(Button2, INPUT_PULLDOWN); // Using internal pull-up resistors
  pinMode(SignalA, OUTPUT);
  pinMode(SignalB, OUTPUT);
}

void loop() {
  int a = A; // Local pulse duration variable
  char c = C; // Local pulse quantity variable, changed to global to maintain its state
  // generateSignals(a, c);
  
  // Read button states

  if (digitalRead(Button1) == 1) {
    delay(WAIT);
    // 停的时间久一点 让我button更好读到
    FLAG1 += 1;
  }

  if (digitalRead(Button2) == 1) {
    delay(WAIT);
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
    digitalWrite(SignalA, LOW);
    digitalWrite(SignalB, LOW);
    // delay(WAIT);
    // // 停的时间久一点 让我button更好读到
    }
    else{
      generateSignals(a, c);
    }

  } else if (FLAG1 % 2 == 0) {
    // Serial.println("Zero status");
    digitalWrite(SignalA, LOW);
    digitalWrite(SignalB, LOW);
    // delay(WAIT);
    // // 停的时间久一点 让我button更好读到
  }


  // Small delay to debounce button
  delayMicroseconds(100);
}


void generateSignals(int a, char c) {
  char i; // Declare the counter variable locally

  // Create Signal B Trigger waveform
  digitalWrite(SignalB, HIGH);
  // delayMicroseconds(50);
  delayMicroseconds(TIME_BASE);
  digitalWrite(SignalB, LOW);

  // Serial.println("Signal B happened");

  // Create iterative sequence of pulses for Signal A
  for (i = 0; i < c; i++) {
    // Create rectangular pulse
    digitalWrite(SignalA, HIGH);
    delayMicroseconds(a);
    digitalWrite(SignalA, LOW);

    delayMicroseconds(B);
    a += TIME_BASE; // Increase the pulse duration for every next iteration
    // Serial.println("Signal A");
  }

  // Serial.println("One circle finished");
  delayMicroseconds(D); // Wait some time here
}








