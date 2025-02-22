#include <Arduino.h>

// Pin definitions
const int sensorPin = 13;      // Touch sensor pin
const int redPin    = 25;      // Red LED pin
const int greenPin  = 26;      // Green LED pin
const int bluePin   = 27;      // Blue LED pin

int currentState = 1;          // Color mode starting state
bool lastSensorState = false;  // Previous state of the touch sensor

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set initial color
  setColor(currentState);
}

void loop() {
  bool sensorState = digitalRead(sensorPin);
  // If the touch sensor is pressed (HIGH and previously LOW)
  if(sensorState && !lastSensorState) {
    currentState++;                 // Increment the color state
    if(currentState > 12) {         // Loop back to 1 after 12
      currentState = 1;
    }
    setColor(currentState);         // Change to the new color
    delay(300);                     // Debounce delay
  }
  lastSensorState = sensorState;
  delay(50);  // Loop delay
}

void setColor(int state) {
  switch(state) {
    case 1: // White
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("White");
      break;
    case 2: // Red
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      Serial.println("Red");
      break;
    case 3: // Green
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      Serial.println("Green");
      break;
    case 4: // Blue
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      Serial.println("Blue");
      break;
    case 5: // Yellow (Red + Green)
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      Serial.println("Yellow");
      break;
    case 6: // Cyan (Green + Blue)
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("Cyan");
      break;
    case 7: // Magenta (Red + Blue)
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      Serial.println("Magenta");
      break;
    case 8: // Pink (Red, low Green, medium Blue)
      analogWrite(redPin, 0);
      analogWrite(greenPin, 150);
      analogWrite(bluePin, 75);
      Serial.println("Pink");
      break;
    case 9: // Orange (Red, medium Green, no Blue)
      analogWrite(redPin, 0);
      analogWrite(greenPin, 90);
      analogWrite(bluePin, 255);
      Serial.println("Orange");
      break;
    case 10: // Purple
      analogWrite(redPin, 55);
      analogWrite(greenPin, 155);
      analogWrite(bluePin, 55);
      Serial.println("Purple");
      break;
    case 11: // Light Blue
      analogWrite(redPin, 82);
      analogWrite(greenPin, 39);
      analogWrite(bluePin, 25);
      Serial.println("Light Blue");
      break;
    case 12: // Gold Yellow
      analogWrite(redPin, 0);
      analogWrite(greenPin, 40);
      analogWrite(bluePin, 255);
      Serial.println("Gold Yellow");
      break;
    default:
      // Default to White
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      Serial.println("Default: White");
      break;
  }
}