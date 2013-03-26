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

  updateLed();
}

void RGBLed::setColor(byte* rgb) {
  setColor(rgb[0], rgb[1], rgb[2]);
}

void RGBLed::setColor(ColorValue value) {
  setColor((byte*)&value);
}

void RGBLed::updateLed(byte* rgb) {
  byte i;
  byte* pin = pins;
  byte* color = rgb;
  for(i = 0; i < 3; i++, pin++, color++) {
    analogWrite(*pin, 255 - *color);
  }
}

void RGBLed::updateLed() {
  updateLed(currentColor);
}


void RGBLed::blink(int duration, int times, ColorValue value) {
  ColorValue black = 0;
  int halfDuration = duration >> 1;
  int doubleTimes = times << 2;
  
  for(int i = 0 ; i < doubleTimes; i++ ) {
    if(i & 0x01) {
      updateLed((byte*)&value);
    }
    else {
      updateLed((byte*)&black); 
    }
    delay(halfDuration);
  }
  updateLed();
}
 
byte* RGBLed::getColor() {
  return currentColor;
}

ColorValue RGBLed::getColorValue() {
  return *((ColorValue *)(currentColor));
}
