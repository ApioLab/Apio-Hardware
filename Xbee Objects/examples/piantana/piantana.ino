#include <XBee.h>
#include <ApioXbee.h>

int pinRed = 6;
int pinGreen = 9;
int pinBlue = 10;

int R; 
int G;
int B;

void rgb(int r, int g, int b, int flag1)
{
  /*r = dim * r / 4095;
  g = dim * g / 4095;
  b = dim * b / 4095;
  w = dim * w / 4095;
  r1 = dim * r1 / 4095;
  g1 = dim * g1 / 4095;
  b1 = dim * b1 / 4095;
  w1 = dim * w1 / 4095;*/
  if(flag1==0)
  {  
    R=r;
    G=g;
    B=b;
  }
  analogWrite(pinRed, r);
  analogWrite(pinGreen, g);
  analogWrite(pinBlue, b);
  
  
}

void candela(int max){
  int val;
  val=random(max/4,max);
  rgb(val,val*5/30-random(max/3),0,1);
  delay(15+random(45));
}

void setup()  
{ 
  apioSetupUno();
  apioSend("4545:hi:40869AB8:z-");
  delay(1000);
  rgb(0,0,0,0);
} 


void loop()  
{
  apioReceive();
  ///Azioni che devono generare un output
  if(proprieta=="onoff")
  {
    if(valore=="1")
    {
      rgb(R,G,B,0);
    }
    else
    {
      rgb(0,0,0,1);
    }
  }
  if(proprieta=="rosso")
  {
    rgb(valore.toInt(),G,B,0);
    proprieta="";
  }
  if(proprieta=="verde")
  {
    rgb(R,valore.toInt(),B,0);
    proprieta="";
  }
  if(proprieta=="blu")
  {
    rgb(R,G,valore.toInt(),0);
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
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255,i,0,1);  delay(8);  }
      }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255-i,255,0,1);  delay(8);  }	
      }
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(0,255,i,1); delay(8);  }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0; } rgb(0,255-i,255,1);  delay(8);  }
      }
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(i,0,255,1);  delay(8);  }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255,0,255-i,1);  delay(8);  }
      }
    }
    if(valore=="2")
    {
      //Rainbow2
      int gioco=255;
      rgb(random(gioco),random(gioco),random(gioco),1);
      delay(1000);
    }
    if(valore=="3")
    {
      //Bianco
      rgb(128,255,145,0);
      proprieta="";
    }
    if(valore=="4")
    {
      rgb(255,100,50,0);
      proprieta="";
    }
    if(valore=="5")
    {
      //Rosso
      rgb(255,0,0,0);
      proprieta="";
    }
    if(valore=="6")
    {
      //Arancio
      rgb(255,19,0,0);
      proprieta="";
    }
    if(valore=="7")
    {
      //Giallo
      rgb(255,91,0,0);
      proprieta="";
    }
    if(valore=="8")
    {
      //Verde
      rgb(0,255,0,0); 
       proprieta="";     
    }
    if(valore=="9")
    {
      //Acqua
      rgb(0,255,22,0);
      proprieta="";
    }
    if(valore=="10")
    {
      rgb(0,255,255,0);
      proprieta="";
    }
    if(valore=="11")
    {
      //Blu
      rgb(0,0,255,0);
      proprieta="";
    }
    if(valore=="12")
    {
      rgb(177,0,255,0);
    }
    if(valore=="13")
    {
      //Fuxia
      rgb(255,0,8,0);
      proprieta="";
    }
    if(valore=="15")
    {
      flag=1;
      
      //Rainbow1
      if(flag==1)
      {
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255,i,0,1);  delay(20);  }
      }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255-i,255,0,1);  delay(20);  }	
      }
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(0,255,i,1); delay(20);  }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0; } rgb(0,255-i,255,1);  delay(20);  }
      }
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(i,0,255,1);  delay(20);  }
      if(flag==1){
        for(uint16_t i = 0; i < 255; i+=1) {if(Serial.available()){break; flag=0;} rgb(255,0,255-i,1);  delay(20);  }
      }
    }
    if(valore=="16")
    {
      flag=1;
      
      candela(255);
    }
  }
}
