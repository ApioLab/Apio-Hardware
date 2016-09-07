/*
Ruiz Tech 
Library to MCP3424 ADC 18Bit

*/

//#ifndef MCP3424_h
//#define MCP3424_h

#include <Arduino.h>

#define MCP3424_ADDRESS 0X69
#define MCP3424_ADDRESS2 0X6A

// Define configuration register bits and addresses
#define MCP342X_GAIN_FIELD 0X03 // PGA field
#define MCP342X_GAIN_X1    0X00 // PGA gain X1
#define MCP342X_GAIN_X2    0X01 // PGA gain X2
#define MCP342X_GAIN_X4    0X02 // PGA gain X4
#define MCP342X_GAIN_X8    0X03 // PGA gain X8

#define MCP342X_RES_FIELD  0X0C // resolution/rate field
#define MCP342X_RES_SHIFT  2    // shift to low bits
#define MCP342X_12_BIT     0X00 // 12-bit 240 SPS
#define MCP342X_14_BIT     0X04 // 14-bit 60 SPS
#define MCP342X_16_BIT     0X08 // 16-bit 15 SPS
#define MCP342X_18_BIT     0X0C // 18-bit 3.75 SPS

#define MCP342X_CONTINUOUS 0X10 // 1 = continuous, 0 = one-shot

#define MCP342X_CHAN_FIELD 0X60 // channel field
#define MCP342X_CHANNEL_1  0X00 // select MUX channel 1
#define MCP342X_CHANNEL_2  0X20 // select MUX channel 2
#define MCP342X_CHANNEL_3  0X40 // select MUX channel 3
#define MCP342X_CHANNEL_4  0X60 // select MUX channel 4

#define MCP342X_START      0X80 // write: start a conversion
#define MCP342X_BUSY       0X80 // read: output not ready


// constructor
class ADCRT3424
{
  public:
     // constructor
     ADCRT3424(byte address, byte gain, byte res);
     // functions
     void ADCRT3424Write(byte msg);
     int getMvDivisor();
     long readData();
     void setChannel(byte chan);
     double getChannelmV(byte chan);
     double getChannelV(byte chan);
     // variables
     //int MCP3424_ADDRESS;
     byte adcConfig;
     uint16_t mvDivisor;
  private:
     // private variables
     byte _address;
     byte _res;
     byte _gain;
     int _rtaddr;

};

//#endif

