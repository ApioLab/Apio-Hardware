/**************************************************************************\
* Apio Library                                                             *
* https://github.com/ApioLab/library-arduino                               *
* Copyright (c) 2014-2015, Apio s.r.l.. All rights reserved.               *
* www.apio.cc                                                              *
* ------------------------------------------------------------------------ *
*  This program is free software; you can redistribute it and/or modify it *
*  under the terms of the BSD License as described in license.txt.         *
\**************************************************************************/
#ifndef _PINOCCIO_HAL_TEMPERATURE_H_
#define _PINOCCIO_HAL_TEMPERATURE_H_

#include <stdint.h>

/*****************************************************************************
*****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/*****************************************************************************
*****************************************************************************/
int8_t HAL_MeasureTemperature(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // _PINOCCIO_HAL_TEMPERATURE_H_
