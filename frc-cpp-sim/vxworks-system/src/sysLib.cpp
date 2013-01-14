/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include "sysLib.h"

int sysClkRateGet() {
//              MHz      KHz  Hz
	return clockRate*1000*1000;
}
