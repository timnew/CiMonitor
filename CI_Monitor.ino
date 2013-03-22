#include "RGB_Led.h"

byte busyLed = 2;
RGBLed led(3, 5, 6);
RGB value = RGB(0);

void setup() {
  value = Black;
  led.setColor(value);
  
  pinMode(busyLed, OUTPUT);
  
  Serial.begin(9600); 
  Serial.println("Color: ");
  
  for(byte i = 0; i < 8; i++) {
    digitalWrite(busyLed, (i % 2 == 0 ? HIGH : LOW));
    delay(100);
  }
}

void loop() {
  if(Serial.available()) {
    digitalWrite(busyLed, HIGH);
    value = (RGB)Serial.parseInt();
    led.setColor(value);
    Serial.println(led.getColor());
    Serial.println("Color: ");
  }
  delay(10);
  digitalWrite(busyLed, LOW);
}

