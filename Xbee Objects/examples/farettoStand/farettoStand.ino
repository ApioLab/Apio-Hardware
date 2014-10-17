#include <Arduino.h>
//librerie per lwm
#include "lwm.h";
#include "lwm/sys/sys.h"
#include "lwm/nwk/nwk.h"

#include "ApioLwm.h"
int pinValue=2;
int valore_attuale;
int flag2=0;

void setup() {
  Serial1.begin(115200); //riga di debug
  apioSetup();
  apioSend("3:hi:3:l-");
  pinMode(pinValue, OUTPUT);
  analogWrite(pinValue,0);
}

void scrivi(int a, int flag1)
{
  if(flag1==0)
  {
    valore_attuale=a;
    analogWrite(pinValue,a);
  }
  if(flag1==1)
  {
    analogWrite(pinValue,a);
  }
  if(flag1==2)
  {
    valore_attuale=a;

  }
  
}

void loop() {
  SYS_TaskHandler();
  select();
  if(proprieta=="onoff")
  {
     if(valore.toInt()==1){
       flag2=0; 
         if(valore_attuale==0)
          {
             
             scrivi(255,0);
             Serial1.println("OK");
          }
          else
          {
            scrivi(valore_attuale,0);
          }
     }
    else
    {
      scrivi(0,1);
      flag2=1;
    } 
  }   
  if(proprieta=="intensita")
  {
    if(flag2==0)
    {
      scrivi(valore.toInt(),0);
    }
    if(flag2==1)
    {
      scrivi(valore.toInt(),2);
    }
  }
}

