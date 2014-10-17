#include <dht.h>
#define trigPin 3
#define echoPin 2
#include <XBee.h>
#include "ApioXBee.h"
#include "sensors.h"

#define dht_dpin 7
dht DHT;

String temperature[20];
String humidity[20];
long distance;

void setup()  
{ 
  Serial.begin(9600);
  apioSetupUno();
  //Here we assume that the objectID is 4545 and physical address is 40B3E1D4
  apioSend("4545:hi:40B3E1D4:z-"); //Send init for my object
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
} 

long leggiSonar()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
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
  distance= leggiSonar();
  Serial.println(distance);
  //Serial.print(DHT.temperature);
  controlla(DHT.temperature);
  delay(800);
 
}
