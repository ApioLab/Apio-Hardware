#include <dht.h>
#include <XBee.h>
#include "ApioXBee.h"
#include "sensors.h"

#define dht_dpin 7
dht DHT;

String temperature[20];
String humidity[20];

void setup()  
{ 
  Serial.begin(9600);
  apioSetupUno();
  //Here we assume that the objectID is 4545 and physical address is 40B3E1D4
  apioSend("4545:hi:40B3E1D4:z-"); //Send init for my object

} 

void loop()  
{
  //This is the function that we call in each loop and let you receive key value
  apioReceive();
  //Serial.println(tipo);
  //Funzioni per la registrazione
  if (proprieta=="temperatura")
  {
    if(tipo=="r")
    {
      insert_new(valore);
    }
    if(tipo=="d")
    {
      elimina(valore);
    }  
  }
  //Funzione che legge dal sensore
  DHT.read11(dht_dpin);
  //Funzioni che notificano
  //Serial.print(DHT.temperature);
  controlla(DHT.temperature);
  delay(800);
 
}
