#include <Arduino.h>
#include "BluetoothA2DPSink.h"

// Pin Tanımlamaları
const int sensorPin = 13;
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

// Değişkenler
int currentState = 1;
bool colorCycleActive = false;
bool musicSyncMode = false;
unsigned long pressStartTime = 0;
bool longPressActive = false;
bool lastSensorState = false; // Eksik değişken eklendi

// Renk Döngüsü
int hue = 0;
const int hueStep = 2;
unsigned long previousHueUpdate = 0;
const long hueInterval = 15;

// Bluetooth
BluetoothA2DPSink a2dp_sink;
bool btConnected = false;
bool isMusicPlaying = false;

// HSV-RGB Dönüşümü
struct RGBColor { int r; int g; int b; };
RGBColor hueToRGB(int hue) {
  hue %= 255;
  if(hue < 85) {
    return {255 - hue*3, hue*3, 255};
  } else if(hue < 170) {
    hue -= 85;
    return {255, 255 - hue*3, hue*3};
  } else {
    hue -= 170;
    return {hue*3, 255, 255 - hue*3};
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Bluetooth Başlatma (Güncellenmiş Yöntem)
  a2dp_sink.start("SmartLEDSpeaker");
}

void loop() {
  bool sensorState = digitalRead(sensorPin);
  
  // Uzun Basış Kontrolü
  if(sensorState && !longPressActive) {
    if(!lastSensorState) pressStartTime = millis();
    if(millis() - pressStartTime > 3000) {
      toggleMusicSyncMode();
      longPressActive = true;
    }
  } else if(!sensorState) {
    longPressActive = false;
  }

  // Kısa Basış Kontrolü
  if(sensorState && !lastSensorState && !longPressActive) {
    currentState = (currentState % 13) + 1;
    colorCycleActive = (currentState == 13);
    setColor(currentState);
    delay(300);
  }
  lastSensorState = sensorState;

  // Bluetooth Durumu
  btConnected = a2dp_sink.is_connected();
  isMusicPlaying = btConnected;

  // Renk Kontrolü
  if(colorCycleActive) {
    updateColorCycle();
  }
  
  delay(50);
}

void updateColorCycle() {
  if(millis() - previousHueUpdate >= hueInterval) {
    previousHueUpdate = millis();
    RGBColor color = hueToRGB(hue);
    analogWrite(redPin, color.r);
    analogWrite(greenPin, color.g);
    analogWrite(bluePin, color.b);
    hue = (hue + hueStep) % 255;
  }
}

void toggleMusicSyncMode() {
  if(isMusicPlaying) {
    musicSyncMode = !musicSyncMode;
    Serial.println(musicSyncMode ? "Müzik Modu Aktif" : "Normal Mod");
  }
}

void setColor(int state) {
  switch(state) {
    case 1: // Beyaz
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("White");
      break;
    case 2: // Kırmızı
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      Serial.println("Red");
      break;
    case 3: // Yeşil
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      Serial.println("Green");
      break;
    case 4: // Mavi
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      Serial.println("Blue");
      break;
    // Diğer case'ler aynı kalacak
    case 13:
      colorCycleActive = true;
      Serial.println("Renk Döngüsü");
      break;
    default:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
  }
}