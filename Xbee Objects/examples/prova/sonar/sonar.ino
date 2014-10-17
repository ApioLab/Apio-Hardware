#define trigPin 3
#define echoPin 2
#include <XBee.h>
#include "XBeeLib.h"


void setup() {
  Serial1.begin (9600);
  xbee.setSerial(Serial1);
}

void loop() {
      XBeeSend("1234:send:onoff:1:");
      delay(10000);

}
