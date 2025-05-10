#include <LiquidCrystal.h>
#include <Servo.h>

const int potentiometerPin = A0; 
const int ledPin = 13; 
const int threshold = 70; 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo injector;

void setup() {
  pinMode(ledPin, OUTPUT); 
  lcd.begin(16, 2); 
  lcd.print("Glucose Level: ");
  injector.attach(9); 
}

void loop() {
  int sensorValue = analogRead(potentiometerPin);
  int glucoseLevel = map(sensorValue, 0, 1023, 0, 150);
  Serial.begin(9600);  
  Serial.println(sensorValue);  
  lcd.setCursor(0, 1); 
  lcd.print("      "); 
  lcd.print(glucoseLevel);
  lcd.print(" mg/dL");
  if (glucoseLevel < threshold) {
    digitalWrite(ledPin, HIGH);
     delay(2000); 
    injector.write(90); // Move servo to inject
    delay(5000);
    injector.write(0);
   
  } else {
    digitalWrite(ledPin, LOW); 
  }
  delay(500); 
}
