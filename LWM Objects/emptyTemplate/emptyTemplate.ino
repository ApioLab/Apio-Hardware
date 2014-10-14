#include <Arduino.h>


//librerie per lwm
#include "lwm.h";
#include "lwm/sys/sys.h"
#include "lwm/nwk/nwk.h"

#include "ApioLwm.h"


void setup() {
  Serial1.begin(115200); //riga di debug
  apioSetup();
  apioSend("2:hi:2:l-");
}

void loop() {
  SYS_TaskHandler();
  select();
}

