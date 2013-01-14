/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <cmath>
#include <ctime>
#include "fpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tGlobal.h"
#include "interfaces/tSystemInterface.h"

class tGlobal_impl:public nFPGA::nFRC_2012_1_6_4::tGlobal {
public:
	tGlobal_impl(tRioStatusCode*);
	~tGlobal_impl();
	nFPGA::tSystemInterface* getSystemInterface();
	unsigned short readVersion(tRioStatusCode*);
	void writeFPGA_LED(bool,tRioStatusCode*);
	bool readFPGA_LED(tRioStatusCode*);
	unsigned int readLocalTime(tRioStatusCode*);
	unsigned int readRevision(tRioStatusCode*);
private:
	bool led;
};

nFPGA::nFRC_2012_1_6_4::tGlobal* nFPGA::nFRC_2012_1_6_4::tGlobal::create(tRioStatusCode* status) {
	return new tGlobal_impl(status);
}

tGlobal_impl::tGlobal_impl(tRioStatusCode* status):led(false) {
}

tGlobal_impl::~tGlobal_impl() {
}

nFPGA::tSystemInterface* tGlobal_impl::getSystemInterface() {
	return get_system_interface();
}

unsigned short tGlobal_impl::readVersion(tRioStatusCode* status) {
	return FPGA_VERSION;
}

void tGlobal_impl::writeFPGA_LED(bool value,tRioStatusCode* status) {
	led=value;
}

bool tGlobal_impl::readFPGA_LED(tRioStatusCode* status) {
	return led;
}

unsigned int tGlobal_impl::readLocalTime(tRioStatusCode* status) {
	double micros=std::clock()*1.0/CLOCKS_PER_SEC*1000*1000;
	return std::floor(micros);
}

unsigned int tGlobal_impl::readRevision(tRioStatusCode* status) {
	return FPGA_REVISION;
}
