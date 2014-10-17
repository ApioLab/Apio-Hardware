// Smart Remote Control Sketch
// Copyright 2014 Tony DiCola
// Released under an MIT license: http://opensource.org/licenses/MIT

// Based on examples from the IR remote library at: https://github.com/shirriff/Arduino-IRremote
// Depends on a fork of the library to fix a file name conflict in recent Arduino IDE releases.
// Download forked library from: https://github.com/tdicola/Arduino_IRremote

#include "IRremote_library.h"
#include "IRremoteInt_library.h"

// Pin connected to the IR receiver.
#define RECV_PIN 4

// Length of time to delay between codes.
#define REPEAT_DELAY_MS 40

// Size of parsing buffer.
#define BUFFER_SIZE 100

// Parsing state.
char buffer[BUFFER_SIZE+1] = {0};
int index = 0;
decode_results command;
unsigned int rawbuf[RAWBUF] = {4400, 4450, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 600, 500, 1700, 500, 600, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500, 1700, 500};

// Remote code types.
#define TYPE_COUNT 9
char* type_names[TYPE_COUNT] = { "NEC", "SONY", "RC5", "RC6", "DISH", "SHARP", "PANASONIC", "JVC", "RAW" };
int type_values[TYPE_COUNT] = { 1, 2, 3, 4, 5, 6, 7, 8, -1 };

// IR send and receive class.
IRsend irsend;
IRrecv irrecv(RECV_PIN);



// Setup function called once at bootup.
void setup() {
  // Initialize bridge, Serial, and IR receiver.
  Serial.begin(9600);
  irrecv.enableIRIn();
}

// Loop function called continuously.
void loop() {
  // Check if an IR code has been received and print it.
  decode_results results;
  if (irrecv.decode(&results)) {
    Serial.println("Decoded remote code:");
    print_code(&results);
    Serial.println("--------------------");
    delay(20);
    irrecv.resume();
  }
  // Wait a small amount so the Bridge library is not overwhelmed with requests to read the Serial.
  delay(10);
  if(Serial.available()>0)
  {
    Serial.println("Ciao");
    Serial.read();
    irsend.sendRaw(rawbuf, 148 , 38);
  }
}

// Send the parsed remote control command.
void send_command() {
  // Use the right send function depending on the command type.
  if (command.decode_type == NEC) {
    irsend.sendNEC(command.value, command.bits);
  }
  else if (command.decode_type == SONY) {
    // Sony codes are sent 3 times as a part of their protocol.
    for (int i = 0; i < 3; ++i) {
      irsend.sendSony(command.value, command.bits);
      delay(REPEAT_DELAY_MS);
    }
  }
  else if (command.decode_type == RC5) {
    // RC5 codes are sent 3 times as a part of their protocol.
    for (int i = 0; i < 3; ++i) {
      irsend.sendRC5(command.value, command.bits);
      delay(REPEAT_DELAY_MS);
    }
  }
  else if (command.decode_type == RC6) {
    // RC6 codes are sent 3 times as a part of their protocol.
    for (int i = 0; i < 3; ++i) {
      irsend.sendRC6(command.value, command.bits);
      delay(REPEAT_DELAY_MS);
    }
  }
  else if (command.decode_type == DISH) {
    irsend.sendDISH(command.value, command.bits);
  }
  else if (command.decode_type == SHARP) {
    irsend.sendSharp(command.value, command.bits);
  }
  else if (command.decode_type == PANASONIC) {
    irsend.sendPanasonic(command.panasonicAddress, command.value);
    delay(REPEAT_DELAY_MS);
  }
  else if (command.decode_type == JVC) {
    irsend.sendJVC(command.value, command.bits, 0);
  }
  else if (command.decode_type == UNKNOWN) {
    irsend.sendRaw(rawbuf, command.rawlen, 38);
  }
}

// Print received code to the Serial.
void print_code(decode_results *results) {
  if (results->decode_type == NEC) {
    Serial.print("NEC: ");
    Serial.print(results->bits, HEX);
    Serial.print(" ");
    Serial.println(results->value, HEX);
  } 
  else if (results->decode_type == SONY) {
    Serial.print("SONY: ");
    Serial.print(results->bits, HEX);
    Serial.print(" ");
    Serial.println(results->value, HEX);
  } 
  else if (results->decode_type == RC5) {
    Serial.print("RC5: ");
    Serial.print(results->bits, HEX);
    Serial.print(" ");
    Serial.println(results->value, HEX);
  } 
  else if (results->decode_type == RC6) {
    Serial.print("RC6: ");
    Serial.print(results->bits, HEX);
    Serial.print(" ");
    Serial.println(results->value, HEX);
  }
  else if (results->decode_type == PANASONIC) {	
    Serial.print("PANASONIC: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" ");
    Serial.println(results->value, HEX);
  }
  else if (results->decode_type == JVC) {
     Serial.print("JVC: ");
    Serial.print(results->bits, HEX);
    Serial.print(" ");
     Serial.println(results->value, HEX);
  }
  else {
    Serial.print("RAW: ");
    Serial.println(results->rawlen);
    for (int i = 1; i < results->rawlen; i++) {
      // Scale length to microseconds.
      unsigned int value = results->rawbuf[i]*USECPERTICK;
      // Adjust length based on error in IR receiver measurement time.
      if (i % 2) {
        value -= MARK_EXCESS;
      }
      else {
        value += MARK_EXCESS;
      }
      // Print mark/space length.
      Serial.print(value);
      Serial.print(", ");
    }
    Serial.println("}");
  }
}

// Grab the currently parsed word and clear the buffer.
char* current_word() {
  buffer[index] = 0;
  index = 0;
  return buffer;
}


