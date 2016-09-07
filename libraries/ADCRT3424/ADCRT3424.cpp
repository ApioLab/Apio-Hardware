/*
Ruiz Tech 
Library to MCP3424 ADC 18Bit
	
- gain values 0-3 represent {x1,x2,x4,x8}
- resolution 0-3 represents {12bits, 14bits, 16bits, 18bits}
*/

#include <Arduino.h>
#include <Wire.h>
#include "ADCRT3424.h"

// constructor takes I2C address, required channel, gain and resolution and configures chip.
ADCRT3424::ADCRT3424(byte address, byte gain, byte res)
{ 
   _address = address;
   _gain = gain;
   _res = res;
   _rtaddr = address;
}


// function sets channel
void ADCRT3424::setChannel(byte chan) 
{
  byte adcConfig = MCP342X_START | MCP342X_CHANNEL_1 | MCP342X_CONTINUOUS;
  adcConfig |= chan << 5 | _res << 2 | _gain;
  ADCRT3424Write(adcConfig);
}


// calculate and return mV devisor from gain and resolution.
int ADCRT3424::getMvDivisor()
{
  int mvDivisor = 1 << (_gain + 2*_res);
  return mvDivisor;
}

// Write byte to register on MCP3424
void ADCRT3424::ADCRT3424Write(byte msg) // address needs to be hardcoded or doesn't work
{
 //Serial.println(_address,HEX);
 Wire.beginTransmission(_address);
 Wire.write(msg);
 Wire.endTransmission(); 
  
}

long ADCRT3424::readData()
{
  long data;
  // pointer used to form int32 data
  byte *p = (byte *)&data;
  // timeout - not really needed?
  long start = millis();
  do {
    // assume 18-bit mode
    Wire.requestFrom(_rtaddr, 4);
    //Serial.println(Wire.available());
    if (Wire.available() != 4) {
      Serial.println("read failed");
      return false;
    }
    for (int i = 2; i >= 0; i--) {
      p[i] = Wire.read();
    }
    // extend sign bits
    p[3] = p[2] & 0X80 ? 0XFF : 0;
    // read config/status byte
    byte s = Wire.read();
    if ((s & MCP342X_RES_FIELD) != MCP342X_18_BIT) {
      // not 18 bits - shift bytes for 12, 14, or 16 bits
      p[0] = p[1];
      p[1] = p[2];
      p[2] = p[3];
    }
    if ((s & MCP342X_BUSY) == 0) return data;
  }
  while (millis() - start < 500); //allows rollover of millis()
  Serial.println("read timeout"); 
  return false; 
}

double ADCRT3424::getChannelmV(byte chan)
{
  long data;
  setChannel(chan);
  int mvDivisor = getMvDivisor();
    if (readData()!=0){
    data = readData();
    }
    else Serial.println("Read error");
    
  double mv = (double)data/mvDivisor;
  return mv;
}

double ADCRT3424::getChannelV(byte chan)
{
  /*long data;
  setChannel(chan);
  int mvDivisor = getMvDivisor();
    if (readData()!=0){
    data = readData();
    //Serial.println("Dentro get ChannelV");
    //Serial.println(data);
    }
    else Serial.println("Read error");
    
  double mv = (double)data/mvDivisor * 0.005456766; /// /100 To convert in volt
  //Serial.println(mv);
  return data;
  */
  long data;
  setChannel(chan);
  int mvDivisor = getMvDivisor();
  data = readData();
  if(data==0) Serial.println("Read error");
  double mv = (double)data/mvDivisor * 0.005456766;
  return data;
}


