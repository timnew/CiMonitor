#include "RGBLed.h"
#include "BlueToothSerial.h"

#define BLUETOOTH true

RGBLed led(11, 10, 9);
BlueToothSerial BTSerial = BlueToothSerial(2, &Serial);

void setup() {
  led.setColor(0, 0, 0);
  led.blink(100, 2, 0xFFFFFFL);
  Serial.begin(9600);
  
#if BLUETOOTH  
  BTSerial.beginSetup(3);
  
  BTSerial.setupEcho();
  BTSerial.setupBaund(9600);
  BTSerial.setupRole(0);
  BTSerial.setupName("TimNew-CI-Lamp");
  BTSerial.setupSecret("4884");
  
  String result = BTSerial.endSetup();
  
  BTSerial.println(result);
  
#endif

  led.blink(100, 4, 0xFFFFFFL);
  
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
    else {
      BTSerial.print("Unknown command: ");
      BTSerial.println(command);
    }
  }
}

