#include "RGB_Led.h"

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin) {
  pins[0] = bluePin;
  pins[1] = greenPin;
  pins[2] = redPin;  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void RGBLed::setColor(RGB newValue) {
  newValue = (RGB)(newValue &  0x07);
  current = newValue;
  for(byte i = 0 ; i < 3; i++) {
    Serial.print(pins[i]);
    Serial.print(":");
     
    if(newValue & 0x01) {
      digitalWrite(pins[i], HIGH);
      Serial.print("1");
    }
    else {
      digitalWrite(pins[i], LOW);
      Serial.print("0");
    }
    Serial.print(", ");
    newValue = (RGB)(newValue >> 1);
  }
  Serial.println();
}
 
RGB RGBLed::getColor() {
  return current;
}
