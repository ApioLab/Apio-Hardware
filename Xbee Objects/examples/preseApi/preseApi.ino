 /* sketch
turn on a fan using a relay and a button
*/
#include <XBee.h>
#include "ApioXbee.h"

int Relay1 = 2;
int stateRelay1 = HIGH;

int Relay2 = 3;
int stateRelay2 = HIGH;

int Relay3 = 4;
int stateRelay3 = HIGH;

int Relay4 = 5;
int stateRelay4 = HIGH;


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
        if(proprieta=="onoffuno") {
            if(valore.toInt() == 1){
                stateRelay1 = LOW;
                digitalWrite(Relay1, stateRelay1);
            } else {
                stateRelay1 = HIGH;
                digitalWrite(Relay1, stateRelay1);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onoffdue") {
            if(valore.toInt() == 1){
                stateRelay2 = LOW;
                digitalWrite(Relay2, stateRelay2);
            } else {
                stateRelay2 = HIGH;
                digitalWrite(Relay2, stateRelay2);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onofftre") {
            if(valore.toInt() == 1){
                stateRelay3 = LOW;
                digitalWrite(Relay3, stateRelay3);
            } else {
                stateRelay3 = HIGH;
                digitalWrite(Relay3, stateRelay3);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="onoffquattro") {
            if(valore.toInt() == 1){
                stateRelay4 = LOW;
                digitalWrite(Relay4, stateRelay4);
            } else {
                stateRelay4 = HIGH;
                digitalWrite(Relay4, stateRelay4);
            }
         
        proprieta="";    
        }
        
        if(proprieta=="ping")
        {
          apioSend("1234:hi:40B3E1EB:z-");
        }
          
}
