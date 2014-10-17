#include <DmxSimple.h>
#include <XBee.h>
#include "oggettoX.h"

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
}

void loop()
{
 Input();
 Select();
 if(proprieta=="onoff1")
 {
   
 }
 if (proprieta=="dimmer1")
 {
   
 }
 if (proprieta=="rainbow1")
 {
   
 }
 if(proprieta=="onoff2")
 {
   
 }
 if (proprieta=="dimmer2")
 {
   
 }
 if (proprieta=="rainbow2")
 {
   
 }
 if(proprieta=="onoff3")
 {
   
 }
 if (proprieta=="dimmer3")
 {
   
 }
 if (proprieta=="rainbow3")
 {
   
 }
 if(proprieta=="onoff4")
 {
   
 }
 if (proprieta=="dimmer4")
 {
   
 }
 if (proprieta=="rainbow4")
 {
   
 }
 if(proprieta=="onoff5")
 {
   
 }
 if (proprieta=="dimmer5")
 {
   
 }
 if (proprieta=="rainbow5")
 {
   
 }
 if(proprieta=="onoff6")
 {
   
 }
 if (proprieta=="dimmer6")
 {
   
 }
 if (proprieta=="rainbow6")
 {
   
 } 
}
