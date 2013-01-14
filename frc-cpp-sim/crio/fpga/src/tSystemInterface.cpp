/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <cstring>
#include "fpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tSystemInterface.h"

class tSystemInterface_impl:public nFPGA::tSystemInterface {
public:
	const uint16_t getExpectedFPGAVersion();
	const uint32_t getExpectedFPGARevision();
	const uint32_t* const getExpectedFPGASignature();
	void getHardwareFpgaSignature(uint32_t*,tRioStatusCode*);
	uint32_t getLVHandle(tRioStatusCode*);
	uint32_t getHandle();
};

const uint16_t tSystemInterface_impl::getExpectedFPGAVersion() {
	return FPGA_VERSION;
}

const uint32_t tSystemInterface_impl::getExpectedFPGARevision() {
	return FPGA_REVISION;
}

const uint32_t* const tSystemInterface_impl::getExpectedFPGASignature() {
	return FPGA_SIGNATURE;
}

void tSystemInterface_impl::getHardwareFpgaSignature(uint32_t* guid_ptr,tRioStatusCode* status) {
	std::memcpy(guid_ptr,FPGA_SIGNATURE,sizeof(uint32_t)*FPGA_SIGNATURE_LEN);
}

uint32_t tSystemInterface_impl::getLVHandle(tRioStatusCode* status) {
	return 0; // no idea what this is for; not used anywhere
}

uint32_t tSystemInterface_impl::getHandle() {
	return 0; // no idea what this is for; not used anywhere
}

nFPGA::tSystemInterface* get_system_interface() {
	static nFPGA::tSystemInterface* instance=NULL;
	if(instance==NULL) {
		instance=new tSystemInterface_impl();
	}
	return instance;
}
