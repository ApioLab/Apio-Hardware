/**
 *  Modbus master example 1:
 *  The purpose of this example is to query an array of data
 *  from an external Modbus slave device. 
 *  The link media can be USB or RS232.
 *
 *  Recommended Modbus slave: 
 *  diagslave http://www.modbusdriver.com/diagslave.html
 *
 *  In a Linux box, run 
 *  "./diagslave /dev/ttyUSB0 -b 19200 -d 8 -s 1 -p none -m rtu -a 1"
 * 	This is:
 * 		serial port /dev/ttyUSB0 at 19200 baud 8N1
 *		RTU mode and address @1
 */

#include <ModbusRtu.h>

// data array for modbus network sharing
uint16_t au16data[16];
uint8_t u8state;

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  u8serno : serial port (use 0 for Serial)
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus master(0,1,0); // this is master and RS-232 or USB-FTDI

/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram;

unsigned long u32wait;

void setup() {
  Serial.begin(115200);
  master.begin( 9600 ); // baud-rate at 19200
  master.setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    telegram.u8id = 1; // slave address
    telegram.u8fct = 4; // function code (this one is registers read)
    telegram.u16RegAdd = 0; // start address in slave
    telegram.u16CoilsNo = 2; // number of elements (coils or registers) to read
    telegram.au16reg = au16data; // pointer to a memory array in the Arduino
   
    master.query( telegram ); // send query (only once)
    Serial.print(telegram.au16reg[0]); 
      Serial.print(telegram.au16reg[1]); 
      Serial.print(telegram.au16reg[2]); 
      Serial.print(telegram.au16reg[3]);
      Serial.print(telegram.au16reg[4]);
      Serial.print(telegram.au16reg[5]);
      Serial.print(telegram.au16reg[6]);
      Serial.print(telegram.au16reg[7]);
      Serial.print(telegram.au16reg[8]);
      Serial.print(telegram.au16reg[9]);
      Serial.print(telegram.au16reg[10]);
      Serial.print(telegram.au16reg[11]);
      Serial.print(telegram.au16reg[12]);
      Serial.print(telegram.au16reg[13]);
      Serial.print(telegram.au16reg[14]);
      Serial.println(telegram.au16reg[15]); 
    u8state++;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 100;
      Serial.print(telegram.au16reg[0]); 
      Serial.print(telegram.au16reg[1]); 
      Serial.print(telegram.au16reg[2]); 
      Serial.print(telegram.au16reg[3]);
      Serial.print(telegram.au16reg[4]);
      Serial.print(telegram.au16reg[5]);
      Serial.print(telegram.au16reg[6]);
      Serial.print(telegram.au16reg[7]);
      Serial.print(telegram.au16reg[8]);
      Serial.print(telegram.au16reg[9]);
      Serial.print(telegram.au16reg[10]);
      Serial.print(telegram.au16reg[11]);
      Serial.print(telegram.au16reg[12]);
      Serial.print(telegram.au16reg[13]);
      Serial.print(telegram.au16reg[14]);
      Serial.println(telegram.au16reg[15]); 
      
    }
    break;
  }
}






