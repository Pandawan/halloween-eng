#include <Servo.h>

/**
   PROJECT CORNDOG v2.0
   IT'S STILL NOT A FRUIT.
*/


/* Motion Sensor */
const int motionSensorPin = 6;
// Value read from Motion Sensor (PIR) [LOW/HIGH]
int motionSensorValue = LOW;
// Previous value from Motion Sensor
int previousMotionSensorValue = LOW;


/* Ready Light */
const int readyLightRedPin = 9;
const int readyLightGreenPin = 10;
const int readyLightBluePin = 11;
// Number between 0 and 255 for brightness of the ready light
const int readyLightBrightness = 255;

/* Reset Button */
// Pin for the Reset Button
const int resetButtonPin = 4;
// Current value of the Reset Button
int resetButtonValue = LOW;

/* Servo Motor */
Servo servoMotor;
int servoMotorPin = 3;

/* Extra Variables */
// Whether or not the system is ready to be launched
int readyForLaunch = LOW;


void setup() {

  Serial.begin(9600);
  printMessage("Initializing...", true);

  // Declare Motion Sensor Pin as an Input
  pinMode(motionSensorPin, INPUT);

  // Declare Button as an Input
  pinMode(resetButtonPin, INPUT);

  // Declare Ready Red Pin as an Output
  pinMode(readyLightRedPin, OUTPUT);
  // Declare Ready Green Pin as an Output
  pinMode(readyLightGreenPin, OUTPUT);
  // Declare Ready Blue Pin as an Output
  pinMode(readyLightBluePin, OUTPUT);

  // Declare Servo's Motor Pin as Servo
  servoMotor.attach(servoMotorPin);

  reset();

  printMessage("Done initializing.", true);
}

void loop() {
  /* Motion Sensor Sequence */
  // Motion Sensor needs to run before reset button so that the servo motor doesn't run while pressing reset button
  motionSensorValue = digitalRead(motionSensorPin);


  /* Reset Button Sequence */
  // Read reset button's value
  resetButtonValue = digitalRead(resetButtonPin);

  // If press the reset button AND it wasn't already reset AND the motion sensor is not seeing anything, reset it now.
  // Don't want it to get auto-activated upon pressing the button if it already sees motion
  if (resetButtonValue == HIGH && readyForLaunch == LOW && motionSensorValue == LOW) {
    reset();
  }


  /* Ready Light Sequence */  
  // Ready For Launch
  if (readyForLaunch == HIGH) {
    // Ready Light Green
    setReadyLightColor(0, readyLightBrightness, 0);
  }
  // Not Ready for Launch
  else if (readyForLaunch == LOW) {
    // Ready Light Red
    setReadyLightColor(readyLightBrightness, 0, 0);
  }


  /* Launching Sequence */
  // If it's ready and it sees movement
  if (readyForLaunch == HIGH && motionSensorValue == HIGH) {
    launch();
  }


  /* End Sequence */
  previousMotionSensorValue = motionSensorValue;
}

void reset() {
  printMessage("Resetting.", true);
  readyForLaunch = HIGH;
  servoMotor.write(0);
  delay(1000);
  readyForLaunch = HIGH;
  printMessage("Done resetting.", true);
}

void launch() {
  printMessage("Launching.", true);
  readyForLaunch = LOW;
  // TODO: Make launching sequence
  servoMotor.write(180);
  delay(1000);
  readyForLaunch = LOW;
  printMessage("Done launching.", true);
}


/*
   HELPER METHODS
*/

// Print Message Utility
void printMessage(char* stringToPrint, bool newLine) {
  Serial.print(millis());
  Serial.print(" ");
  if (newLine) {
    Serial.println(stringToPrint);
  }
  else {
    Serial.print(stringToPrint);
  }
}

// Print Message Utility
void printMessage(int numberToPrint, bool newLine) {
  Serial.print(millis());
  Serial.print(" ");
  if (newLine) {
    Serial.println(numberToPrint);
  }
  else {
    Serial.print(numberToPrint);
  }
}

// Set Ready Light's Color Utility
void setReadyLightColor(int red, int green, int blue)
{
  printMessage(red, true);
  analogWrite(readyLightRedPin, red);
  analogWrite(readyLightGreenPin, green);
  analogWrite(readyLightBluePin, blue);
}
