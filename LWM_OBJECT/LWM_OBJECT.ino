
#include "Apio.h"
#include "property.h"
int pin20=20;
int pin21=21;
void setup() {
	Apio.setup("Miiiio", "1,0", 18, 0x01);
	
}
void loop(){
	Apio.loop();
	
}
