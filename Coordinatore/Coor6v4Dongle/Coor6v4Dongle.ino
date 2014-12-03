//librerie generiche
#include <Arduino.h>

//Libreria per il watchdog
#include <avr/wdt.h>

//librerie per lwm
#include "lwm.h";
#include "lwm/sys/sys.h"
#include "lwm/nwk/nwk.h"



//librerie per Xbee
#include <XBee.h>
#include "coordinatore.h"

#define INDIRIZZO_COORIDATORE_LWM 4
/*-----------------dichiarazioni variabili--------------------------------------------*/

char comando=0;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//++++++++++++++++++++++++fine dichiarazioni+++++++++++++++++++++++++++++++++++++++++


void setup() {
  wdt_disable();
  delay(1000);
  Serial.begin(115200); //per la comunicazione con il web server
  
  //setup Xbee
  Serial1.begin(9600);//per la comunicazione con l xbee
  xbee.setSerial(Serial1);
   
  //setup LWM
  SYS_Init();
  NWK_SetAddr(INDIRIZZO_COORIDATORE_LWM);
  NWK_SetPanId(0x01);
  PHY_SetChannel(0x1a);
  PHY_SetRxState(true);
  NWK_OpenEndpoint(1, LwmInput);
  
  Serial.println("setup");
  wdt_enable(WDTO_8S);

}

void loop() 
{
  SYS_TaskHandler(); //funzione lwm da chiamare spesso (cosi dice la documentazione)
        

  
  /*-------------lettura dei comandi dal webserver (su Serial1)-------------*/
  if(Serial.available())
  {
    comando = ReadFromWebServer(); //legge dal WebServer setta la variabile comando e mette su content il messaggio da inviare

    switch(comando)
    {
      
      // se il seriale contiene una 'z' allora abilito la lettura dei parametri zigbee
     case('z'):
        XBeeOutput();
        break;
        
      
     
      // se il seriale contiene una 'l' allora abilito la lettura dei parametri lwm
      case('l'):
        LwmOutput();
        break;
        
     }  
    content="";
    dispositivo="";
    comando=NULL;
  }
/*-------------RX----------------------*/  
  //verifica se ci sono dati in arrivo dagli oggetti
  //domand: forse è da mettere l'if dentro SerialToWebServer e gestire il tutto in quella funzione di libreria?
XBeeInput(); //riempie dispositivo1 proprieta1 valore1
wdt_reset();
}
