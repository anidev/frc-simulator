/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

// TODO must decide if watchdog will be implemented here (no network latency, must be reimplemented) or on client (network latency, single implementation)

#include <ctime>
#include <cmath>
#include <iostream>
#include <pthread.h>
#include "fpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tWatchdog.h"
#include "interfaces/tSystemInterface.h"

const double kSystemClockTicksPerMicrosecond=40; // from WPILib SensorBase.h

class tWatchdog_impl:public nFPGA::nFRC_2012_1_6_4::tWatchdog {
public:
	tWatchdog_impl(tRioStatusCode*);
	~tWatchdog_impl();
	nFPGA::tSystemInterface* getSystemInterface();
	tStatus readStatus(tRioStatusCode*);
	bool readStatus_SystemActive(tRioStatusCode*);
	bool readStatus_Alive(tRioStatusCode*);
	unsigned short readStatus_SysDisableCount(tRioStatusCode*);
	unsigned short readStatus_DisableCount(tRioStatusCode*);
	void writeImmortal(bool value, tRioStatusCode*);
	bool readImmortal(tRioStatusCode*);
	void strobeKill(tRioStatusCode*);
	void strobeFeed(tRioStatusCode*);
	void writeExpiration(unsigned int value, tRioStatusCode*);
	unsigned int readExpiration(tRioStatusCode*);
	unsigned int readTimer(tRioStatusCode*);
private:
	void set_enabled(bool);
	void panic();
	static void* thread_entry(void*);
	bool alive;
	bool system_active;
	unsigned short sys_disable_count;
	unsigned short disable_count;
	bool fed;
	timespec time_fed;
	bool enabled; // !immortal
	pthread_t* thread;
	double expiration; // microseconds
};

nFPGA::nFRC_2012_1_6_4::tWatchdog* nFPGA::nFRC_2012_1_6_4::tWatchdog::create(tRioStatusCode* status) {
	return new tWatchdog_impl(status);
}

tWatchdog_impl::tWatchdog_impl(tRioStatusCode* status):alive(true),
                                                       system_active(true),
                                                       sys_disable_count(0),
                                                       disable_count(0),
                                                       fed(false),
                                                       thread(NULL),
                                                       expiration(10*1e6 /*10 seconds*/)
{
	set_enabled(true);
	clock_gettime(CLOCK_MONOTONIC,&time_fed);
}

tWatchdog_impl::~tWatchdog_impl() {
}

nFPGA::tSystemInterface* tWatchdog_impl::getSystemInterface() {
	return get_system_interface();
}

nFPGA::nFRC_2012_1_6_4::tWatchdog::tStatus tWatchdog_impl::readStatus(tRioStatusCode* status) {
	nFPGA::nFRC_2012_1_6_4::tWatchdog::tStatus dog_status={{system_active,alive,sys_disable_count,disable_count}};
	return dog_status;
}

bool tWatchdog_impl::readStatus_SystemActive(tRioStatusCode* status) {
	return system_active;
}

bool tWatchdog_impl::readStatus_Alive(tRioStatusCode* status) {
	return alive;
}
unsigned short tWatchdog_impl::readStatus_SysDisableCount(tRioStatusCode* status) {
	return sys_disable_count;
}

unsigned short tWatchdog_impl::readStatus_DisableCount(tRioStatusCode* status) {
	return disable_count;
}

void tWatchdog_impl::writeImmortal(bool value, tRioStatusCode* status) {
	set_enabled(!value);
}

bool tWatchdog_impl::readImmortal(tRioStatusCode* status) {
	return !enabled;
}

void tWatchdog_impl::strobeKill(tRioStatusCode* status) {
	alive=false;
	set_enabled(false);
}

void tWatchdog_impl::strobeFeed(tRioStatusCode* status) {
	alive=true;
	fed=true;
	clock_gettime(CLOCK_MONOTONIC,&time_fed);
	set_enabled(true);
}

void tWatchdog_impl::writeExpiration(unsigned int value, tRioStatusCode* status) {
	// value is in ticks
	double microseconds=value*1.0/kSystemClockTicksPerMicrosecond;
	expiration=microseconds;
	set_enabled(false);
	set_enabled(true);
}

unsigned int tWatchdog_impl::readExpiration(tRioStatusCode* status) {
	return expiration*kSystemClockTicksPerMicrosecond;
}

unsigned int tWatchdog_impl::readTimer(tRioStatusCode* status) {
	timespec now_time;
	clock_gettime(CLOCK_MONOTONIC,&now_time);
	int nanosec_elapsed=(now_time.tv_sec-time_fed.tv_sec)*1e9+(now_time.tv_nsec-time_fed.tv_nsec);
	int ticks_elapsed=(nanosec_elapsed/1e3)*kSystemClockTicksPerMicrosecond;
	return ticks_elapsed;
}
void tWatchdog_impl::set_enabled(bool value) {
	enabled=value;
	if(enabled) {
		pthread_create(thread,NULL,tWatchdog_impl::thread_entry,(void*)this);
	} else {
		if(thread!=NULL) {
			pthread_cancel(*thread);
		}
		thread=NULL;
	}
}
void tWatchdog_impl::panic() {
	// TODO
	std::cout<<"AAAAH PANIC! THE WATCHDOG HAS DIED FROM STARVATION!"<<std::endl;
}
void* tWatchdog_impl::thread_entry(void* void_ptr) {
	tWatchdog_impl* this_ptr=(tWatchdog_impl*)void_ptr;
	while(true) {
		pthread_testcancel();
		long nanoseconds=this_ptr->readExpiration(NULL)*1e3;
		time_t seconds=(time_t)floor(nanoseconds/1e9);
		nanoseconds-=seconds*1e9;
		timespec sleep_time={seconds,nanoseconds};
		nanosleep(&sleep_time,NULL);
		if(this_ptr->fed) {
			this_ptr->fed=false;
		} else{
			this_ptr->panic();
		}
		pthread_testcancel();
	}
	return NULL;
}
