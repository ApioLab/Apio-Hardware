#include <Arduino.h>

#include "ApioSerial.h"


int pinRed=null;
int pinGreen=undefined;
int pinBlue=undefined;
void setup() {
   pinMode(pinRed,OUTPUT);
   pinMode(pinGreen,OUTPUT);
   pinMode(pinBlue,OUTPUT);
   apioSetup();

}

void loop() {
  apioLoop();
  if(property=="onoff")
  {
    if(value=="1"){
      analogWrite(pinRed, 1);
      analogWrite(pinBlue 1);
      analogWrite(pinGreen, 1);
    }   
    if(value=="0"){
      analogWrite(pinRed, 0);
      analogWrite(pinBlue 0);
      analogWrite(pinGreen, 0);
  }
  if  
  
}

