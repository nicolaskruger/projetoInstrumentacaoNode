#include <Arduino.h>
#define LED D0
bool b=false;
void setup() {
  pinMode(LED,OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  b=!b;
  digitalWrite(LED, b);
  delay(1000);
  // put your main code here, to run repeatedly:
}