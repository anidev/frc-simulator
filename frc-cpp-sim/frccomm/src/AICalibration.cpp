/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <cstdint>
#include "impl.h"
#include "AICalibration.h"

uint32_t FRC_NetworkCommunication_nAICalibration_getLSBWeight(const uint32_t aiSystemIndex,const uint32_t channel,int32_t* status) {
	return LSB_WEIGHT;
}

int32_t FRC_NetworkCommunication_nAICalibration_getOffset(const uint32_t aiSystemIndex,const uint32_t channel,int32_t* status) {
	return OFFSET;
}
