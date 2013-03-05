/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <pthread.h>
#include "interfaces/NiFpga.h"
#include "interfaces/NiRio.h"
#include "interfaces/tInterruptManager.h"
#include "interrupts.h"

struct manager_data {
	bool enabled;
	nFPGA::tInterruptHandler handler;
	void* param;
};

void interrupt_helper(unsigned int mask,void* param) {
	manager_data* data=(manager_data*)param;
	if(data->enabled&&data->handler!=NULL&&data->param!=NULL) {
		data->handler(mask,data->param);
	}
}

namespace nFPGA {

tInterruptManager::tInterruptManager(unsigned int mask,bool watcher,tRioStatusCode* status):tSystem(status),
                                                                                            _handler(NULL),
                                                                                            _interruptMask(mask),
                                                                                            _watcher(watcher),
                                                                                            _userParam(NULL)
{
	disable(NULL);
	manager_data* data=new manager_data;
	data->enabled=false;
	data->handler=NULL;
	data->param=NULL;
	interrupts_callback callback={interrupt_helper,(void*)_userParam};
	interrupts::get_instance()->register_callback(mask,callback);
}

tInterruptManager::~tInterruptManager() {
}

void tInterruptManager::registerHandler(tInterruptHandler handler,void* param,tRioStatusCode* status) {
	_handler=handler;
	_userParam=param;
	manager_data* data=(manager_data*)_userParam;
	data->handler=handler;
	data->param=param;
	if(_enabled) {
		enable(NULL);
	} else {
		disable(NULL);
	}
}

unsigned int tInterruptManager::watch(int timeout,tRioStatusCode* status) {
	// TODO
	*status=NiFpga_Status_IrqTimeout;
	return 0;
}

void tInterruptManager::enable(tRioStatusCode* status) {
	_enabled=true;
	manager_data* data=(manager_data*)_userParam;
	data->enabled=true;
}

void tInterruptManager::disable(tRioStatusCode* status) {
	_enabled=false;
	manager_data* data=(manager_data*)_userParam;
	data->enabled=false;
}

bool tInterruptManager::isEnabled(tRioStatusCode* status) {
	return _enabled;
}

}
