#ifndef _BlueTooth_H_
#define _BlueTooth_H_

#include "Arduino.h"

class BlueToothSerial : public Stream{
  public:
  BlueToothSerial(byte ATPin, Stream* serialPort);
  void setup(int baund, char* name, char* secrectPin);

  virtual unsigned int write(byte data);
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();
 
  void sendCommand(char* command);
  
  private:
  Stream* stream;
  byte atPin; 
};

#endif
