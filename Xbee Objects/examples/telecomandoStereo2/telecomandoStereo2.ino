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
#include "XbeeLib.h"

IRsend irsend;

decode_results results;
int buttonState = 0;
int pin = 13;

void setup()
{
  Serial.begin(9600);
  xbee.setSerial(Serial);
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

void loop() {
  XBeeInput();
  if (proprieta!="")
  {
    buttonState=HIGH;
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
    if(valore.toInt()==1)
    {
     codeValue=1040; 
    }
    else
    {
      codeValue=1041;
    }
  }  
  if (buttonState) {
    Serial.println("Pressed, sending");
    digitalWrite(pin, HIGH);
    sendCode(lastButtonState != buttonState);
    delay(100); // Wait a bit between retransmissions
    lastButtonState = buttonState;
    delay(100);
    digitalWrite(pin, LOW);
    buttonState=LOW;
    proprieta="";
    dispositivo="";
  } 

}
