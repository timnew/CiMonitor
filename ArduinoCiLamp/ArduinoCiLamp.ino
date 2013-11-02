#include "BlueToothSerial.h"

//#define BLUETOOTH 
#define IRREMOTE

#ifdef IRREMOTE
#include "IRremote.h"
#endif

BlueToothSerial BTSerial = BlueToothSerial(2, &Serial);

#ifdef IRREMOTE
IRsend irsend;

void sendCode() {
  unsigned long codeValue;
  int codeLen;
  BTSerial.readBytes((char*)&codeValue, 4);
  BTSerial.readBytes((char*)&codeLen, 2);
  irsend.sendNEC(codeValue, codeLen);
}

#endif

void setup() {
  Serial.begin(9600);
  
  bool succeeded = true;
  
#ifdef BLUETOOTH  
  BTSerial.beginSetup(3);
 
  if(BTSerial.setupEcho(6)) { // Bluetooth board if found
   
    succeeded &= BTSerial.setupBaund(9600);
    succeeded &= BTSerial.setupRole(0);
    succeeded &= BTSerial.setupName("TimNew-CI-Lamp");
    succeeded &= BTSerial.setupSecret("4884");
  }
  else {
    led.last(0x00FFFF);
  }
  
  String result = BTSerial.endSetup();
  
  BTSerial.println(result);
#endif

  BTSerial.println("LED+Ready");
}

void loop() {
  if(BTSerial.available()) {
    String command = BTSerial.readStringUntil(';');
    command.trim();
    command.toUpperCase();
    
    if(command == "LED+CONNECT") {
      BTSerial.println("LED+Ready");
    }
#ifdef IRREMOTE
    else if(command == "LED+IR") {
      sendCode();
    }
#endif
    else {
      BTSerial.print("Unknown command: ");
      BTSerial.println(command);
    }
  }
}


