#include <XBee.h>
#include "ApioXBee.h"
#include "Tlc5940.h"


int dim;
int R; 
int G;
int B;
int W;
int R1;
int G1;
int Bb1;
int W1;

void rgbw(int r, int g, int b, int w, int w1, int b1, int g1, int r1, int flag1)
{
  /*r = dim * r / 4095;
  g = dim * g / 4095;
  b = dim * b / 4095;
  w = dim * w / 4095;
  r1 = dim * r1 / 4095;
  g1 = dim * g1 / 4095;
  b1 = dim * b1 / 4095;
  w1 = dim * w1 / 4095;*/
  if(flag1==0){
    R=r;
    G=g;
    B=b;
    W=w;
    R1=r1;
    G1=g1;
    Bb1=b1;
    W1=w1;
  }
  Tlc.clear();
  Tlc.set(0, 4095-r1);
  Tlc.set(1, 4095-g1);
  Tlc.set(2, 4095-b1);
  Tlc.set(3, 4095-w1);
  Tlc.set(4, 4095-w);
  Tlc.set(5, 4095-b);
  Tlc.set(6, 4095-g);
  Tlc.set(7, 4095-r);
  Tlc.update();
}

void candela(int max){
  int val;
  val=random(max/4,max);
  rgbw(val,val*5/10-random(max/10),0,0,0,0,val*5/10-random(max/10),val,1);
  delay(15+random(45));
}

void setup()  
{ 
  apioSetupUno();
  apioSend("4545:hi:40B3E1DA:z-");
  delay(1000);
  Tlc.init();
  delay(500);
  dim=0;
  rgbw(0,0,0,0,0,0,0,0,0);
} 


void loop()  
{
  apioReceive();
  ///Azioni che devono generare un output
  if(proprieta=="onoff")
  {
    if(valore=="1")
    {
      if(R==0 && G==0 && B==0 && W==0 && R1==0 && G1==0 && Bb1==0 && W1==0)
      {
        rgbw(4000,4000,4000,4000,4000,4000,4000,4000,1);
      }
      else
      {
        rgbw(R,G,B,W,R1,G1,Bb1,W1,0);
      }
    }
    else
    {
      rgbw(0,0,0,0,0,0,0,0,1);
    }
    proprieta="";
  }
  if(proprieta=="rosso")
  {
    rgbw(valore.toInt(),G,B,W,W1,Bb1,G1,valore.toInt(),0);
    proprieta="";
  }
  if(proprieta=="verde")
  {
    rgbw(R,valore.toInt(),B,W,W1,Bb1,valore.toInt(),R1,0);
    proprieta="";
  }
  if(proprieta=="blu")
  {
    rgbw(R,G,valore.toInt(),W,W1,valore.toInt(),G1,R1,0);
    proprieta="";
  }
  if(proprieta=="bianco")
  {
    rgbw(R,G,B,valore.toInt(),valore.toInt(),Bb1,G,R,0);
    proprieta="";
  }
  if(proprieta=="funzioni")
  {
    int flag=0;
    if(valore=="1")
    {
      flag=1;
      
      //Rainbow1
      if(flag==1)
      {
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095,i,0,0,0,0,i,4095,1);  delay(2);  }
      }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095-i,4095,0,0,0,0,4095,4095-i,1);  delay(2);  }	
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,4095,i,0,0,i,4095,0,1); delay(2);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0; } rgbw(0,4095-i,4095,0,0,4095,4095-i,0,1);  delay(2);  }
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,0,4095,i,i,4095,0,0,1);  delay(2);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,0,4095-i,4095,4095,4095-i,0,0,1);  delay(2);  }
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0; } rgbw(i,0,0,4095-i,4095-i,0,0,i,1);  delay(2);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095,0,0,0,0,0,0,4095,1);  delay(2);  }
      }
    }
    if(valore=="2")
    {
      //Rainbow2
      int gioco=3000;
      rgbw(random(gioco),random(gioco),random(gioco),random(gioco),random(gioco),random(gioco),random(gioco),random(gioco),1);
      delay(1000);
    }
    if(valore=="3")
    {
      //Bianco
      rgbw(0,0,0,4095,4095,0,0,0,0);
      proprieta="";
    }
    if(valore=="4")
    {
      rgbw(3000,2500,2000,1000,1000,2000,2500,3000,0);
      proprieta="";
    }
    if(valore=="5")
    {
      //Rosso
      rgbw(4095,0,0,0,0,0,0,4095,0);
      proprieta="";
    }
    if(valore=="6")
    {
      //Arancio
      rgbw(4095,1005,0,0,0,0,1005,4095,0);
      proprieta="";
    }
    if(valore=="7")
    {
      //Giallo
      rgbw(4095,4095,0,0,0,0,4095,4095,0);
      proprieta="";
    }
    if(valore=="8")
    {
      //Verde
      rgbw(0,4095,0,0,0,0,4095,0,0); 
       proprieta="";     
    }
    if(valore=="9")
    {
      //Acqua
      rgbw(0,4095,633,0,0,633,4095,0,0);
      proprieta="";
    }
    if(valore=="10")
    {
      rgbw(0,4095,4095,0,0,4095,4095,0,0);
      proprieta="";
    }
    if(valore=="11")
    {
      //Blu
      rgbw(0,0,4095,0,0,4095,0,0,0);
      proprieta="";
    }
    if(valore=="13")
    {
      //Fuxia
      rgbw(4095,0,707,0,0,4095,0,707,0);
      proprieta="";
    }
    if(valore=="15")
    {
      flag=1;
      
      if(flag==1)
      {
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095,i,0,0,0,0,i,4095,1);  delay(6);  }
      }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095-i,4095,0,0,0,0,4095,4095-i,1);  delay(6);  }	
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,4095,i,0,0,i,4095,0,1); delay(6);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0; } rgbw(0,4095-i,4095,0,0,4095,4095-i,0,1);  delay(6);  }
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,0,4095,i,i,4095,0,0,1);  delay(6);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(0,0,4095-i,4095,4095,4095-i,0,0,1);  delay(6);  }
      }
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0; } rgbw(i,0,0,4095-i,4095-i,0,0,i,1);  delay(6);  }
      if(flag==1){
        for(uint16_t i = 0; i < 4096; i+=1) {if(Serial.available()){break; flag=0;} rgbw(4095,0,0,0,0,0,0,4095,1);  delay(6);  }
      }
    }
    if(valore=="16")
    {
      flag=1;
      
      candela(4095);
    }
    
  }
}
