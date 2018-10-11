/**
 * PROJECT CORNDOG
 * It's not a fruit.
 */

// Motion Sensor (PIR) pin
int motionSensorPin = 2;
// Value read from Motion Sensor (PIR) [LOW/HIGH]
int motionSensorValue = LOW;
int previousSensorValue = LOW;

// TODO: Maybe add a system so that you can launch it only once and you have to do a specific step to reset it

 
void setup() {
  // Declare Motion Sensor Pin as an Input
  pinMode(motionSensorPin, INPUT);
  
  Serial.begin(9600);
}
 
void loop(){
  // Refresh the Motion Sensor Value
  motionSensorValue = digitalRead(motionSensorPin);
  // If it switched from LOW to HIGH
  if (motionSensorValue == HIGH && previousSensorValue == LOW) {
    // Launch the facehugger
    launch();
  }
  // Set the previous value
  previousSensorValue = motionSensorValue;
}

void launch() {
  // TODO: Make launching system using motor
  Serial.println("Launch facehugger!");
}
