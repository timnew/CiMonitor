#ifndef _RGB_Led_h
#define _RGB_Led_h

#include "Arduino.h"

enum RGB {
  Black = 0x00,
  Red = 0x04,
  Green = 0x02,
  Blue = 0x01
};

class RGBLed {
  public:
  RGBLed(byte redPin, byte greenPin, byte bluePin);
  void setColor(RGB newValue);
  RGB getColor();
  
  private:
  RGB current;
  byte pins[3];
};

#endif
