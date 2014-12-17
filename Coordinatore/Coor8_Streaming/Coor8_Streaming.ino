//Library for the watchdog
#include <avr/wdt.h>


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

//Library for the Xbee
#include <XBee.h>


#include "coordinatore.h"


void setup() {
  wdt_disable();
 /*--------------------------------------------------------------------*/ 
 ApioCoordinatorSetup(); //inizializzazione coordinatore
  
 /*--------------------------------------------------------------------*/  
  wdt_enable(WDTO_8S);
}

// the loop routine runs over and over again forever:
void loop() {
  SYS_TaskHandler(); //task management LWM
  
  if(Serial.available()>0)
  {
      comunication_protocol = ReadFromWebServer();
              
        switch(comunication_protocol)
        {
          case('z'):
            //Serial1.println("case z"); //debug
            XBeeOutput(); 
          break;
        
          case('l'):
            //Serial1.println("case l"); //debug
            LwmOutput();
            
          break;
        }
        
    content="";
    deviceAddr="";
    comunication_protocol=NULL;
        
   }    



 /*--------------------------------------------------------------------*/ 
  wdt_reset(); //watchdog reset
}
