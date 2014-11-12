//Libreria per il watchdog
#include <avr/wdt.h>

//librerie per Xbee
#include <XBee.h>


#include "coordinatore.h"



void setup() {
  wdt_disable();
 /*--------------------------------------------------------------------*/ 
 ApioCoordinatorSetup(); //inizializzazione coordinatore
  
 /*--------------------------------------------------------------------*/  
  wdt_enable(WDTO_8S);
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available()>0)
  {
      comando = ReadFromWebServer();
        Serial.println(comando);      
        switch(comando)
        {
          case('z'):
            Serial.println("case z"); //debug
            XBeeOutput();
          break;
        }
        
    content="";
    dispositivo="";
    comando=NULL;
        
   }    


  XBeeInput(); //riempie dispositivo1 proprieta1 valore1
 /*--------------------------------------------------------------------*/ 
  wdt_reset(); //watchdog reset
}
