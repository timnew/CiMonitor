#include "RGBLed.h"
#include "BlueToothSerial.h"

//#define BLUETOOTH 

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

BlueToothSerial BTSerial = BlueToothSerial(2, &Serial);

void setup() {
  led.setColor(0, 0, 0);
  led.blink(0xFFFFFFL, 2);
  Serial.begin(9600);
  
  bool succeeded = true;
  
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
    
  }
}


