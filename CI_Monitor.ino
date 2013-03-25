#include "RGB_Led.h"

#define AT 2

RGBLed led(11, 10, 9);

void setupBlueTooth() {
   pinMode(AT, OUTPUT);
   
   digitalWrite(AT, HIGH);
  
   Serial.begin(9600); 
   delay(100);
  
   Serial.println("AT");
   delay(100);
  
   Serial.println("AT+NAME=OPENJUMPER-Bluetooth"); 
   delay(100);
  
   Serial.println("AT+ROLE=0"); 
   delay(100);
  
   Serial.println("AT+PSWD=1234"); 
   delay(100);
  
   Serial.println("AT+UART=9600,0,0"); 
   delay(100);
  
   digitalWrite(AT, LOW);
 }

void setup() {
  led.setColor(0, 0, 0);
  setupBlueTooth();
  Serial.begin(9600); 

  Serial.println("CT+Ready");
}

void loop() {
  if(Serial.available()) {
    char values[3];   
    Serial.readBytes(values, 3);

    led.setColor((byte*)values);
    
    Serial.println(led.getColorValue(), HEX);
  }
}

