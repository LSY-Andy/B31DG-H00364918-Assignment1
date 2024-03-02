#define SignalA 15
#define SignalB 21
#define Button1 22
#define Button2 23

#define A 1200
#define B 600
#define C 10
#define D 3000

// Defining global variables
char c = C; // Local pulse quantity variable, changed to global to maintain its state


// Defining global variables
char switch1; // Button 1 read state
char switch2; // Button 2 read state

void setup() {
  Serial.begin(19200);
  // Set Pin Modes
  pinMode(Button1, INPUT); // Using internal pull-up resistors
  pinMode(Button2, INPUT); // Using internal pull-up resistors

}

void loop() {

  Serial.println(digitalRead(Button1));
  Serial.println(digitalRead(Button2));
  delay(100);
 
}




