/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <pthread.h>
#include "interfaces/NiRio.h"
#include "interfaces/tInterruptManager.h"
#include "interrupts.h"

void interrupt_helper(unsigned int mask,void* param) {
	tInterruptManager* manager=(tInterruptManager*)param;
	if(manager->_enabled) {
		manager->_handler(manager->_userParam);
	}
}

namespace nFPGA {

tInterruptManager::tInterruptManager(unsigned int mask,bool watcher,tRioStatusCode* status):_interruptMask(mask),
                                                                                            _watcher(watcher),
                                                                                            _handler(NULL),
                                                                                            _userParam(NULL)
{
	disable(NULL);
}

tInterruptManager::~tInterruptManager() {
}

tInterruptManager::registerHandler(tInterruptHandler handler,void* param,tRioStatusCode* status) {
	_handler=handler;
	_userParam=param;
	if(_enabled) {
		enable(NULL);
	} else {
		disable(NULL);
	}
}


}
