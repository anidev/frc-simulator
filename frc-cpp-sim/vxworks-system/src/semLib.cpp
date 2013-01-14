/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <semaphore.h>
#include "semLib.h"

// semLib
STATUS semGive(SEM_ID sem_id) {
	sem_t* sem=sem_id->sem;
	sem_post(sem);
	sem_id->value++;
	return OK;
}

STATUS semTake(SEM_ID sem_id,int timeout_ticks) {
	sem_t* sem=sem_id->sem;
	sem_id->value--;
	if(timeout_ticks==-1) {
		sem_wait(sem);
		return OK;
	}
	if(timeout_ticks==0) {
		sem_trywait(sem);
		return OK;
	}
	struct timespec timeout_nanos={0,(long)(timeout_ticks*microsPerTick*1000)};
	sem_timedwait(sem,&timeout_nanos);
	return OK;
}

STATUS semFlush(SEM_ID sem_id) {
	sem_t* sem=sem_id->sem;
	// NOTE: Not sure if this works or gets stuck in infinite loop
	while(sem_id->value<0) {
		sem_post(sem);
		sem_id->value++;
		// sem_getvalue might be easier, but not guaranteed to return sane value
	}
	return OK;
}

STATUS semDelete(SEM_ID sem_id) {
	sem_t* sem=sem_id->sem;
	sem_destroy(sem);
	delete sem;
	delete sem_id;
	return OK;
}

// semCLib
SEM_ID semCCreate(int options,int initialCount) {
	SEM_ID sem_id=new semlib_t;
	sem_id->sem=new sem_t;
	sem_id->type=SEM_COUNT;
	sem_id->value=initialCount;
	sem_init(sem_id->sem,0,initialCount);
	return sem_id;
}

// semBLib
SEM_ID semBCreate(int options,SEM_B_STATE initialState) {
	SEM_ID sem_id=new semlib_t;
	sem_id->sem=new sem_t;
	sem_id->type=SEM_BINARY;
	sem_id->value=initialState;
	sem_init(sem_id->sem,0,initialState);
	return sem_id;
}

// semMLib
SEM_ID semMCreate(int options) {
	SEM_ID sem_id=new semlib_t;
	sem_id->sem=new sem_t;
	sem_id->type=SEM_MUTEX;
	sem_id->value=0;
	sem_init(sem_id->sem,0,0);
	return sem_id;
}

