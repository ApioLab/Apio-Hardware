#include <XBee.h>

#include "luce.h"
#include "XBeeLib.h"


Output* lucePointer;
Output luce[1];



void setup(){
	Serial.begin(9600);
        xbee.setSerial(Serial);
	lucePointer=luce;
		luce[0].pin = 10;
	luce[0].valore = 0;
	pinMode(luce[0].pin, OUTPUT);
}

 void loop() {
   XBeeInput();
	if (proprieta=="onoff"){
	lucePointer=onoff(lucePointer,valore);
	proprieta="";
	}

	if (proprieta=="gioco"){
	lucePointer=gioco(lucePointer,valore);
	}

	if (proprieta=="intensita"){
	lucePointer=intensita(lucePointer,valore);
	proprieta="";
	}

}

