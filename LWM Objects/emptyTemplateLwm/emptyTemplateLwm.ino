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

uint16_t object_address=34;

void setup() {
//  Serial1.begin(9600); // debug
//  Serial1.println("object setup ");
  apioSetup(object_address);
}

void loop() { 
  apioLoop();
}

