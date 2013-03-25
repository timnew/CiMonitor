#ifndef _RGBLed_H_
#define _RGBLed_H_

#include "Arduino.h"

typedef unsigned long ColorValue;

class RGBLed {
  public:
  RGBLed(byte redPin, byte greenPin, byte bluePin);
  void setColor(byte* rgb);
  void setColor(byte r, byte g, byte b);
  void setColor(ColorValue value);
  byte* getColor();
  ColorValue getColorValue();
  
  private:
  void refresh();
  byte pins[3];
  byte currentColor[3];
  byte __protector; // Used for over boundary protection;
};

#endif