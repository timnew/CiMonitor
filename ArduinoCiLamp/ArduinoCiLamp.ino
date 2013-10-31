#include "RGBLed.h"
#include "BlueToothSerial.h"

//#define BLUETOOTH 
#define IRREMOTE

//#define RGBLED
#define RBGLED

#define RedPin 11
#define GreenPin 10
#define BluePin 9

#if defined RGBLED
RGBLed led(RedPin, GreenPin, BluePin);
#elif defined RBGLED
RGBLed led(RedPin, BluePin, GreenPin);
#endif

#ifdef IRREMOTE
#include "IRremote.h"
#include "IRremoteInt.h"
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
  led.setColor(0, 0, 0);
  led.blink(0xFFFFFFL, 2);
  Serial.begin(9600);
  
  bool succeeded = true;
  
#ifdef BLUETOOTH  
  BTSerial.beginSetup(3);
 
  if(BTSerial.setupEcho(6)) { // Bluetooth board if found

    led.blink(0xFF0000L, 3);
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

  if(succeeded) {
    led.blink(0x00FF00L, 4);
  }
  else {
    led.blink(0x0000FFL, 4);
  }

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
    else if(command == "LED+COLOR") {
      byte values[3];   
      BTSerial.readBytes((char*) values, 3);
      led.setColor((byte*)values);
      BTSerial.print("LED+Color=[");
      BTSerial.print(values[0], DEC);
      BTSerial.write(',');
      BTSerial.print(values[1], DEC);
      BTSerial.write(',');
      BTSerial.print(values[2], DEC);
      BTSerial.println("]");
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


