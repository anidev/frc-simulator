/*
 * DefaultThreadManger.cpp
 *
 *  Created on: Sep 21, 2012
 *      Author: Mitchell Wills
 */

#include "networktables2/thread/DefaultThreadManager.h"
#include <stdio.h>

#ifdef __FRC_CPP_SIM__
#include <taskLib.h>
#endif


PeriodicNTThread::PeriodicNTThread(PeriodicRunnable* _r, const char* _name) : 
			name(_name), thread(new Task(name, (FUNCPTR)PeriodicNTThread::taskMain)), r(_r), run(true){
	fprintf(stdout, "Starting task: %s\n", name);
	fflush(stdout);
#ifdef __FRC_CPP_SIM__
	thread->Start((taskarg_t)this);
#else
	thread->Start((UINT32)this);
#endif
}

PeriodicNTThread::~PeriodicNTThread(){
	//TODO somehow do this async
	//delete thread;
}
int PeriodicNTThread::taskMain(PeriodicNTThread* o){//static wrapper
	return o->_taskMain();
}
int PeriodicNTThread::_taskMain(){
	try {
		while(run){
			r->run();
		}
	} catch (...) {
		fprintf(stdout, "Task exited with uncaught exception %s\n", name);
		fflush(stdout);
		return 1;
	}
	fprintf(stdout, "Task exited normally: %s\n", name);
	fflush(stdout);
	return 0;
}
void PeriodicNTThread::stop() {
	run = false;
	//TODO thread->Stop();
}
bool PeriodicNTThread::isRunning() {
	return thread->IsReady();
}

NTThread* DefaultThreadManager::newBlockingPeriodicThread(PeriodicRunnable* r, const char* name) {
	return new PeriodicNTThread(r, name);
}
