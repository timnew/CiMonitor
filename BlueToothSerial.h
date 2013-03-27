#ifndef _BlueTooth_H_
#define _BlueTooth_H_

#include "Arduino.h"

#ifndef sbyte
  typedef signed char sbyte;
#endif

class BlueToothSerial : public Stream{
  public:
  BlueToothSerial(byte ATPin, Stream* serialPort);
  
  void beginSetup(sbyte retryTimes = 3);

  boolean setupEcho(sbyte retryTimes = -1); // AT
  boolean setupBaund(int baund, sbyte retryTimes = -1); // AT+UART
  boolean setupRole(byte role, sbyte retryTimes = -1); // AT+ROLE
  boolean setupName(String name, sbyte retryTimes = -1); // AT+NAME
  boolean setupSecret(String secretPin, sbyte retryTimes = -1); // AT+PSWD
  boolean setupRemoveParis(sbyte retryTimes = -1); // AT+RMAAD

  void setupPrint(String output);
  void setupPrintln();
  void setupPrintln(String output);
  void setupPrintln(String label, String value);
  void setupPrintln(String label, int index, String value);

  String endSetup();

  virtual unsigned int write(byte data);
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();
 
  boolean sendCommand(char* command, sbyte retryTimes = -1);
  boolean sendCommand(String command, sbyte retryTimes = -1);

  
  private:
  String setupResult;
  byte retry;
  Stream* stream;
  byte atPin; 
};

#endif
