#include "RGBLed.h"
#include "BlueToothSerial.h"

RGBLed led(11, 10, 9);
BlueToothSerial BTSerial = BlueToothSerial(2, &Serial);

void setup() {
  led.setColor(0, 0, 0);
  Serial.begin(9600);
  BTSerial.setup(9600, "TimNew's CI Monitor", "4884");  

  BTSerial.println("CT+Ready");
}

void loop() {
  if(BTSerial.available()) {
    char values[3];   
    BTSerial.readBytes(values, 3);

    led.setColor((byte*)values);
    
    BTSerial.println(led.getColorValue(), HEX);
  }
}

