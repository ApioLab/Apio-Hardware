#include <SPI.h>cd
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include <avr/wdt.h>
////// start oled display
/////RT for baudrate

////// end baudrate


#define OLED_RESET 6
Adafruit_SSD1306 display2(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

////// end of oled 


#include "Apio.h"
#include "property.h"
int pin20=14;
int pin21=15;
void setup() {
  wdt_disable();
pinMode(14,OUTPUT);
pinMode(15,OUTPUT);
/*
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display2.clearDisplay();
  display2.display();
  display2.setTextSize(0);
  display2.setTextColor(WHITE);
  display2.setCursor(27,0);
  display2.println("APIO srl");
  display2.setCursor(0,9);
  display2.println("Coordinatore V.1");
  display2.display();
  delay(500);
  display2.clearDisplay();
  display2.display();
  display2.setCursor(0,0);
  */
Apio.setup("Miiiio", "1,0", 0, 0x01);
wdt_enable(WDTO_4S);

//UBRR0H  = 0;
//UBRR0L  = 0;
	
}
int flagP = 0;
unsigned long previousM = 0;
unsigned long previousM1 = 0;
void loop(){
  Apio.loop();

  
  wdt_reset();	
}
