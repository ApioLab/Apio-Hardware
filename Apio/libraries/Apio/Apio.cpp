/**************************************************************************\
* Apio Library                                                         *
* https://github.com/ApioLab/library                                   *
* Copyright (c) 2014-2015, Apio s.r.l. All rights reserve              *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the BSD License as described in license.txt.         *
\**************************************************************************/
#include <Arduino.h>
#include <Apio.h>
#include <avr/eeprom.h>
#include <src/bitlash.h>
#include <lwm/phy/atmegarfr2.h>

ApioClass::ApioClass() {
  // this has to be called as early as possible before other code uses the register
  lastResetCause = GPIOR0;
}

ApioClass::~ApioClass() { }

void ApioClass::setup(const char *sketchName, const char *sketchRevision, int32_t sketchBuild) {
  this->sketchName = sketchName;
  this->sketchRevision = sketchRevision;
  this->sketchBuild = sketchBuild;

  SYS_Init();
  PHY_RandomReq();

  digitalWrite(SS, HIGH);
  pinMode(SS, OUTPUT);

  loadSettingsFromEeprom();
}

void ApioClass::loop() {
  SYS_TaskHandler();
}

void ApioClass::goToSleep(uint32_t sleepForMs) {
  // TODO  http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=136036
  // - put radio to sleep
  // - set all GPIO pins to inputs
  // - turn off ADC
  // - turn off backpack power
  // - put MCU to sleep
}

void ApioClass::enableExternalAref() {
  isExternalAref = true;
  analogReference(EXTERNAL);
}

void ApioClass::disableExternalAref() {
  isExternalAref = false;
  ADMUX = (1 << REFS1) | (1 << REFS0); // 1.6V internal voltage ref.
}

bool ApioClass::getExternalAref() {
  return isExternalAref;
}

const char* ApioClass::getLastResetCause() {
  switch (lastResetCause) {
      case 1:
        return PSTR("Power-on");
        break;
      case 2:
        return PSTR("External");
        break;
      case 4:
        return PSTR("Brown-out");
        break;
      case 8:
        return PSTR("Watchdog");
        break;
      case 16:
        return PSTR("JTAG");
        break;
      default:
        return PSTR("Unknown Cause Reset");
  }
}

int8_t ApioClass::getTemperature() {
  if (isExternalAref == false) {
    return HAL_MeasureTemperature();
  } else {
    return -127;
  }
}

void ApioClass::setHQToken(const char *token) {
  for (int i=0; i<32; i++) {
    eeprom_update_byte((uint8_t *)8130+i, token[i]);
  }
}

void ApioClass::getHQToken(char *token) {
  for (int i=0; i<32; i++) {
    token[i] = eeprom_read_byte((uint8_t *)8130+i);
  }
}

void ApioClass::resetHQToken() {
  for (int i=0; i<32; i++) {
    eeprom_update_byte((uint8_t *)8130+i, 0xFF);
  }
}

void ApioClass::setOTAFlag() {
  eeprom_update_byte((uint8_t *)8125, 0x00);
}

uint32_t ApioClass::getHwSerial() {
  return eeprom_read_dword((uint32_t *)8184);
}

uint16_t ApioClass::getHwFamily() {
  return eeprom_read_word((uint16_t *)8188);
}

uint8_t ApioClass::getHwVersion() {
  return eeprom_read_byte((uint8_t *)8190);
}

uint8_t ApioClass::getEEPROMVersion() {
  return eeprom_read_byte((uint8_t *)8191);
}

void ApioClass::sendStateToHQ() {
  // TODO - Send state to HQ, and set pin values and pinmodes from response
}

void ApioClass::loadSettingsFromEeprom() {
  // Address 8125 - 1 byte   - Initiate OTA flag
  // Address 8126 - 1 byte   - Data rate
  // Address 8127 - 3 bytes  - Torch color (R,G,B)
  // Address 8130 - 32 bytes - HQ Token
  // Address 8162 - 16 bytes - Security Key
  // Address 8178 - 1 byte   - Transmitter Power
  // Address 8179 - 1 byte   - Frequency Channel
  // Address 8180 - 2 bytes  - Network Identifier/Troop ID
  // Address 8182 - 2 bytes  - Network Address/Scout ID
  // Address 8184 - 4 bytes  - Unique ID
  // Address 8188 - 2 bytes  - HW family
  // Address 8190 - 1 byte   - HW Version
  // Address 8191 - 1 byte   - EEPROM Version
  byte buffer[32];

  for (int i=0; i<32; i++) {
    buffer[i] = eeprom_read_byte((uint8_t *)8130+i);
  }
  setHQToken((char *)buffer);
  memset(buffer, 0x00, 32);

  for (int i=0; i<16; i++) {
    buffer[i] = eeprom_read_byte((uint8_t *)8162+i);
  }
  meshSetSecurityKey((uint8_t *)buffer);
  memset(buffer, 0x00, 16);

  if (eeprom_read_word((uint16_t *)8182) != 0xFFFF ||
      eeprom_read_word((uint16_t *)8180) != 0xFFFF ||
      eeprom_read_byte((uint8_t *)8179) != 0xFF) {
    meshSetRadio(eeprom_read_word((uint16_t *)8182), eeprom_read_word((uint16_t *)8180), eeprom_read_byte((uint8_t *)8179));
  }
  if (eeprom_read_byte((uint8_t *)8178) != 0xFF) {
    meshSetPower(eeprom_read_byte((uint8_t *)8178));
  }
  if (eeprom_read_byte((uint8_t *)8126) != 0xFF) {
    meshSetDataRate(eeprom_read_byte((uint8_t *)8126));
  }
}

void ApioClass::meshSetRadio(const uint16_t theAddress, const uint16_t thePanId, const uint8_t theChannel) {
  NWK_SetAddr(theAddress);
  address = theAddress;
  NWK_SetPanId(thePanId);
  panId = thePanId;
  PHY_SetChannel(theChannel);
  channel = theChannel;
  PHY_SetRxState(true);

  eeprom_update_word((uint16_t *)8182, address);
  eeprom_update_word((uint16_t *)8180, panId);
  eeprom_update_byte((uint8_t *)8179, channel);

  if (eeprom_read_byte((uint8_t *)8178) != 0xFF) {
    meshSetPower(eeprom_read_byte((uint8_t *)8178));
  }else{
    meshSetPower(0);
  }
  if (eeprom_read_byte((uint8_t *)8126) != 0xFF) {
    meshSetDataRate(eeprom_read_byte((uint8_t *)8126));
  }else{
    meshSetDataRate(0);
  }

}


void ApioClass::meshSetPower(const uint8_t theTxPower) {
  /* Page 116 of the 256RFR2 datasheet
    0   3.5 dBm
    1   3.3 dBm
    2   2.8 dBm
    3   2.3 dBm
    4   1.8 dBm
    5   1.2 dBm
    6   0.5 dBm
    7  -0.5 dBm
    8  -1.5 dBm
    9  -2.5 dBm
    10 -3.5 dBm
    11 -4.5 dBm
    12 -6.5 dBm
    13 -8.5 dBm
    14 -11.5 dBm
    15 -16.5 dBm
  */
  PHY_SetTxPower(theTxPower);
  txPower = theTxPower;
  eeprom_update_byte((uint8_t *)8178, theTxPower);
}

void ApioClass::meshSetDataRate(const uint8_t theRate) {
  /* Page 123 of the 256RFR2 datasheet
    0   250 kb/s  | -100 dBm
    1   500 kb/s  |  -96 dBm
    2   1000 kb/s |  -94 dBm
    3   2000 kb/s |  -86 dBm
  */
  TRX_CTRL_2_REG_s.oqpskDataRate = theRate;
  dataRate = theRate;
  eeprom_update_byte((uint8_t *)8126, theRate);
}

void ApioClass::meshSetSecurityKey(const uint8_t *key) {
  NWK_SetSecurityKey((uint8_t *)key);

  for (int i=0; i<16; i++) {
    eeprom_update_byte((uint8_t *)8162+i, key[i]);
  }
}

void ApioClass::meshGetSecurityKey(char *key) {
  for (int i=0; i<16; i++) {
    key[i] = eeprom_read_byte((uint8_t *)8162+i);
  }
}

void ApioClass::meshResetSecurityKey(void) {
  const uint8_t buf[16] = {0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};
  meshSetSecurityKey(buf);
}

void ApioClass::meshListen(uint8_t endpoint, bool (*handler)(NWK_DataInd_t *ind)) {
  NWK_OpenEndpoint(endpoint, handler);
}

void ApioClass::meshJoinGroup(uint16_t groupAddress) {
  if (!NWK_GroupIsMember(groupAddress)) {
    NWK_GroupAdd(groupAddress);
  }
}

void ApioClass::meshLeaveGroup(uint16_t groupAddress) {
  if (NWK_GroupIsMember(groupAddress)) {
    NWK_GroupRemove(groupAddress);
  }
}

bool ApioClass::meshIsInGroup(uint16_t groupAddress) {
  return NWK_GroupIsMember(groupAddress);
}

uint16_t ApioClass::getAddress() {
  return address;
}

uint16_t ApioClass::getPanId() {
  return panId;
}

uint8_t ApioClass::getChannel() {
  return channel;
}

uint8_t ApioClass::getTxPower() {
  return txPower;
}

const char* ApioClass::getSketchName() {
  return sketchName;
}

const char* ApioClass::getSketchRevision() {
  return sketchRevision;
}

int32_t ApioClass::getSketchBuild() {
  return sketchBuild;
}

const char* ApioClass::getTxPowerDb() {
  switch (txPower) {
    case 0:
      return PSTR("3.5 dBm");
      break;
    case 1:
      return PSTR("3.3 dBm");
      break;
    case 2:
      return PSTR("2.8 dBm");
      break;
    case 3:
      return PSTR("2.3 dBm");
      break;
    case 4:
      return PSTR("1.8 dBm");
      break;
    case 5:
      return PSTR("1.2 dBm");
      break;
    case 6:
      return PSTR("0.5 dBm");
      break;
    case 7:
      return PSTR("-0.5 dBm");
      break;
    case 8:
      return PSTR("-1.5 dBm");
      break;
    case 9:
      return PSTR("-2.5 dBm");
      break;
    case 10:
      return PSTR("-3.5 dBm");
      break;
    case 11:
      return PSTR("-4.5 dBm");
      break;
    case 12:
      return PSTR("-6.5 dBm");
      break;
    case 13:
      return PSTR("-8.5 dBm");
      break;
    case 14:
      return PSTR("-11.5 dBm");
      break;
    case 15:
      return PSTR("-16.5 dBm");
      break;
    default:
      return PSTR("unknown");
      break;
  }
}

uint8_t ApioClass::getDataRate() {
  return dataRate;
}

const char* ApioClass::getDataRatekbps() {
  switch (dataRate) {
    case 0:
      return PSTR("250 kb/s");
      break;
    case 1:
      return PSTR("500 kb/s");
      break;
    case 2:
      return PSTR("1 Mb/s");
      break;
    case 3:
      return PSTR("2 Mb/s");
      break;
    default:
      return PSTR("unknown");
      break;
  }
}
