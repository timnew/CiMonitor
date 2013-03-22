#ifndef _RGB_Led_h
#define _RGB_Led_h

#include "Arduino.h"

#define ARGB long

class RGBLed {
  public:
  RGBLed(byte redPin, byte greenPin, byte bluePin);
  void setColor(ARGB newValue);
  ARGB getColor();
  
  private:
  ARGB current;
  byte pins[3];
};

#endif
