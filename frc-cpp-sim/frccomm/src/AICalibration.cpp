/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <cstdint>
#include <vxWorks.h>
#include "frccomm-impl.h"
#include "AICalibration.h"

UINT32 FRC_NetworkCommunication_nAICalibration_getLSBWeight(const UINT32 aiSystemIndex,const UINT32 channel,INT32* status) {
	return LSB_WEIGHT;
}

INT32 FRC_NetworkCommunication_nAICalibration_getOffset(const UINT32 aiSystemIndex,const UINT32 channel,INT32* status) {
	return OFFSET;
}
