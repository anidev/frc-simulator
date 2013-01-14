/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "fpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tAccumulator.h"
#include "interfaces/tSystemInterface.h"

class tAccumulator_impl:public nFPGA::nFRC_2012_1_6_4::tAccumulator {
public:
	tAccumulator_impl(unsigned char);
	~tAccumulator_impl();
	nFPGA::tSystemInterface* getSystemInterface();
	unsigned char getSystemIndex();
	tOutput readOutput(tRioStatusCode*);
	signed long long readOutput_Value(tRioStatusCode*);
	unsigned int readOutput_Count(tRioStatusCode*);
	void writeCenter(signed int,tRioStatusCode*);
	signed int readCenter(tRioStatusCode*);
	void strobeReset(tRioStatusCode*);
	void writeDeadband(signed int,tRioStatusCode*);
	signed int readDeadband(tRioStatusCode*);
private:
	unsigned char sys_index;
	signed long long value;
	unsigned int count;
	signed int center;
	signed int deadband;
};

nFPGA::nFRC_2012_1_6_4::tAccumulator* nFPGA::nFRC_2012_1_6_4::tAccumulator::create(unsigned char sys_index,tRioStatusCode* status) {
	return new tAccumulator_impl(sys_index);
}

tAccumulator_impl::tAccumulator_impl(unsigned char sys_index):sys_index(sys_index),
                                                              value(0),
                                                              count(0),
                                                              center(0),
                                                              deadband(0) {
}

tAccumulator_impl::~tAccumulator_impl() {
}

nFPGA::tSystemInterface* tAccumulator_impl::getSystemInterface() {
	return get_system_interface();
}

unsigned char tAccumulator_impl::getSystemIndex() {
	return sys_index;
}

tAccumulator_impl::tOutput tAccumulator_impl::readOutput(tRioStatusCode* status) {
	tOutput output={{value,count}};
	return output;
}

signed long long tAccumulator_impl::readOutput_Value(tRioStatusCode* status) {
	return value;
}

unsigned int tAccumulator_impl::readOutput_Count(tRioStatusCode* status) {
	return count;
}

void tAccumulator_impl::writeCenter(signed int new_center,tRioStatusCode* status) {
	center=new_center;
}

signed int tAccumulator_impl::readCenter(tRioStatusCode* status) {
	return center;
}

void tAccumulator_impl::strobeReset(tRioStatusCode* status) {
	value=0;
	count=0;
}

void tAccumulator_impl::writeDeadband(signed int new_deadband,tRioStatusCode* status) {
	deadband=new_deadband;
}

signed int tAccumulator_impl::readDeadband(tRioStatusCode* status) {
	return deadband;
}
