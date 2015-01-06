
#include "atmegarfr2.h"
#include "config.h"
#include "hal.h"
#include "halTimer.h"
#include "nwk.h"
#include "nwkCommand.h"
#include "nwkDataReq.h"
#include "nwkFrame.h"
#include "nwkGroup.h"
#include "nwkRoute.h"
#include "nwkRouteDiscovery.h"
#include "nwkRx.h"
#include "nwkSecurity.h"
#include "nwkTx.h"
#include "phy.h"
#include "sys.h"
#include "sysConfig.h"
#include "sysEncrypt.h"
#include "sysTimer.h"
#include "sysTypes.h"
#include "apioGeneral.h"

#include "ApioLwm.h"

void setup() {
  apioSetup(16);
  pinMode(20,OUTPUT);
  pinMode(21,OUTPUT);
  generalSetup();
}

void loop(){
	apioLoop();
        if(property=="onoff")
        {
          if(value=="1")
          {
            digitalWrite(20,HIGH);
          }
          if(value=="0")
          {
            digitalWrite(20,LOW);
          }
        }
        if(property=="onoff1")
        {
          if(value=="1")
          {
            digitalWrite(21,HIGH);
          }
          if(value=="0")
          {
            digitalWrite(21,LOW);
          }
        }
}
