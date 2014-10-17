/*
 * IRrecord: record and play back IR signals as a minimal 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected to the input BUTTON_PIN; this is the
 * send button.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <XBee.h>
#include <IRremote.h>
#include "ApioXbee.h"

IRsend irsend;

decode_results results;
int buttonState = 0;
int pin = 13;
int repeatNumber=1;

void setup()
{
  apioSetup();
  pinMode(pin, OUTPUT);
}

// Storage for the recorded code
int codeType = RC5; // The type of code
unsigned long codeValue; // The code value if not raw
int codeLen=12; // The length of the code
int toggle = 0; // The RC5/6 toggle state


void sendCode(int repeat) {
  if (codeType == RC5 || codeType == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      toggle = 1 - toggle;
    }
    // Put the toggle bit into the code to send
    codeValue = codeValue & ~(1 << (codeLen - 1));
    codeValue = codeValue | (toggle << (codeLen - 1));
    if (codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue);
      irsend.sendRC5(codeValue, codeLen);
    } 
  } 
}

int lastButtonState;
int statoVolume=0;
void loop() {
  
  apioReceive();
  if (proprieta!="")
  {
    buttonState=1;
  }
  // If button pressed, send the code. 
  if(proprieta=="onoff")
  {
    codeValue=949;
  }
  if(proprieta=="muto")
  {
    codeValue=1037;
  }
  if(proprieta=="avanti")
  {
    codeValue=928;
  }
  if(proprieta=="indietro")
  {
    codeValue=929;
  }
  if(proprieta=="volume")
  {
    int intervallo=valore.toInt()-statoVolume;
    statoVolume=valore.toInt();
    if(intervallo>0)
    {
     repeatNumber=intervallo;
     codeValue=1040; 
    }
    else
    {
      repeatNumber=-intervallo;
      codeValue=1041;
    }
  }  
  if (buttonState) {
    Serial.println("Pressed, sending");
    for(int i=0; i<repeatNumber; i++)
    {
/*      if(!lastButtonState)
      {
        buttonState=1;
      }*/
      digitalWrite(pin, HIGH);
      sendCode(lastButtonState != buttonState);
      delay(100); // Wait a bit between retransmissions
      lastButtonState = buttonState;
      delay(100);
      buttonState=LOW;
      digitalWrite(pin, LOW);
    }
    proprieta="";
    dispositivo="";
    repeatNumber=1;
  } 

}
