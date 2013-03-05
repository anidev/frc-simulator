/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <vxWorks.h>
#include "UsageReporting.h"

UINT32 nUsageReporting::report(tResourceType resource,UINT8 instanceNumber,UINT8 context,const char* feature) {
	// we don't care about this stuff
	return 0;
}
