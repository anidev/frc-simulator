/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "fpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tAlarm.h"
#include "interfaces/tSystemInterface.h"

class tAlarm_impl:public nFPGA::nFRC_2012_1_6_4::tAlarm {
public:
	tAlarm_impl(tRioStatusCode*);
	~tAlarm_impl();
	nFPGA::tSystemInterface* getSystemInterface();
	void writeTriggerTime(unsigned int,tRioStatusCode*);
	unsigned int readTriggerTime(tRioStatusCode*);
	void writeEnable(bool,tRioStatusCode*);
	bool readEnable(tRioStatusCode*);
private:
	unsigned int trigger_time;
	bool enabled;
};

nFPGA::nFRC_2012_1_6_4::tAlarm* nFPGA::nFRC_2012_1_6_4::tAlarm::create(tRioStatusCode* status) {
	return new tAlarm_impl(status);
}

tAlarm_impl::tAlarm_impl(tRioStatusCode* code):trigger_time(0),
                                                    enabled(false)
{	
}

tAlarm_impl::~tAlarm_impl() {
}

nFPGA::tSystemInterface* tAlarm_impl::getSystemInterface() {
	return get_system_interface();
}

void tAlarm_impl::writeTriggerTime(unsigned int time,tRioStatusCode* status) {
	trigger_time=time;
}

unsigned int tAlarm_impl::readTriggerTime(tRioStatusCode* status) {
	return trigger_time;
}

void tAlarm_impl::writeEnable(bool value,tRioStatusCode* status) {
	enabled=value;
}

bool tAlarm_impl::readEnable(tRioStatusCode* status) {
	return enabled;
}
