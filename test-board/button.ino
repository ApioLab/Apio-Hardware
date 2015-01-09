#include "communicationLibraries"
#define BUTTON 1

void setup(){
	apioSetup(2);
	pinMode(BUTTON, INPUT);
}
int previousButtonState;
void loop(){
    apioLoop();
    int buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) 
  {
  	if(previousButtonState!=buttonState)
  	{
  		apioSend("4:update:button:1-");
  		previousButtonState=buttonState;
  	}
  }
  //if the button is not pressed
  //buttonState is LOW
  else if(buttonState == LOW)
  {
  	if(previousButtonState!=buttonState)
  	{
  		apioSend("4:update:button:0-");
  		previousButtonState=buttonState;
	}
  }
}
