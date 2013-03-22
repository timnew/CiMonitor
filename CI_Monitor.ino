#include "RGB_Led.h"

byte busyLed = 2;
RGBLed led(11, 10, 9);

void setup() {
  led.setColor(0);
  
  pinMode(busyLed, OUTPUT);
  
  Serial.begin(9600); 
  Serial.println("Color: A,R,G,B");
  
  for(byte i = 0; i < 8; i++) {
    digitalWrite(busyLed, (i % 2 == 0 ? HIGH: LOW));
    delay(100);
  }
}

void loop() {
  if(Serial.available()) {
    digitalWrite(busyLed, HIGH);

    Serial.print("Read Color: #");    
    
    char values[4];   
    for(byte i = 0; i < 4 ; i++) {
      values[i] = (byte) Serial.parseInt();
      Serial.print(values[i], HEX);
      if(i < 3) {
        Serial.find(",");
      }
    }
    
    long longValue = *((long*) values);
    led.setColor(longValue);
    
    Serial.println(led.getColor(), HEX);
    Serial.println("Color: A,R,G,B");
  }
  delay(10);
  digitalWrite(busyLed, LOW);
}

