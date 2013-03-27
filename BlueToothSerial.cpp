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

void BlueToothSerial::beginSetup(sbyte retryTimes) {
  digitalWrite(atPin, HIGH);
  this->retry = retryTimes;
  setupResult = "\r\n== BlueTooth Setup ==\r\n\r\n";
}

void BlueToothSerial::setupPrint(String output) { setupResult += output; }
void BlueToothSerial::setupPrintln() { setupResult += "\r\n"; }
void BlueToothSerial::setupPrintln(String output) { 
  setupPrint(output);
  setupPrintln(); 
}
void BlueToothSerial::setupPrintln(String label, String value) {
  setupPrint(label);
  setupPrint(": ");
  setupPrint(value);
  setupPrintln();
}
void BlueToothSerial::setupPrintln(String label, int index, String value) {
  setupPrint(label);
  setupPrint("[");
  setupPrint(String(index, DEC));
  setupPrint("]: ");
  setupPrint(value);
  setupPrintln();
}


String BlueToothSerial::endSetup() {
  setupPrint("\r\n\r\n== BlueTooth Setup End ==\r\n");
  digitalWrite(atPin, LOW);
  return setupResult;
}

boolean BlueToothSerial::setupEcho(sbyte retryTimes) { return sendCommand("AT", retryTimes); }
boolean BlueToothSerial::setupBaund(int baund, sbyte retryTimes) { return sendCommand("AT+UART=" + String(baund, DEC) + ",0,0", retryTimes); }
boolean BlueToothSerial::setupRole(byte role, sbyte retryTimes) { return sendCommand("AT+ROLE=" + String(role, DEC), retryTimes); }
boolean BlueToothSerial::setupName(String name, sbyte retryTimes) { return sendCommand("AT+NAME=" + String(name), retryTimes); }
boolean BlueToothSerial::setupSecret(String secretPin, sbyte retryTimes) { return sendCommand("AT+PSWD=" + String(secretPin), retryTimes); }
boolean BlueToothSerial::setupRemoveParis(sbyte retryTimes) { return sendCommand("AT+RMAAD", retryTimes); }

boolean BlueToothSerial::sendCommand(char* command, sbyte retryTimes) {
  return sendCommand(String(command), retryTimes);
}

boolean BlueToothSerial::sendCommand(String command, sbyte retryTimes) {
  byte times;
  if(retryTimes == -1)
    retryTimes = retry;

    setupPrintln("Command", command);
  
  for(times = 0; times < retryTimes; times ++) {    
    stream->println(command); 
    stream->flush();
   
    String result = stream->readStringUntil('\n');
    if(result=="")
      result = "<TimeOut>";
      
    setupPrintln("Result", times, result);
    result.trim();
    if( result == "OK") {
      break;
    }
  }
  
  if(times == retryTimes) {
    setupPrint("Result: Failed\r\n\r\n");
    return false;
  }
  else {
    setupPrint("Result: Succeeded\r\n\r\n");
    return true;
  }
}



