#include <Arduino.h>
//library for lwm

//Library for the Lwm
#include "lwm.h"
#include "lwm/phy/atmegarfr2.h"
#include "lwm/hal/hal.h"
#include "lwm/hal/halTimer.h"
#include "lwm/nwk/nwk.h"
#include "lwm/nwk/nwkCommand.h"
#include "lwm/nwk/nwkDataReq.h"
#include "lwm/nwk/nwkFrame.h"
#include "lwm/nwk/nwkGroup.h"
#include "lwm/nwk/nwkRoute.h"
#include "lwm/nwk/nwkRouteDiscovery.h"
#include "lwm/nwk/nwkRx.h"
#include "lwm/nwk/nwkSecurity.h"
#include "lwm/nwk/nwkTx.h"
#include "lwm/phy/phy.h"
#include "lwm/sys/sys.h"
#include "lwm/sys/sysConfig.h"
#include "lwm/sys/sysEncrypt.h"
#include "lwm/sys/sysTimer.h"
#include "lwm/sys/sysTypes.h"

#include <ApioLwm.h>


void setup() {
  Serial.begin(115200); // debug
  Serial.println("setup oggetto");

  apioSetup();
  

}

void loop() {
  Serial.flush();
  SYS_TaskHandler();
  select();
}

