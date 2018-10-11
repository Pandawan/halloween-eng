/**
   PROJECT CORNDOG
   It's not a fruit.
*/

// Motion Sensor (PIR) pin
int motionSensorPin = 2;
// Value read from Motion Sensor (PIR) [LOW/HIGH]
int motionSensorValue = LOW;
// Previous value from Motion Sensor
int previousSensorValue = LOW;

// Ready Button pin
int readyButtonPin = 4;
// Value read from Ready Button
int readyButtonValue = LOW;
// Whether or not it is ready for next launch
int readyForLaunch = LOW;

// Status Light pin
int statusLightPinRed = 9;
int statusLightPinGreen = 10;
int statusLightPinBlue = 11;

void setup() {
  // Declare Motion Sensor Pin as an Input
  pinMode(motionSensorPin, INPUT);
  
  // Declare Button as an Input
  pinMode(readyButtonPin, INPUT);

  // Declare Status Light as Output
  pinMode(statusLightPinRed, OUTPUT);
  pinMode(statusLightPinGreen, OUTPUT);
  pinMode(statusLightPinBlue, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  readyStateRefresh();
  statusLightRefresh();
  motionSensorRefresh();
}

// Refrehs the motion sensor's value and do launch system
void motionSensorRefresh() {
  // Refresh the Motion Sensor Value
  motionSensorValue = digitalRead(motionSensorPin);
  // If it is ready for launch
  if (readyForLaunch == HIGH) {
    // If it switched from LOW to HIGH
    if (motionSensorValue == HIGH && previousSensorValue == LOW) {
      // Launch the facehugger
      launch();
    }
  }
  // Set the previous value
  previousSensorValue = motionSensorValue;
}

// Ready State controlled by a button
void readyStateRefresh() {
  readyButtonValue = digitalRead(readyButtonPin);

  if (readyButtonValue == HIGH) {
    readyForLaunch = HIGH;
  }
}

void statusLightRefresh() {
  if (readyForLaunch == LOW) {
    setColor(statusLightPinRed, 255, statusLightPinGreen, 0, statusLightPinBlue, 0);
  }
  else if (readyForLaunch == HIGH) {
    setColor(statusLightPinRed, 0, statusLightPinGreen, 255, statusLightPinBlue, 0);
  }
}

void launch() {
  // TODO: Make launching system using motor
  Serial.println("Launch facehugger!");
  readyForLaunch = LOW;
}

// Set Color Utility
void setColor(int redPin, int red, int greenPin, int green, int bluePin, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
