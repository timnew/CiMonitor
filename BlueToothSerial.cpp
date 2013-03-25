#include "BlueToothSerial.h"

unsigned int BlueToothSerial::write(byte data) {
  return stream->write(data);
}

int BlueToothSerial::available() {
  return stream->available();
}

int BlueToothSerial::read() {
  return stream->read();
}

int BlueToothSerial::peek() {
  return stream->peek();
}

void BlueToothSerial::flush() {
  return stream->flush();
}

BlueToothSerial::BlueToothSerial(byte ATPin, Stream* serialPort) {
  atPin = ATPin;
  stream = serialPort;
}

void BlueToothSerial::setup(int baund, char* name, char* secretPin) {
  digitalWrite(atPin, HIGH);
    
   stream->println("AT");
   delay(100);
  
   stream->print("AT+NAME=");
   stream->println(name); 
   delay(100);
  
   stream->print("AT+ROLE="); 
   stream->println("0");
   delay(100);
  
   stream->print("AT+PSWD="); 
   stream->println(secretPin);
   delay(100);
  
   stream->print("AT+UART=");
   stream->print(baund, DEC);
   stream->println(",0,0"); 
   delay(100);
  
   digitalWrite(atPin, LOW);
}

void BlueToothSerial::sendCommand(char* command) {
  digitalWrite(atPin, HIGH);
  stream->println(command);
  delay(100);
  digitalWrite(atPin, LOW);
}


