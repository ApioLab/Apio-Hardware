/**************************************************************************\
* Apio Library                                                         *
* https://github.com/ApioLab/library                                   *
* Copyright (c) 2012-2014, Apio s.r.l. All rights reserved.            *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the BSD License as described in license.txt.         *
\**************************************************************************/

#ifndef LIB_Apio_H_
#define LIB_Apio_H_

//#define Apio_DEBUG
#ifdef Apio_DEBUG
#  define D(x) x
#else
#  define D(x)
#endif

#include <Arduino.h>

#include "atmegarfr2.h"
#include "config.h"
#include "hal.h"
#include "halTimer.h"
#include "nwk.h"
#include "nwkCommand.h"
#include "nwkDataReq.h"
#include "nwkFrame.h"
#include "nwkGroup.h"
#include "nwkRoute.h"
#include "nwkRouteDiscovery.h"
#include "nwkRx.h"
#include "nwkSecurity.h"
#include "nwkTx.h"
#include "phy.h"
#include "sys.h"
#include "sysConfig.h"
#include "sysEncrypt.h"
#include "sysTimer.h"
#include "sysTypes.h"


class ApioClass {

  public:
    ApioClass();
    ~ApioClass();

    void setup(const char *sketchName, const char *sketchRevision, int32_t sketchBuild);
    void loop();

    void goToSleep(uint32_t sleepForMs);

    int8_t getTemperature();
    void enableExternalAref();
    void disableExternalAref();
    bool getExternalAref();

    const char* getLastResetCause();
    void loadSettingsFromEeprom();

    void setHQToken(const char *token);
    void getHQToken(char *token);
    void resetHQToken();
    void setOTAFlag();

    uint32_t getHwSerial();
    uint16_t getHwFamily();
    uint8_t getHwVersion();
    uint8_t getEEPROMVersion();

    void sendStateToHQ();

    void meshSetRadio(const uint16_t theAddress, const uint16_t thePanId=0x4567, const uint8_t theChannel=20);
    void meshSetPower(const uint8_t theTxPower);
    void meshSetDataRate(const uint8_t theRate);
    void meshSetSecurityKey(const uint8_t *key);
    void meshGetSecurityKey(char *key);
    void meshResetSecurityKey(void);
    void meshListen(uint8_t endpoint, bool (*handler)(NWK_DataInd_t *ind));

    void meshJoinGroup(uint16_t groupAddress);
    void meshLeaveGroup(uint16_t groupAddress);
    bool meshIsInGroup(uint16_t groupAddress);

    uint16_t getAddress();
    uint16_t getPanId();
    uint8_t getChannel();
    uint8_t getTxPower();
    const char* getTxPowerDb();
    uint8_t getDataRate();
    const char* getDataRatekbps();

    const char* getSketchName();
    const char* getSketchRevision();
    int32_t getSketchBuild();

  protected:
    void convertLongToBytes(byte *convBytes, uint32_t target);
    uint32_t convertBytesToLong(byte *convBytes);

    bool isExternalAref;
    uint8_t lastResetCause;
    uint16_t address;
    uint16_t panId;
    uint8_t channel;
    uint8_t txPower;
    uint8_t dataRate;

    // Name of the sketch (e.g. "Bootstrap")
    const char* sketchName;
    // Detailed revision of the sketch (e.g. "2014031902-1-g5579a21-dirty")
    const char* sketchRevision;
    // Released build number, or -1 for custom builds
    int32_t sketchBuild;
};

#endif