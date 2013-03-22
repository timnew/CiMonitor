#include "RGB_Led.h"

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin) {
  pins[0] = redPin;  
  pins[1] = greenPin;
  pins[2] = bluePin;
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void RGBLed::setColor(ARGB newValue) {
  char *elements = (char*)(&newValue);
  
  Serial.print("#");
  for(byte i = 0 ; i < 3; i++) {
    byte pin = pins[i];
    byte value = *(elements + i + 1);
    Serial.print(value, HEX);
    analogWrite(pin, 255 - value);
  }
  Serial.println();
}
 
ARGB RGBLed::getColor() {
  return current;
}
