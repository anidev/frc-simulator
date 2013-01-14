/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef TASKLIB_H_INC
#define TASKLIB_H_INC

#include "vxWorks.h"
#include <pthread.h>

typedef int task_t;

#ifdef __x86_64__
typedef uint64_t taskarg_t;
#else
typedef uint32_t taskart_t;
#endif
#define TASKARG_T_DEFINED

typedef struct _task_info {
	char* name;
	task_t task_id;
	int priority;
	int stack_size;
	FUNCPTR entry_point;
	taskarg_t arg1;
	taskarg_t arg2;
	taskarg_t arg3;
	taskarg_t arg4;
	taskarg_t arg5;
	taskarg_t arg6;
	taskarg_t arg7;
	taskarg_t arg8;
	taskarg_t arg9;
	taskarg_t arg10;
	pthread_mutex_t safe_mutex;
	pthread_cond_t safe_cond;
	bool safe;
} task_info;

static const int VX_UNBREAKABLE=0x0002;
static const int VX_FP_TASK=0x0008;
static const int VX_PRIVATE_ENV=0x0080;
static const int VX_NO_STACK_FILL=0x0100;

#ifdef __cplusplus
extern "C" {
#endif

// vxworks-system_frc-cpp-sim
task_info* get_task_info(task_t);
task_info* find_task_by_name(const char*);

// taskLib
task_t taskSpawn(char*,int,int,int,FUNCPTR,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t,taskarg_t);
// STATUS taskInit(WIND_TCB*,char*,int,int,char*,int,FUNCPTR,int,int,int,int,int,int,int,int,int,int); // NOT IMPLEMENTED
// STATUS taskActivate(task_t); // NOT IMPLEMENTED
// void exit(task_t); // NOT IMPLEMENTED
STATUS taskDelete(task_t);
// STATUS taskDeleteForce(task_t); // NOT IMPLEMENTED
STATUS taskSuspend(task_t);
STATUS taskResume(task_t);
STATUS taskRestart(task_t);
STATUS taskPrioritySet(task_t,int);
STATUS taskPriorityGet(task_t,int*);
// STATUS taskLock(); // NOT IMPLEMENTED
// STATUS taskUnlock(); // NOT IMPLEMENTED
STATUS taskSafe();
STATUS taskUnsafe();
STATUS taskDelay(int);
task_t taskIdSelf();
STATUS taskIdVerify(task_t);
// WIND_TCB* taskTcb(task_t);

// taskInfo
BOOL taskIsReady(task_t);
BOOL taskIsSuspended(task_t);
int taskNameToId(const char*);

#ifdef __cplusplus
}
#endif

#endif // TASKLIB_H_INC

