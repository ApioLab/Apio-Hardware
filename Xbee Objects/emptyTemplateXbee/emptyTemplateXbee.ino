#include <XBee.h>
#include <ApioXbee.h>




void setup()  
{ 
  Serial.begin(9600);
  apioSetup();


} 

void loop()  
{
  apioLoop();
  
  ///Azioni che devono generare un output.
  
  /*---------------------------*/
  //Azioni che provengono dagli Input
  
  

}
