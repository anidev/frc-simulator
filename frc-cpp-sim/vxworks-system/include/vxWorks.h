/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef VXWORKS_H_INC
#define VXWORKS_H_INC

#include <cstdint>

typedef int (*FUNCPTR)(...);

typedef int8_t   INT8;
typedef uint8_t  UINT8;
typedef int16_t  INT16;
typedef uint16_t UINT16;
typedef int32_t  INT32;
typedef uint32_t UINT32;
typedef long long int  INT64;
typedef unsigned long long int UINT64;
typedef UINT32   UINT;
typedef int STATUS;
typedef int BOOL;
typedef unsigned short INSTR;

static const STATUS OK=0;
static const STATUS ERROR=-1;
#ifndef TRUE
static const BOOL TRUE=1;
#endif
#ifndef FALSE
static const BOOL FALSE=0;
#endif

// AAGH for some reason WPILib's SensorBase::kSystemClockTicksPerMicrosecond
// defines the clock rate at 40 MHz, while WPILib's Timer.cpp assumes
// it to be 33 MHz...
// TODO assuming 33 MHz - find real rate
//static const int clockRate=40; // MHz, as defined in WPILib SensorBase::kSystemClockTicksPerMicrosecond
static const int clockRate=33;
static const double ticksPerMicro=clockRate;
static const double ticksPerMilli=clockRate*1000;
static const double microsPerTick=1.0/clockRate;
static const double millisPerTick=microsPerTick*1000;

#endif // VXWORKS_H_INC

