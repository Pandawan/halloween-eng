/**
 * PROJECT CORNDOG
 * It's not a fruit.
 */

// Motion Sensor (PIR) pin
int motionSensorPin = 2;
// Value read from Motion Sensor (PIR) [LOW/HIGH]
int motionSensorValue = LOW;
 
void setup() {
  // Declare Motion Sensor Pin as an Input
  pinMode(motionSensorPin, INPUT);
  
  Serial.begin(9600);
}
 
void loop(){
  motionSensorValue = digitalRead(motionSensorPin);
  Serial.print("Variable: ");
  Serial.println(motionSensorValue);
}
