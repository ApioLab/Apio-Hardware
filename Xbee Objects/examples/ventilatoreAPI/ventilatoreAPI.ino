/* sketch
turn on a fan using a relay and a button
*/
#include <XBee.h>
#include "XbeeLib0_3.h"

int Relay = 2;
int Relay2= 3;
int stateRelay = LOW;
int stateRelay2 = LOW;


/*void serialEvent(){
    content=Serial.readStringUntil(':');
    if(content!=""){
        oggetto=content;
        if(oggetto=="987532"){   
            content=Serial.readStringUntil(':');
            chiave=content;
            content=Serial.readStringUntil(':');
            valore=content;
        } else {
            Serial.read();
        }
   }
}*/

void setup() {
    Serial.begin(9600);
    xbee.setSerial(Serial);
    pinMode(Relay, OUTPUT);
    pinMode(Relay2, OUTPUT);
    
}
     
void loop() {
  XBeeInput();
  select();
        if(proprieta=="onoff") {
            if(valore.toInt() == 0){
                stateRelay = LOW;
                digitalWrite(Relay, stateRelay);
            } else {
                stateRelay = HIGH;
                digitalWrite(Relay, stateRelay);
            }
            
        }
        if (proprieta=="velocita"){
          if (valore.toInt() == 1){
            stateRelay2 = LOW;
            digitalWrite(Relay2, stateRelay2);
          } else if (valore.toInt() == 2){
            stateRelay2=HIGH;
            digitalWrite(Relay2, stateRelay2);
          }        
        }
}
