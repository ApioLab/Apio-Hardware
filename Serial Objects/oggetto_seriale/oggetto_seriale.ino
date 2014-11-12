#include <Arduino.h>

#include "ApioSerial.h"

int led = 13;
void setup() {
  
  pinMode(led, OUTPUT);
  apioSetup();

}

void loop() {
 
  apioReceive();
  select();
  
  if(proprieta=="onoff")
  {
    if(valore=="1")
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      
    if(valore=="0")  
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW

  }
  delay(100);               // wait for a second

  
}

