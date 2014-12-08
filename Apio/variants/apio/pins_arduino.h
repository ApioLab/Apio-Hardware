/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            19//da controllare
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 24 : -1)//da controllare
#define digitalPinHasPWM(p)         ((p) == 2 || (p) == 3 || (p) == 4 || (p) == 5 || (p) == 21 || (p) == 22 || (p) == 23)


//che num associo: qual è la logica?


#define D0              0
#define D1              1  
#define D2              2
#define D3              3
#define D4              4
#define D5              5
#define D6              6
#define D7              7
#define D8              8
#define D9              9

#define A0              17
#define A1              16
#define A2              15
#define A3              14
#define A4              13
#define A5              12
#define A6              11
#define A7              10

#define RX1             18
#define TX1             19

// ~: PWM, *: external interrupt
// Pin num   Pin functions     Connected to / label on board
//RIGHT SIDE (keep usb down )
// D0:  PD6  T1                D0
// D1:  PD5  XCK1              D1
// D2:  PD0  INT0/SCL          D2
// D3:  PD1  INT1/SDA          D3
// D4:  PD7  T0                D4 
// D5:  PB0  SS/PCINT0         D5  
// D6:  PB7  OC0A/OC1C/PCINT7  D6~
// D7:  PB5  OC1A/PCINT5       D7~
// D8:  PB6  OC1B/PCINT6       D8~
// D9:  PB4                    D9~
//LEFT SIDE
// D10: PF7  ADC7/TDI          A7    
// D11: PF6  ADC6/TDO          A6  
// D12: PF5  ADC5/TMS          A5  
// D13: PF4  ADC4/TCK          A4
// D14: PF3  ADC3/DIG4         A3
// D15: PF2  ADC2/DIG2         A2
// D16: PF1  ADC1              A1
// D17: PF0  ADC0              A0
// D18: PD3  INT3/TXD1         TX1
// D19: PD2  INT2/RXD1         RX1


// These pins are not connected / don't have a pin
// number:
//...
//
// Interrupt mapping
//   Note that the interrupt numbers (as passed to attachInterrupt) do
//   _not_ correspond directly to the INTx values in the datasheet,
//   due to the way the Arduino core maps them (probably for backward
//   compatibility).
//
// Number  Pin          Datasheet name
//NO PIN INTERRUPT

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 24) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 24) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
  NOT_A_PORT,
  NOT_A_PORT,
  (uint16_t)&DDRB,
  NOT_A_PORT,
  (uint16_t)&DDRD,
  (uint16_t)&DDRE,
  (uint16_t)&DDRF,
  (uint16_t)&DDRG,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
  NOT_A_PORT,
  NOT_A_PORT,
  (uint16_t)&PORTB,
  NOT_A_PORT,
  (uint16_t)&PORTD,
  (uint16_t)&PORTE,
  (uint16_t)&PORTF,
  (uint16_t)&PORTG,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
  NOT_A_PORT,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
  NOT_A_PIN,
  NOT_A_PIN,
  (uint16_t)&PINB,
  NOT_A_PIN,
  (uint16_t)&PIND,
  (uint16_t)&PINE,
  (uint16_t)&PINF,
  (uint16_t)&PING,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
  NOT_A_PIN,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
  /*  D0: */ PD,
  /*  D1: */ PD,
  /*  D2: */ PD,
  /*  D3: */ PD,
  /*  D4: */ PD,
  /*  D5: */ PB,
  /*  D6: */ PB,
  /*  D7: */ PB,
  /*  D8: */ PB,
  /*  D9: */ PB,
  /* D10: */ PF,
  /* D11: */ PF,
  /* D12: */ PF,
  /* D13: */ PF,
  /* D14: */ PF,
  /* D15: */ PF,
  /* D16: */ PF,
  /* D17: */ PF,
  /* D18: */ PD,
  /* D19: */ PD,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
  /*  D0: */ _BV(PD6),
  /*  D1: */ _BV(PD5),
  /*  D2: */ _BV(PD0),
  /*  D3: */ _BV(PD1),
  /*  D4: */ _BV(PD7),
  /*  D5: */ _BV(PB0),
  /*  D6: */ _BV(PB7),
  /*  D7: */ _BV(PB5),
  /*  D8: */ _BV(PB6),
  /*  D9: */ _BV(PB4),
  /* D10: */ _BV(PF7),
  /* D11: */ _BV(PF6),
  /* D12: */ _BV(PF5),
  /* D13: */ _BV(PF4),
  /* D14: */ _BV(PF3),
  /* D15: */ _BV(PF2),
  /* D16: */ _BV(PF1),
  /* D17: */ _BV(PF0),
  /* D18: */ _BV(PD3),
  /* D19: */ _BV(PD2),

};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
  /*  D0: */ NOT_ON_TIMER,
  /*  D1: */ NOT_ON_TIMER,
  /*  D2: */ NOT_ON_TIMER,
  /*  D3: */ NOT_ON_TIMER,
  /*  D4: */ NOT_ON_TIMER,
  /*  D5: */ NOT_ON_TIMER,
  /*  D6: */ TIMER0A,
  /*  D7: */ TIMER1A,
  /*  D8: */ TIMER1B,
  /*  D9: */ TIMER2A,
  /* D10: */ NOT_ON_TIMER,
  /* D11: */ NOT_ON_TIMER,
  /* D12: */ NOT_ON_TIMER,
  /* D13: */ NOT_ON_TIMER,
  /* D14: */ NOT_ON_TIMER,
  /* D15: */ NOT_ON_TIMER,
  /* D16: */ NOT_ON_TIMER,
  /* D17: */ NOT_ON_TIMER,
  /* D18: */ NOT_ON_TIMER,
  /* D19: */ NOT_ON_TIMER,
};

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR         Serial
#define SERIAL_PORT_HARDWARE        Serial
#define SERIAL_PORT_HARDWARE1       Serial1
//#define SERIAL_PORT_HARDWARE2       Serial2
//#define SERIAL_PORT_HARDWARE3       Serial3
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
//#define SERIAL_PORT_HARDWARE_OPEN1  Serial2
//#define SERIAL_PORT_HARDWARE_OPEN2  Serial3

#endif