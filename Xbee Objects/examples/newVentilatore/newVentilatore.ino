#include <XBee.h>
#include "ApioGeneralLib.h"
#include "ApioXbeeLib.h"

int ReadButton = 2;     //ONOFF
int ReadButton1 = 4;    //SWING
int ReadFade = A0;

int WriteButton=7;
int WriteButton1=8;
int WriteFade=6;

int valFade;
int sup;
int inf;
int statoSlider=0;
//Parte da spento e rotazione spento
String stateOnoff = "0";
String stateSwing = "0";

void setup()  { 
  // nothing happens in setup
  pinMode(WriteButton, OUTPUT);
  pinMode(WriteButton1, OUTPUT);
  pinMode(ReadButton,INPUT);
  pinMode(ReadButton, INPUT);
  
  Serial.begin(9600);
  xbee.setSerial(Serial);
  digitalWrite(ReadButton, HIGH);
  digitalWrite(ReadButton1, HIGH);
  digitalWrite(WriteButton, HIGH);
  digitalWrite(WriteButton1, HIGH);
} 

void loop()  {
  XBeeSerialInput();
  select(); 
  if(digitalRead(ReadButton)==0)
  {
    delay(200);
    if(digitalRead(ReadButton)==0)
    {
      //Scrivi sul pin    
      //Spara messaggio XBee
      if(stateOnoff=="0")
      {
        stateOnoff="1";
        XBeeSend_to_coordinator("1111:update:onoff:"+stateOnoff+"-");
        delay(10);
        
      }
      else if(stateOnoff=="1")
      {
        stateOnoff="0";
        XBeeSend_to_coordinator("1111:update:onoff:"+stateOnoff+"-");
        delay(10);
      }
      digitalWrite(WriteButton, LOW);
      delay(150);
      digitalWrite(WriteButton,HIGH);
      delay(500);
    }
  }
  if(digitalRead(ReadButton1)==0)
  {
    delay(200);
    if(digitalRead(ReadButton1)==0)
    {
      //Spara messaggio XBee
      if(stateOnoff=="0")
      {
        stateOnoff="1";
        XBeeSend_to_coordinator("1111:update:rotazione:"+stateOnoff+"-");
        delay(10);
        
      }
      else if(stateOnoff=="1")
      {
        stateOnoff="0";
        XBeeSend_to_coordinator("1111:update:rotazione:"+stateOnoff+"-");
        delay(10);
      }
            //Scrivi sul pin
      digitalWrite(WriteButton1, LOW);
      delay(150);
      digitalWrite(WriteButton1,HIGH);
      delay(500);
    }
  }
  valFade=analogRead(ReadFade);
  delay(500);
  if(analogRead(ReadFade)>valFade+30 || analogRead(ReadFade)<=valFade-30)
  {
    //Spara messaggio XBee
    //Scrive sul pin
    analogWrite(WriteFade, valFade/4);
    statoSlider=valFade;
    String va=String(statoSlider/4);
    XBeeSend_to_coordinator("1111:update:velocita:"+va+"-");
    delay(200);
  }
  if(proprieta=="velocita")
  {
    
    analogWrite(WriteFade, valore.toInt());
    proprieta="";
  }
  if (proprieta=="onoff")
  {
    if(valore.toInt()==1 && stateOnoff=="0")
    {
        digitalWrite(WriteButton, LOW);
        delay(200);
        digitalWrite(WriteButton,HIGH);
         stateOnoff="1"; 
    }
    if(valore.toInt()==0 && stateOnoff=="1")
    {
        digitalWrite(WriteButton, LOW);
        delay(200);
        digitalWrite(WriteButton,HIGH);
        stateOnoff="0";
    }
   proprieta=""; 
  }
  if (proprieta=="rotazione")
  {
    if(valore.toInt()==1 && stateSwing!="1")
      {
        digitalWrite(WriteButton1, LOW);
        delay(200);
        digitalWrite(WriteButton1,HIGH); 
        stateSwing="1";
      }
    if(valore.toInt()==0 && stateSwing!="0")
      {
        digitalWrite(WriteButton1, LOW);
        delay(200);
        digitalWrite(WriteButton1,HIGH);
        stateSwing="0"; 
      }  
    proprieta="";
  }
}
