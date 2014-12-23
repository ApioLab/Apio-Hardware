#include "XBee.h"
#include "ApioXbee.h"




void setup()  
{ 
  Serial.begin(9600);
  apioSetup();


} 

void loop()  
{
  //This function provide in every loop a property and a  value
  //this variables come from the gesture over interface.
  apioLoop();
  
  //Action that generates OUTPUT (if (property==...){...})
  
  /*---------------------------*/
  //Action from INPUT  
  

}
