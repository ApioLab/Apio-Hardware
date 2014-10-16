#include <XBee.h>
#include "ApioXBee.h"




void setup()  
{ 
  Serial.begin(9600);
  apioSetupMega();
  //Here we assume that the objectID is 4545 and physical address is 40B3E1D4
  apioSend("4545:hi:40B3E1D4:z-"); //Send init for my object

} 

void loop()  
{
  //This is the function that we call in each loop and let you receive key value
  apioReceive();
  ///Azioni che devono generare un output.
  
  /*---------------------------*/
  //Azioni che provengono dagli Input
 
}
