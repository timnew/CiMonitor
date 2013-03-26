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
  pinMode(atPin, OUTPUT);
  stream = serialPort;
  
  while(stream->available()) {
    stream->read();
  }
}

void BlueToothSerial::beginSetup(byte retryTimes = 0) {
  digitalWrite(atPin, HIGH);
  this->retry = retryTimes;
  setupResult = "\r\n== BlueTooth Setup ==\r\n";
}

String BlueToothSerial::endSetup() {
  digitalWrite(atPin, LOW);
  return setupResult;
}

boolean BlueToothSerial::setupEcho() { return sendCommand("AT"); }
boolean BlueToothSerial::setupBaund(int baund) { return sendCommand("AT+UART=" + String(baund, DEC) + ",0,0"); }
boolean BlueToothSerial::setupRole(byte role) { return sendCommand("AT+ROLE=" + String(role, DEC)); }
boolean BlueToothSerial::setupName(String name) { return sendCommand("AT+NAME=" + String(name)); }
boolean BlueToothSerial::setupSecret(String secretPin) { return sendCommand("AT+PSWD=" + String(secretPin)); }
boolean BlueToothSerial::setupRemoveParis() { return sendCommand("AT+RMAAD"); }

boolean BlueToothSerial::sendCommand(char* command) {
  return sendCommand(String(command));
}

boolean BlueToothSerial::sendCommand(String command) {
  byte times;
  
  for(times = 0; times < retry; times ++) {
    setupResult += "Sent: ";
    setupResult += command;
    setupResult += "\r\n";
    
    stream->println(command); 
    stream->flush();
   
    String result = stream->readStringUntil('\n');
    
    setupResult += "Result: ";
    setupResult += result;
    setupResult += "\r\n";
    result.trim();
    if( result == "OK") {
      break;
    }
  }
  
  if(times == retry) {
    setupResult += "ERROR: Command Failed\r\n\r\n";
    return false;
  }
  else {
    setupResult += "SUCCEEDED\r\n\r\n";
    return true;
  }
}




