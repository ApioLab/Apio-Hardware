
/**************************************************************************\
* Apio Library                                                         *
* https://github.com/Apio/library-Apio                             *
* Copyright (c) 2012-2014, Apio Inc. All rights reserved.              *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the BSD License as described in license.txt.         *
\**************************************************************************/


///////////////////// oled
#include <SPI.h>
#include <Wire.h>

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET 6
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
///////////////////// oled
#define rt_baud_prescale 3   // 3 = 250K, 0 = 1M, if UCSRA = 0!!! else if = 1 Baudrate is x2 


#include <Arduino.h>
#include "Apio.h"
#include <avr/eeprom.h>
#include "atmegarfr2.h"
#include "StringBuffer.h"
#include "String.h"

ApioClass Apio;

boolean running_hearth = false;

void divide_string(String stringToSplit) {

  int strlen=stringToSplit.length();
  //Serial1.println(stringToSplit); //debug
  int i; //counter
  Apio.deviceAddr="";
  Apio.messageId="";
  Apio.property="";
  Apio.value="";
  i=0;
  for(i; stringToSplit.charAt(i)!=':' && i<strlen ;i++)
  {
    Apio.deviceAddr += String(stringToSplit.charAt(i));
  }
  /*
  for(i; stringToSplit.charAt(i)!=':' && i<strlen ;i++)
  {
    Apio.messageId += String(stringToSplit.charAt(i));
  }*/
  //-----------property----------------
  for(i++; stringToSplit.charAt(i)!=':' && i<strlen ;i++)
  {
    Apio.property += String(stringToSplit.charAt(i));
  }
  //-----------value----------------
  for(i++; stringToSplit.charAt(i)!='-' && i<strlen ;i++)
  {
    Apio.value += String(stringToSplit.charAt(i));
  }
  /*int newProperty = 1;
  for(int j = 0; j<Apio.indexReceived; j++)
  {
    if(Apio.propertyReceived[j]==Apio.property)
    {
      Apio.valueReceived[j] = Apio.value;
      newProperty = 0;
    }
  }
  if(newProperty)
  {
    Apio.propertyReceived[Apio.indexReceived]=Apio.property;
    Apio.valueReceived[Apio.indexReceived]= Apio.value;
    Apio.indexReceived++;
  }*/


  //Serial.println(Apio.messageId);
}

static int fieldAnswerTo = 0;
static char *fieldAnswerChunks;
static int fieldAnswerChunksAt;
static int fieldAnswerRetries;
static StringBuffer fieldCommand(0, 16);

StringBuffer a;

static NWK_DataReq_t toSend;





// mesh callback for handling incoming commands
static bool receive(NWK_DataInd_t *ind);

static bool receive(NWK_DataInd_t *ind) {
  if(Apio.isDongle)
  {
    //Serial.println("FUCK");
    int message_size=ind->size;
    
    char bufferL[62]=" ";
    for(int i=0; i<message_size; i++)
    {
      //Serial.print(ind->data[i]);
      bufferL[i] = ind->data[i];
    }
    //Serial.println();
    //Serial.println(ind->dstEndpoint);
    //Serial.println(abs(ind->rssi));
    Serial.println(String(bufferL));
    return true;
  } else {
    //Serial.println("Ciao ho ricevuto questo");
    int message_size=ind->size;
    int i;
    char Buffer[110];
    String receivedL="";
    for(i=0; i<message_size; i++)
    {
      Buffer[i] = ind->data[i];

      //delay(10);
      //Serial.write(ind->data[i]);

    }
    //Serial.println();
    
    NWK_SetAckControl(abs(ind->rssi));
    //Serial.println(String(Buffer));
    divide_string(String(Buffer));

    for(int i=0; i<100; i++)
    {
      Buffer[i]=NULL;

    }
    return true;

  }
  /*
  numvar ret;
  if (Scout.handler.isVerbose) {
    Serial.print(F("Received command"));
    Serial.print(F("lqi: "));
    Serial.print(ind->lqi);
    Serial.print(F("  "));
    Serial.print(F("rssi: "));
    Serial.println(ind->rssi);
  }

  if (fieldAnswerTo) {
    if (Scout.handler.isVerbose) {
      Serial.println(F("can't receive command while sending answer"));
    }
    return false;
  }

  if (!fieldCommand.concat((const char*)ind->data, ind->size)) {
    return false; // TODO we need to restart or something, no memory
  }

  // ack w/ our rssi as control
  NWK_SetAckControl(abs(ind->rssi));

  // when null terminated, do the message
  if (fieldCommand[fieldCommand.length() - 1] != '\0') {
    if (Scout.handler.isVerbose) {
      Serial.println(F("waiting for more"));
    }
    return true;
  }

  if (Scout.handler.isVerbose) {
    Serial.print(F("running command "));
    Serial.println(fieldCommand.c_str());
  }

  Shell.lastMeshRssi = abs(ind->rssi);
  Shell.lastMeshLqi = ind->lqi;
  Shell.lastMeshFrom = ind->srcAddr;

  fieldCommandOutput = "";
  ret = Shell.eval(PrintToString(fieldCommandOutput), fieldCommand);
  fieldCommand = (char*)NULL;

  if (Scout.handler.isVerbose) {
    Serial.print(F("got result "));
    Serial.println(ret);
    Serial.println(fieldCommandOutput.c_str());
  }

  // a command from the command endpoint doesn't get a response
  if(ind->srcEndpoint == 2)
  {
    fieldCommandOutput = (char*)NULL;
    return true;
  }

  // send data back in chunks
  fieldAnswerTo = ind->srcAddr;
  fieldAnswerChunksAt = 0;
  fieldAnswerRetries = 0;
  fieldAnswerChunk();

  return true;
  */
}


void appDataConf(NWK_DataReq_t *req)
{
  //Serial.print("ACK: "); //debug
  switch(req->status)
  {
    case NWK_SUCCESS_STATUS:
      //if(Apio.isDongle) Serial.println("1:"+String(req->dstAddr));
      //Serial.println(String(req->control));
      Apio.ack = 1;
      //Serial.print("ok:"+String((const char*) req->data));
      break;
    case NWK_ERROR_STATUS:
      //if(Apio.isDongle) Serial.println("2:"+String(req->dstAddr));
      Apio.ack = 2;
      break;
    case NWK_OUT_OF_MEMORY_STATUS:
      //if(Apio.isDongle) Serial.println("3:"+String(req->dstAddr));
      Apio.ack = 3;
      break;
    case NWK_NO_ACK_STATUS:
      //if(Apio.isDongle) Serial.println("4:"+String(req->dstAddr));
      //if(Apio.isDongle) Serial.println(req->control);
      Apio.ack = 4;
      break;
    case NWK_NO_ROUTE_STATUS:
      //if(Apio.isDongle) Serial.println("5:"+String(req->dstAddr));
      Apio.ack = 5;
      break;
    case NWK_PHY_CHANNEL_ACCESS_FAILURE_STATUS:
      //if(Apio.isDongle) Serial.println("6:"+String(req->dstAddr));
      Apio.ack = 6;
      break;
    case NWK_PHY_NO_ACK_STATUS:
      //if(Apio.isDongle) Serial.println("7:"+String(req->dstAddr));
      Apio.ack = 7;
      break;
    default:
      //if(Apio.isDongle) Serial.println("no correspondence in ack");
      break;


  }
  Apio.nwkDataReqB = 0;
  //Work Here
  //Serial.println("Ack vale "+String(req->control));
  int message_size=req->size;
  
  int i;
  char x[100];
  //String receivedL="";
  //Apio.codaInvio[Apio.toInsert] = "";
  if(Apio.ack==1){
    Serial.print("ok:");
    for(int j=0; j<message_size; j++)
    {
      x[j] = req->data[j];
      Serial.print(x[j]);
      //delay(10);
      //Serial.write(ind->data[i]);
  
    }
    Serial.println();
  }
  //Serial.println(Apio.codaInvio[Apio.toInsert]);
  //Apio.codaRetry[Apio.toInsert]=millis();
  //Serial.println(Apio.codaInvio[Apio.toInsert]);
  
  //Serial.println(Apio.toInsert);
  /*if(Apio.ack!=1){
    codaInvio[toInsert]=
  }*/
  //Apio.loop();



}

//Apio.send();
//static void fieldAnswerChunk();



/*
// chunk packet confirmation callback by mesh
static void fieldAnswerChunkConfirm(NWK_DataReq_t *req);

// send the first/next chunk of the answer back and confirm
static void fieldAnswerChunk();

// mesh callback whenever another scout announces something on a channel
static bool fieldAnnouncements(NWK_DataInd_t *ind);
*/


ApioClass::ApioClass() {
  // this has to be called as early as possible before other code uses the register
  lastResetCause = GPIOR0;
  
}



ApioClass::~ApioClass() { }


/*Apio.setup(parametri sketchName, sketchRevision )
* Questa funzione mette in due variabile lo sketchName e lo sketchRevision.
* Poi fa SYS_Init(); la funzione che serve all'ATmega256rfr2
* Attiva PHY_RandomReq(); che genera numeri random (potrebbe tornare utile)
* Serial.begin(115200) questo va bene anche per noi, sia per la General che per il Dongle
*

*/

void ApioClass::setup(const char *sketchName, const char *sketchRevision, const uint16_t theAddress, const uint16_t thePanId) {
  this->sketchName = sketchName;
  this->sketchRevision = sketchRevision;
  this->hi = 0;
  SYS_Init();
  PHY_RandomReq();
  NWK_Init();
  
  
//  UBRR0H  = (rt_baud_prescale >>8);
//  UBRR0L  = rt_baud_prescale;
//  UCSR0B = ((1<<TXEN0)|(1<<RXEN0) | (1<<RXCIE0));
  
  Serial.begin(115200);
  theAdd= theAddress;
  if(theAddress==0)
  {
    this->isDongle=1;
    
    Serial.println("COORDINATOR ACTIVE");
  //////////// oled setup start
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.display();
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("COORD ACTIVE");
  //display.setCursor(0,9);
  //display.println("ATTIVO");
   display.display();
//////// oled setup start

  } else {
    this->isDongle=0;
    Serial.println("Sono una General");
    send(String(theAddress)+":hi::-");


  }


  //loadSettingsFromEeprom();
  //thePanId = getPanId();
  //int pan = getPanId();
  int pan = thePanId; 
  Serial.println("Pan ID vale "+String(pan));
  meshSetRadio(theAddress, pan, 0x1a);
  //Canale di ascolto di default messaggi Apio
  meshListen(1, receive);
  for(int j=0; j<10; j++){
    codaInvio[j]="";
  }

  //loadSettingsFromEeprom();
}

void ApioClass::loop() {
  SYS_TaskHandler();
  if(this->isDongle){
    /*if(!this->hi){
      if (this->isVerbose)
      {
        Serial.println("Invio l'hi a tutti");
        //display.clearDisplay();
       display.display();
        display.setCursor(0,9);
        display.println("TX -hi- To All ");
        display.display();
      }

      this->sendTo="65535";
      this->mex = "65535:hi:m-";
      this->hi=1;

      send();

    }*/
     /*if(!this->hi && millis()>15000){
      this->sendTo="65535";
      this->mex = "65535:hi:m-";
      this->hi=1;

      send();
      

    }*/
    //Serial.println(ack);
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      Serial.println("c");
      
      running_hearth = !running_hearth;
      digitalWrite(15,running_hearth);
      display.invertDisplay(running_hearth);
     
    }
    if(currentMillis-previousTable>10000){
      Serial.println("Here");
      NWK_RouteTableEntry_t *table = NWK_RouteTable();
      for (int i=0; i < NWK_ROUTE_TABLE_SIZE; i++) {
        if (table[i].dstAddr == NWK_ROUTE_UNKNOWN) {
          continue;
        }
        
        /*Serial.print(String(i)+"|Fixed:");
        Serial.print(table[i].fixed);
        Serial.print("|Multicast:");
        Serial.print(table[i].multicast);
        Serial.print("|Score:");
        Serial.print(table[i].score);
        Serial.print("|dstAddr:");
        Serial.print(table[i].dstAddr);
        Serial.print("|nextHp:");
        Serial.println(table[i].nextHopAddr);*/
      }
      previousTable = millis();
    }
    
    if(Serial.available()){
      char c = readFromSerial();
      //if(this->isVerbose) Serial.println(c+this->sendTo+":"+this->mex);
        display.clearDisplay();
        display.display();
        display.setCursor(0,0);
        display.println(c+this->sendTo+":"+this->mex);
        display.setCursor(66,9);
        display.println("ST256");
        display.display();
      if(c=='l') {
        flagSendInLoop=1;

        send();

      }else if(c=='s') {
        //Serial.println(Apio.mex);
        int i = 0;
        int flagAddPropertyValue=0;
        int len = Apio.mex.length();
        String p = "";
        String v = "";
        for(i=0;i<len; i++){
          if(Apio.mex.charAt(i)==':'){
            flagAddPropertyValue++;
            i++;
          }
          if(flagAddPropertyValue==1){
            p+=Apio.mex.charAt(i);
          }
          else if(flagAddPropertyValue==2){
            if(Apio.mex.charAt(i)!='-')
            v+=Apio.mex.charAt(i);
          }
          
        }
        Serial.println(p);
        if(p=="panId"){
          if(v!=""){
            setPanId(v.toInt());
            meshSetRadio(0, v.toInt(), 0x1a);
            Serial.println("Cambio panId "+v);
          } else if(v==""){
            int pan = getPanId();
            Serial.println("0:update:panId:"+String(pan));
          }
          
        
        } else if(p=="hi"){
          Serial.println("Invio l'hi");
          this->sendTo="65535";
          this->mex = "65535:hi:m-";
          this->hi=1;
    
          send();
          
        }
        
      }  else if(c=='p'){
          Serial.println("Here");
          NWK_RouteTableEntry_t *table = NWK_RouteTable();
          for (int i=0; i < NWK_ROUTE_TABLE_SIZE; i++) {
            if (table[i].dstAddr == NWK_ROUTE_UNKNOWN) {
              continue;
            }
            
            Serial.print(String(i)+"|Fixed:");
            Serial.print(table[i].fixed);
            Serial.print("|Multicast:");
            Serial.print(table[i].multicast);
            Serial.print("|Score:");
            Serial.print(table[i].score);
            Serial.print("|dstAddr:");
            Serial.print(table[i].dstAddr);
            Serial.print("|nextHp:");
            Serial.println(table[i].nextHopAddr);
          }
          
          
        } 
    }
    
  }

  if(!this->isDongle)
  {
    //This function backup the state of the object when the network goes down
    /*if(this->property=="hi"){
      for(int j = 0; j<indexReceived; j++)
      {
        if(this->isVerbose) Serial.println(theAdd+":update:"+propertyReceived[j]+":"+valueReceived[j]+"-");
        display.clearDisplay();
        display.display();
        display.setCursor(0,0);
        display.println(theAdd+":update:"+propertyReceived[j]+":"+valueReceived[j]+"-");
        display.display();
        
        send(theAdd+":update:"+propertyReceived[j]+":"+valueReceived[j]+"-");
      }
      this->property = "";*/
    //}
    //FIX HERE
    if(ack!=1 && contatoreInvii<6){
      //if(isVerbose) Serial.println("Non ho potuto inviare "+codaInvio+" riprovo");
      //send(codaInvio);
      contatoreInvii++;
    } else if (contatoreInvii>=6){
      if(isVerbose) Serial.println("Invio avvenuto correttamente o impossibile inviare");
      contatoreInvii = 0;
      ack=1;
    }
  }

  //Qui settiamo la tabella di routing
  //Controllo della rete

  /*bool showStatus = (indicate && lastIndicate < now && (now % indicate == 0));
  if(showStatus){
    NWK_RouteTableEntry_t *table = NWK_RouteTable();
    bool meshed = 0;
    for (int i=0; i < NWK_ROUTE_TABLE_SIZE; i++)
    {
      //Serial.println(String(table[i].dstAddr));
      if (table[i].dstAddr != NWK_ROUTE_UNKNOWN) meshed = 1;
    }

    if(meshed)
    {
      lastIndicate = now;
    }
  }*/
}

void ApioClass::goToSleep(uint32_t sleepForMs) {
  // TODO  http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=136036
  // - put radio to sleep
  // - set all GPIO pins to inputs
  // - turn off ADC
  // - turn off backpack power
  // - put MCU to sleep
}

void ApioClass::enableExternalAref() {
  isExternalAref = true;
  analogReference(EXTERNAL);
}

void ApioClass::disableExternalAref() {
  isExternalAref = false;
  ADMUX = (1 << REFS1) | (1 << REFS0); // 1.6V internal voltage ref.
}

bool ApioClass::getExternalAref() {
  return isExternalAref;
}

char ApioClass::readFromSerial() {
  //l16:onoff:1-rosso:255-verde:255-blu:255-funzioni:0-
  //Serial1.println("readfrom");
  this->sendTo="";
  this->mex = "";
  int flagAddr=0;
  char interface=NULL;
  delayMicroseconds(100); // it is needed, otherwise every now and then you lose the first character to be read!!!
  interface = Serial.read();
  delayMicroseconds(100);
  while (Serial.available())
  {
    char buf = Serial.read();
    delayMicroseconds(100);
    if(buf==':'){
      flagAddr=1;
    }
    if(flagAddr==0)
    {
      this->sendTo+=buf;
    }
    this->mex += buf;
  }
  
  delayMicroseconds(100);
  //Serial.println("ok:"+this->mex);
  //divide_string(content);
  return interface;
}

const char* ApioClass::getLastResetCause() {
  switch (lastResetCause) {
      case 1:
        return PSTR("Power-on");
        break;
      case 2:
        return PSTR("External");
        break;
      case 4:
        return PSTR("Brown-out");
        break;
      case 8:
        return PSTR("Watchdog");
        break;
      case 16:
        return PSTR("JTAG");
        break;
      default:
        return PSTR("Unknown Cause Reset");
  }
}

int8_t ApioClass::getTemperature() {
  if (isExternalAref == false) {
    return HAL_MeasureTemperature() + tempOffset;
  } else {
    return -127;
  }
}

int8_t ApioClass::getTemperatureOffset(void) {
  return tempOffset;
}

void ApioClass::setTemperatureOffset(int8_t offset) {
  eeprom_update_byte((uint8_t *)8124, (uint8_t)offset);
  tempOffset = offset;
}

void ApioClass::setHQToken(const char *token) {
  for (int i=0; i<32; i++) {
    eeprom_update_byte((uint8_t *)8130+i, token[i]);
  }
}

void ApioClass::getHQToken(char *token) {
  for (int i=0; i<32; i++) {
    token[i] = eeprom_read_byte((uint8_t *)8130+i);
  }
}

void ApioClass::resetHQToken() {
  for (int i=0; i<32; i++) {
    eeprom_update_byte((uint8_t *)8130+i, 0xFF);
  }
}

void ApioClass::setOTAFlag() {
  eeprom_update_byte((uint8_t *)8125, 0x00);
}

uint32_t ApioClass::getHwSerial() {
  return eeprom_read_dword((uint32_t *)8184);
}

uint16_t ApioClass::getHwFamily() {
  return eeprom_read_word((uint16_t *)8188);
}

uint8_t ApioClass::getHwVersion() {
  return eeprom_read_byte((uint8_t *)8190);
}

uint8_t ApioClass::getEEPROMVersion() {
  return eeprom_read_byte((uint8_t *)8191);
}



void ApioClass::send(String message) {
  if(this->isDongle == 1){

    if(!nwkDataReqB)
    {
      int len;
      int flagReinvio = 0;
      if(message != ""){
        len = String(message).length(); //if i use toSend.toCharArray() the lwm packet do not get good
        //Serial.print("Lunghezza:");
        //Serial.println(len);
        //Serial.println("Il messaggio è");
        //Serial.println(String(message));
        flagReinvio = 1;
        //FIX HERE
        //codaInvio = message;
        char sendThis[len];
        //sendTo="0";
        for(int g=0; g<len ;g++)
        {
            sendThis[g]=message.charAt(g);
          //Serial.write(sendThis[g]);
        }
        a = message;
        sendTo = exSend;

      } else {
        flagNoLoop = 0;
        //Serial.println("Voglio inviare e sono un dongle");
        len = mex.length(); //if i use toSend.toCharArray() the lwm packet do not get good
        //Serial.print("Lunghezza:");
        //Serial.println(len);
        char sendThis[len];
        for(int g=0; g<len ;g++)
        {
            sendThis[g]=mex.charAt(g);
          //Serial.write(sendThis[g]);
        }
        a = mex;

      }
//        display.clearDisplay();
//        display.display();
//        display.setCursor(0,0);
//        display.println(mex);
//        display.setCursor(0,9);
//        display.println("SYS TO LWM");
//        display.display();

      //Serial.println(mex);
      this->nwkDataReqB = 1;
      if (!flagReinvio) exSend = sendTo;
      toSend.dstAddr = this->sendTo.toInt();
      //Serial.println(toSend.dstAddr);
      toSend.dstEndpoint = 1;
      toSend.srcEndpoint = 1;
      toSend.options = NWK_OPT_ACK_REQUEST|NWK_OPT_ENABLE_SECURITY;
      toSend.data = (uint8_t*)a.c_str();
      //Serial.println(toSend.data);
      toSend.size = len;
      toSend.confirm = appDataConf;
      NWK_DataReq(&toSend);
      mex = "";
      sendTo="";
    }

  } else {
    if(!nwkDataReqB)
    {
      //Serial.println("Voglio inviare e sono un dongle");
      int len = message.length(); //if i use toSend.toCharArray() the lwm packet do not get good
      //Serial.print("Lunghezza:");
      //Serial.println(len);
      //FIX HERE
      //codaInvio = message;
      char sendThis[len];
      sendTo="0";
      for(int g=0; g<len ;g++)
      {
          sendThis[g]=message.charAt(g);
        //Serial.write(sendThis[g]);
      }
      a = message;
//        display.clearDisplay();
//        display.display();
//        display.setCursor(0,0);
//        display.println(mex);
//        display.setCursor(0,9);
//        display.println("SYS TO LWM");
//        display.display();
      
      //Serial.println(mex);
      this->nwkDataReqB = 1;

      toSend.dstAddr = this->sendTo.toInt();
      //Serial.println(toSend.dstAddr);
      toSend.dstEndpoint = 1;
      toSend.srcEndpoint = 1;
      toSend.options = NWK_OPT_ACK_REQUEST|NWK_OPT_ENABLE_SECURITY;
      toSend.data = (uint8_t*)a.c_str();
      //Serial.println(toSend.data);
      toSend.size = len;
      toSend.confirm = appDataConf;
      NWK_DataReq(&toSend);
      mex = "";
    }



    //Serial.println("Voglio inviare e sono una general");

  }
  // TODO - Send state to HQ, and set pin values and pinmodes from response
}

void ApioClass::loadSettingsFromEeprom() {
  // Address 8124 - 1 byte   - Temperature offset
  // Address 8125 - 1 byte   - Initiate OTA flag
  // Address 8126 - 1 byte   - Data rate
  // Address 8127 - 3 bytes  - Torch color (R,G,B)
  // Address 8130 - 32 bytes - HQ Token
  // Address 8162 - 16 bytes - Security Key
  // Address 8178 - 1 byte   - Transmitter Power
  // Address 8179 - 1 byte   - Frequency Channel
  // Address 8180 - 2 bytes  - Network Identifier/Troop ID
  // Address 8182 - 2 bytes  - Network Address/Scout ID
  // Address 8184 - 4 bytes  - Unique ID
  // Address 8188 - 2 bytes  - HW family
  // Address 8190 - 1 byte   - HW Version
  // Address 8191 - 1 byte   - EEPROM Version
  byte buffer[32];


  //Questo l'HQToken non so cosa fa
  /*for (int i=0; i<32; i++) {
    buffer[i] = eeprom_read_byte((uint8_t *)8130+i);
  }
  setHQToken((char *)buffer);
  memset(buffer, 0x00, 32);

  //Non lo implementiamo

  for (int i=0; i<16; i++) {
    buffer[i] = eeprom_read_byte((uint8_t *)8162+i);
  }
  meshSetSecurityKey((uint8_t *)buffer);
  memset(buffer, 0x00, 16);*/



  /*
  if (eeprom_read_byte((uint8_t *)8178) != 0xFF) {
    meshSetPower(eeprom_read_byte((uint8_t *)8178));
  }
  if (eeprom_read_byte((uint8_t *)8126) != 0xFF) {
    meshSetDataRate(eeprom_read_byte((uint8_t *)8126));
  }
  if (eeprom_read_byte((uint8_t *)8124) != 0xFF) {
    tempOffset = (int8_t)eeprom_read_byte((uint8_t *)8124);
  }*/
}

void ApioClass::meshSetRadio(const uint16_t theAddress, const uint16_t thePanId, const uint8_t theChannel) {
  NWK_SetAddr(theAddress);
  address = theAddress;
  NWK_SetPanId(thePanId);
  panId = thePanId;
  meshSetChannel(theChannel);
  PHY_SetRxState(true);

  //eeprom_update_word((uint16_t *)8182, address);
  //eeprom_update_word((uint16_t *)8180, panId);

  //if (eeprom_read_byte((uint8_t *)8178) != 0xFF) {
  meshSetPower(0);
  meshSetDataRate(2);
}

void ApioClass::setPanId(int panId){
eeprom_update_word((uint16_t *)8180, panId);
}

void ApioClass::meshSetChannel(const uint8_t theChannel) {
  PHY_SetChannel(theChannel);
  channel = theChannel;
  //eeprom_update_byte((uint8_t *)8179, channel);
}

void ApioClass::meshSetPower(const uint8_t theTxPower) {
  /* Page 116 of the 256RFR2 datasheet
    0   3.5 dBm
    1   3.3 dBm
    2   2.8 dBm
    3   2.3 dBm
    4   1.8 dBm
    5   1.2 dBm
    6   0.5 dBm
    7  -0.5 dBm
    8  -1.5 dBm
    9  -2.5 dBm
    10 -3.5 dBm
    11 -4.5 dBm
    12 -6.5 dBm
    13 -8.5 dBm
    14 -11.5 dBm
    15 -16.5 dBm
  */
  PHY_SetTxPower(theTxPower);
  txPower = theTxPower;
  //eeprom_update_byte((uint8_t *)8178, theTxPower);
}

void ApioClass::meshSetDataRate(const uint8_t theRate) {
  /* Page 123 of the 256RFR2 datasheet
    0   250 kb/s  | -100 dBm
    1   500 kb/s  |  -96 dBm
    2   1000 kb/s |  -94 dBm
    3   2000 kb/s |  -86 dBm
  */
  TRX_CTRL_2_REG_s.oqpskDataRate = theRate;
  dataRate = theRate;
  //eeprom_update_byte((uint8_t *)8126, theRate);
}

void ApioClass::meshSetSecurityKey(const uint8_t *key) {
  NWK_SetSecurityKey((uint8_t *)key);

  /*for (int i=0; i<16; i++) {
    eeprom_update_byte((uint8_t *)8162+i, key[i]);
  }*/
}

void ApioClass::meshGetSecurityKey(char *key) {
  for (int i=0; i<16; i++) {
    key[i] = eeprom_read_byte((uint8_t *)8162+i);
  }
}

void ApioClass::meshResetSecurityKey(void) {
  const uint8_t buf[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  meshSetSecurityKey(buf);
}

void ApioClass::meshListen(uint8_t endpoint, bool (*handler)(NWK_DataInd_t *ind)) {
  NWK_OpenEndpoint(endpoint, handler);
}

void ApioClass::meshJoinGroup(uint16_t groupAddress) {
  //if (!NWK_GroupIsMember(groupAddress)) {
  //  NWK_GroupAdd(groupAddress);
  //}
}

void ApioClass::meshLeaveGroup(uint16_t groupAddress) {
  //if (NWK_GroupIsMember(groupAddress)) {
  //  NWK_GroupRemove(groupAddress);
  //}
}

bool ApioClass::meshIsInGroup(uint16_t groupAddress) {
  //return NWK_GroupIsMember(groupAddress);
}

uint16_t ApioClass::getAddress() {
  return address;
}

uint16_t ApioClass::getPanId() {
  return eeprom_read_word((uint16_t *)8180);
}

uint8_t ApioClass::getChannel() {
  return channel;
}

uint8_t ApioClass::getTxPower() {
  return txPower;
}

const char* ApioClass::getSketchName() {
  return sketchName;
}

const char* ApioClass::getSketchRevision() {
  return sketchRevision;
}

int32_t ApioClass::getSketchBuild() {
  return sketchBuild;
}

const char* ApioClass::getTxPowerDb() {
  switch (txPower) {
    case 0:
      return PSTR("3.5 dBm");
      break;
    case 1:
      return PSTR("3.3 dBm");
      break;
    case 2:
      return PSTR("2.8 dBm");
      break;
    case 3:
      return PSTR("2.3 dBm");
      break;
    case 4:
      return PSTR("1.8 dBm");
      break;
    case 5:
      return PSTR("1.2 dBm");
      break;
    case 6:
      return PSTR("0.5 dBm");
      break;
    case 7:
      return PSTR("-0.5 dBm");
      break;
    case 8:
      return PSTR("-1.5 dBm");
      break;
    case 9:
      return PSTR("-2.5 dBm");
      break;
    case 10:
      return PSTR("-3.5 dBm");
      break;
    case 11:
      return PSTR("-4.5 dBm");
      break;
    case 12:
      return PSTR("-6.5 dBm");
      break;
    case 13:
      return PSTR("-8.5 dBm");
      break;
    case 14:
      return PSTR("-11.5 dBm");
      break;
    case 15:
      return PSTR("-16.5 dBm");
      break;
    default:
      return PSTR("unknown");
      break;
  }
}

uint8_t ApioClass::getDataRate() {
  return dataRate;
}

const char* ApioClass::getDataRatekbps() {
  switch (dataRate) {
    case 0:
      return PSTR("250 kb/s");
      break;
    case 1:
      return PSTR("500 kb/s");
      break;
    case 2:
      return PSTR("1 Mb/s");
      break;
    case 3:
      return PSTR("2 Mb/s");
      break;
    default:
      return PSTR("unknown");
      break;
  }
}


////  l3032:RELE:1-
