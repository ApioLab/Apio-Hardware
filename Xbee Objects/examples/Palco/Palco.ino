/* Welcome to DmxSimple. This library allows you to control DMX stage and
** architectural lighting and visual effects easily from Arduino. DmxSimple
** is compatible with the Tinker.it! DMX shield and all known DIY Arduino
** DMX control circuits.
**
** DmxSimple is available from: http://code.google.com/p/tinkerit/
** Help and support: http://groups.google.com/group/dmxsimple       */

/* To use DmxSimple, you will need the following line. Arduino will
** auto-insert it if you select Sketch > Import Library > DmxSimple. */
#include <Arduino.h>
#include "lwm.h";
#include "lwm/sys/sys.h"
#include "lwm/nwk/nwk.h"

#include "ApioLwm.h"
#include <DmxSimple.h>


int S;
int D;
int R;
int G;
int B;
int M;
void rgb(int shutter, int dimmer, int r, int g, int b, int macro)
{
    S=shutter;
    D=dimmer;  
    R=r;
    G=g;
    B=b;
    M=macro;
    DmxSimple.write(1, shutter);
    DmxSimple.write(2, dimmer);
    DmxSimple.write(3, r);
    DmxSimple.write(4, g);
    DmxSimple.write(5, b);
    DmxSimple.write(7, macro);
}
void setup() {
  apioSetup();
  apioSend("4:hi:4:l-");
  DmxSimple.usePin(2);
  DmxSimple.maxChannel(10);
  rgb(0,0,0,0,0,0);
}


void loop() {
  SYS_TaskHandler();
  select();
  if(proprieta=="shutter")
  {
    rgb(valore.toInt(),D,R,G,B,M);
  }
  if(proprieta=="dimmer")
  {
    rgb(S,valore.toInt(),R,G,B,M);
  }
  if(proprieta=="rosso")
  {
    rgb(S,D,valore.toInt(),G,B,M);
  }
  if(proprieta=="verde")
  {
    rgb(S,D,R,valore.toInt(),B,M);
  }
  if(proprieta=="blu")
  {
    rgb(S,D,R,G,valore.toInt(),M);
  }
  if(proprieta=="funzioni")
  {
    if(valore=="0") rgb(S,D,R,G,B,0);
    if(valore=="1") rgb(S,D,R,G,B,1);
    if(valore=="2") rgb(S,D,R,G,B,2);
    if(valore=="3") rgb(S,D,R,G,B,3);
    if(valore=="4") rgb(S,D,R,G,B,4);
    if(valore=="5") rgb(S,D,R,G,B,5);
    if(valore=="6") rgb(S,D,R,G,B,6);
    if(valore=="7") rgb(S,D,R,G,B,7);
    if(valore=="8") rgb(S,D,R,G,B,8);
    if(valore=="9") rgb(S,D,R,G,B,9);
  }  
  
  
}
