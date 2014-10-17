#define trigPin 3
#define echoPin 2
#include <XBee.h>
#include "ApioXbee.h"
#include "dht.h"
#define dht_dpin A0

dht DHT;

int Flag=0;
int pin=13;
int temperature;
int humidity;

void setup() {
  apioSetupUno();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pin, OUTPUT);
  delay(1000);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 30 && Flag==0) {  // This is where the LED On/Off happens
      apioSend("1001:update:onoff:1-?3");
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
      Flag=1;    
  }
  if (distance > 50 && Flag==1) {
      apioSend("1001:update:onoff:0-?4");
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
      Flag=0; 
  }
  delay(500);
 
  DHT.read11(dht_dpin);
  if (humidity != DHT.humidity)
  {
    humidity = DHT.humidity;
    String hum = String(humidity);
    apioSend("1001:update:humidity:"+hum+"-");
    
  }
  if (temperature != DHT.temperature)
  {
    temperature = DHT.temperature;
    String temp = String(temperature);
    apioSend("1000:update:temperature:"+temp+"-"); 
  }
  delay(800);
}
