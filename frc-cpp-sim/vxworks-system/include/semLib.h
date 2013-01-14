/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef SEMLIB_H_INC
#define SEMLIB_H_INC

#include "vxWorks.h"
#include <semaphore.h>

typedef enum {
	SEM_BINARY,
	SEM_COUNT,
	SEM_MUTEX
} sem_type;

typedef struct {
	sem_t* sem;
	sem_type type;
	int value;
} semlib_t,*SEM_ID;

typedef int SEM_B_STATE;

static const int SEM_Q_FIFO=0x0;
static const int SEM_Q_PRIORITY=0x1;
static const int SEM_DELETE_SAFE=0x4;
static const int SEM_INVERSION_SAFE=0x8;
static const int SEM_EVENTSEND_ERR_NOTIFY=0x10;
static const SEM_B_STATE SEM_FULL=1;
static const SEM_B_STATE SEM_EMPTY=0;
static const int NO_WAIT=0;
static const int WAIT_FOREVER=-1;

#ifdef __cplusplus
extern "C" {
#endif

// semLib
STATUS semGive(SEM_ID);
STATUS semTake(SEM_ID,int);
STATUS semFlush(SEM_ID);
STATUS semDelete(SEM_ID);

// semCLib
SEM_ID semCCreate(int,int);

// semBLib
SEM_ID semBCreate(int,SEM_B_STATE);

// semMLib
SEM_ID semMCreate(int);

// semSmLib
// SEM_ID semBSmCreate(int,SEM_B_STATE); // NOT IMPLEMENTED
// SEM_ID semCSmCreate(int,int);         // NOT IMPLEMENTED

#ifdef __cplusplus
}
#endif

#endif // SEMLIB_H_INC

