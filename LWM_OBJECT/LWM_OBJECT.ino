#include "Apio.h"
#include "property.h"
//Library for the watchdog
#include <avr/wdt.h>


void setup() {
  Apio.setup("", "1,0", 1, 0x01);
}
unsigned long previousMillis = 0;
void loop(){
	Apio.loop();
        if(millis()-previousMillis>5000){
          previousMillis=millis();
          Apio.send("1:onoff:0-");
        }
}
