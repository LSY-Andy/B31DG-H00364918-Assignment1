#define GREEN_LED_PIN 21    
#define YELLOW_LED_PIN 15   


void setup() {

  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT); 
  pinMode(YELLOW_LED_PIN, OUTPUT); 
}

void loop() {
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(500); 
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(50); 

  Serial.println("Green");


  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(50);
  digitalWrite(YELLOW_LED_PIN, LOW);
  delay(500); 

  Serial.println("Red");
}
