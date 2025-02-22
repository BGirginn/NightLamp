#include <Arduino.h>

// Pin tanımlamaları
const int sensorPin = 13;      // Dokunma sensörü pini
const int redPin    = 25;      // Kırmızı LED pini
const int greenPin  = 26;      // Yeşil LED pini
const int bluePin   = 27;      // Mavi LED pini

// Renk döngüsü için yeni değişkenler
bool colorCycleActive = false; // Renk döngü modu aktif mi?
int hue = 0;                  // Renk açısı (0-255)
const int hueStep = 2;        // Renk değişim hızı
unsigned long previousHueUpdate = 0;
const long hueInterval = 15;  // Renk güncelleme aralığı (ms)

int currentState = 1;          // Başlangıç modu
bool lastSensorState = false;  // Sensörün önceki durumu

// HSV'den RGB'ye dönüşüm fonksiyonu (Ortak anot için ayarlı)
struct RGBColor { int r; int g; int b; };
RGBColor hueToRGB(int hue) {
  hue %= 255;
  int r, g, b;
  
  if(hue < 85) {
    r = 255 - hue * 3;
    g = hue * 3;
    b = 0;
  } 
  else if(hue < 170) {
    hue -= 85;
    r = 0;
    g = 255 - hue * 3;
    b = hue * 3;
  } 
  else {
    hue -= 170;
    r = hue * 3;
    g = 0;
    b = 255 - hue * 3;
  }
  
  // Ortak anot için renkleri ters çevir
  return {255 - r, 255 - g, 255 - b};
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setColor(currentState);
}

void loop() {
  bool sensorState = digitalRead(sensorPin);
  
  // Dokunma algılandığında
  if(sensorState && !lastSensorState) {
    currentState++;
    
    if(currentState > 13) { // 13 durumlu yeni sistem
      currentState = 1;
    }
    
    // Renk döngü modunu sıfırla
    colorCycleActive = false;
    setColor(currentState);
    delay(300); // Debounce
  }
  lastSensorState = sensorState;

  // Renk döngü modu aktifse
  if(colorCycleActive) {
    unsigned long currentMillis = millis();
    if(currentMillis - previousHueUpdate >= hueInterval) {
      previousHueUpdate = currentMillis;
      
      RGBColor color = hueToRGB(hue);
      analogWrite(redPin, color.r);
      analogWrite(greenPin, color.g);
      analogWrite(bluePin, color.b);
      
      hue = (hue + hueStep) % 255;
    }
  }
  
  delay(50);
}

void setColor(int state) {
  switch(state) {
    // Orijinal 12 durum aynı kaldı
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
    case 5: // Sarı
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      Serial.println("Yellow");
      break;
    case 6: // Camgöbeği
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("Cyan");
      break;
    case 7: // Macenta
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      Serial.println("Magenta");
      break;
    case 8: // Pembe
      analogWrite(redPin, 0);
      analogWrite(greenPin, 150);
      analogWrite(bluePin, 75);
      Serial.println("Pink");
      break;
    case 9: // Turuncu
      analogWrite(redPin, 0);
      analogWrite(greenPin, 90);
      analogWrite(bluePin, 255);
      Serial.println("Orange");
      break;
    case 10: // Mor
      analogWrite(redPin, 55);
      analogWrite(greenPin, 155);
      analogWrite(bluePin, 55);
      Serial.println("Purple");
      break;
    case 11: // Açık Mavi
      analogWrite(redPin, 82);
      analogWrite(greenPin, 39);
      analogWrite(bluePin, 25);
      Serial.println("Light Blue");
      break;
    case 12: // Altın Sarısı
      analogWrite(redPin, 0);
      analogWrite(greenPin, 40);
      analogWrite(bluePin, 255);
      Serial.println("Gold Yellow");
      break;
      
    // Yeni renk döngü modu
    case 13:
      colorCycleActive = true;
      Serial.println("Color Cycle Mode");
      break;
      
    default:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      Serial.println("Default: White");
      break;
  }
}