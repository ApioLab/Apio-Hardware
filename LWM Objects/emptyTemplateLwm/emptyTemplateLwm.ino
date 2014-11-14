#include <Arduino.h>


//library for lwm

extern "C"{
#include <atmegarfr2.h>
#include <commands.h>
#include <config.h>
#include <hal.h>
#include <halBoard.h>
#include <halGpio.h>
#include <halLed.h>
#include <halSleep.h>
#include <halTimer.h>
#include <nwk.h>
#include <nwkCommand.h>
#include <nwkDataReq.h>
#include <nwkFrame.h>
#include <nwkGroup.h>
#include <nwkRoute.h>
#include <nwkRouteDiscovery.h>
#include <nwkRx.h>
#include <nwkSecurity.h>
#include <nwkTx.h>
#include <phy.h>
#include <sys.h>
#include <sysConfig.h>
#include <sysEncrypt.h>
#include <sysTimer.h>
#include <sysTypes.h>
}

#include <ApioLwm.h>

uint16_t object_address=34;
void setup() {
  Serial1.begin(9600); // debug
  Serial1.println("setup oggetto");

  apioSetup(object_address);
  

}

void loop() {
  Serial1.flush();
  SYS_TaskHandler();
  //select();
}

