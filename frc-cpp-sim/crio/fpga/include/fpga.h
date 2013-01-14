/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef FPGA_H_INC
#define FPGA_H_INC

#include <cstdint>
#include "interfaces/NiRio.h"
#include "interfaces/tSystemInterface.h"

// TODO get real values for these...
static const uint16_t FPGA_VERSION=2012;
static const uint32_t FPGA_REVISION=1;
// assuming this is a UUID (based on the parameters to
// tSystemInterface::getHardwareFpgaSignature
static const uint32_t FPGA_SIGNATURE[]={1,2,3,4};
static const int FPGA_SIGNATURE_LEN=4;

nFPGA::tSystemInterface* get_system_interface();

#endif // FGPA_H_INC

