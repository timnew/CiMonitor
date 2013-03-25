#include "RGBLed.h"

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin) {
  pins[0] = redPin;  
  pins[1] = greenPin;
  pins[2] = bluePin;

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  setColor(0, 0, 0);
  __protector == 0;
}

void RGBLed::setColor(byte r, byte g, byte b) {
  currentColor[0] = r;
  currentColor[1] = g;
  currentColor[2] = b;  

  refresh();
}

void RGBLed::setColor(byte* rgb) {
  setColor(rgb[0], rgb[1], rgb[2]);
}

void RGBLed::setColor(ColorValue value) {
  setColor((byte*)&value);
}

void RGBLed::refresh() {
  byte i;
  byte* pin = pins;
  byte* color = currentColor;
  for(i = 0; i < 3; i++, pin++, color++) {
    analogWrite(*pin, 255 - *color);
  }
}
 
byte* RGBLed::getColor() {
  return currentColor;
}

ColorValue RGBLed::getColorValue() {
  return *((ColorValue *)(currentColor));
}
