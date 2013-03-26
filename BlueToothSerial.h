#ifndef _BlueTooth_H_
#define _BlueTooth_H_

#include "Arduino.h"

class BlueToothSerial : public Stream{
  public:
  BlueToothSerial(byte ATPin, Stream* serialPort);
  
  void beginSetup(byte retry);

  boolean setupEcho(); // AT
  boolean setupBaund(int baund); // AT+UART
  boolean setupRole(byte role); // AT+ROLE
  boolean setupName(String name); // AT+NAME
  boolean setupSecret(String secretPin); // AT+PSWD
  boolean setupRemoveParis(); // AT+RMAAD

  void setup(int baund, char* name, char* secrectPin);
  String endSetup();

  virtual unsigned int write(byte data);
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();
 
  boolean sendCommand(char* command);
  boolean sendCommand(String command);

  private:
  String setupResult;
  byte retry;
  Stream* stream;
  byte atPin; 
};

#endif
