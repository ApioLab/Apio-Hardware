 /* sketch
turn on a fan using a relay and a button
*/
#include <XBee.h>
#include "ApioXbee.h"

int Relay1 = 3;
int stateRelay1 = LOW;

int Relay2 = 3;
int stateRelay2 = LOW;

int Relay3 = 3;
int stateRelay3 = LOW;

int Relay4 = 3;
int stateRelay4 = LOW;


void setup() {
    apioSetup();
    pinMode(Relay1, OUTPUT);
    pinMode(Relay2, OUTPUT);
    pinMode(Relay3, OUTPUT);
    pinMode(Relay4, OUTPUT);
    digitalWrite(Relay1, stateRelay1);
    digitalWrite(Relay2, stateRelay2);
    digitalWrite(Relay3, stateRelay3);
    digitalWrite(Relay4, stateRelay4);
    delay(500);
    apioSend("1234:hi:40B3E1EB:z-");
    
}
     
void loop() {
//Questo permette di attivare la procedura di ricezione di proprieta e valori        
  apioReceive();
//IN base alla proprieta che arriva faccio qualcosa        
        if(proprieta=="onoff1") {
            if(valore.toInt() == 0){
                stateRelay = HIGH;
                digitalWrite(Relay, stateRelay);
            } else {
                stateRelay = LOW;
                digitalWrite(Relay, stateRelay);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onoff2") {
            if(valore.toInt() == 0){
                stateRelay = HIGH;
                digitalWrite(Relay, stateRelay);
            } else {
                stateRelay = LOW;
                digitalWrite(Relay, stateRelay);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onoff3") {
            if(valore.toInt() == 0){
                stateRelay = HIGH;
                digitalWrite(Relay, stateRelay);
            } else {
                stateRelay = LOW;
                digitalWrite(Relay, stateRelay);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onoff4") {
            if(valore.toInt() == 0){
                stateRelay = HIGH;
                digitalWrite(Relay, stateRelay);
            } else {
                stateRelay = LOW;
                digitalWrite(Relay, stateRelay);
            }
         
        proprieta="";    
        }        
}
