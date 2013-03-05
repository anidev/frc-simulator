/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include <cstring>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include "taskLib.h"
#include "errnoLib.h"

std::map<pthread_t,task_t> thread_task;
std::map<task_t,pthread_t> task_thread;
std::map<task_t,task_info*> tasks_info_map;
pthread_mutex_t map_mutex=PTHREAD_MUTEX_INITIALIZER;
task_t totalTasks=0;

// private
#ifdef __cplusplus
extern "C"
#endif
void* task_spawn_entry(void* v_info) {
	task_info* info=(task_info*)v_info;
	info->entry_point(info->arg1,
	                  info->arg2,
	                  info->arg3,
	                  info->arg4,
	                  info->arg5,
	                  info->arg6,
	                  info->arg7,
	                  info->arg8,
	                  info->arg9,
	                  info->arg10);
	return NULL;
}

void create_task(task_info* info) {
	pthread_attr_t attrs;
	pthread_attr_init(&attrs);
	pthread_attr_setstacksize(&attrs,info->stack_size);
	pthread_t thread;
	pthread_create(&thread,&attrs,&task_spawn_entry,info);
	pthread_setname_np(thread,info->name);
	pthread_mutex_lock(&map_mutex);
	thread_task[thread]=info->task_id;
	task_thread[info->task_id]=thread;
	tasks_info_map[info->task_id]=info;
	pthread_mutex_unlock(&map_mutex);
}

// vxworks-system_frc-cpp-sim
task_info* get_task_info(task_t task_id) {
	pthread_mutex_lock(&map_mutex);
	task_info* info_copy=NULL;
	task_info* info=tasks_info_map[task_id];
	if(info!=NULL) {
		info_copy=new task_info;
		memcpy(info_copy,info,sizeof(*info_copy));
	}
	pthread_mutex_unlock(&map_mutex);
	return info_copy;
}

task_info* find_task_by_name(const char* name) {
	pthread_mutex_lock(&map_mutex);
	for(std::map<task_t,task_info*>::iterator iterate=tasks_info_map.begin();iterate!=tasks_info_map.end();iterate++) {
		task_info* info=iterate->second;
		if(strcmp(info->name,name)==0) {
			task_info* info_copy=new task_info;
			memcpy(info_copy,info,sizeof(*info_copy));
			pthread_mutex_unlock(&map_mutex);
			return info_copy;
		}
	}
	pthread_mutex_unlock(&map_mutex);
	return NULL;
}

// taskLib
task_t taskSpawn(char* name,int priority,int options,int stackSize,FUNCPTR entryPt,
                 taskarg_t arg1,taskarg_t arg2,taskarg_t arg3,taskarg_t arg4,taskarg_t arg5,
                 taskarg_t arg6,taskarg_t arg7,taskarg_t arg8,taskarg_t arg9,taskarg_t arg10) {
	task_t task_id=totalTasks;
	task_info* info=new task_info;
	info->name=name;
	info->task_id=task_id;
	info->priority=priority;
	info->stack_size=stackSize;
	info->entry_point=entryPt;
	info->arg1=arg1;
	info->arg2=arg2;
	info->arg3=arg3;
	info->arg4=arg4;
	info->arg5=arg5;
	info->arg6=arg6;
	info->arg7=arg7;
	info->arg8=arg8;
	info->arg9=arg9;
	info->arg10=arg10;
	info->safe_mutex=PTHREAD_MUTEX_INITIALIZER;
	info->safe_cond=PTHREAD_COND_INITIALIZER;
	info->safe=false;
	create_task(info);
	totalTasks++;
	return task_id;
}

STATUS taskDelete(task_t task_id) {
	pthread_t thread;
	pthread_mutex_lock(&map_mutex);
	task_info* info=tasks_info_map[task_id];
	pthread_mutex_lock(&info->safe_mutex);
	while(info->safe) {
		pthread_mutex_unlock(&map_mutex);
		pthread_cond_wait(&info->safe_cond,&info->safe_mutex);
	}
	pthread_mutex_lock(&map_mutex);
	pthread_mutex_unlock(&info->safe_mutex);
	delete info;
	thread=task_thread[task_id];
	thread_task.erase(thread);
	task_thread.erase(task_id);
	tasks_info_map.erase(task_id);
	pthread_mutex_unlock(&map_mutex);

	// this doesn't actually kill the thread;
	// AFAICT, there is not way in pthreads to forcibly
	// terminate a thread, so this is the best that can be done.
	pthread_cancel(thread);
	pthread_detach(thread);
	return OK;
}

STATUS taskSuspend(task_t task_id) {
	// do nothing,
	// because nothing (AFAICT) can be done in pthreads
	// to suspend threads.
	return OK;
}

STATUS taskResume(task_t task_id) {
	// do nothing;
	// see taskSuspend.
	return OK;
}

STATUS taskRestart(task_t task_id) {
	// attempts to delete (cancel and detach) task,
	// then start task again, regardless if
	// previous task is still running.
	// can't be helped with pthreads
	pthread_mutex_lock(&map_mutex);
	task_info* info_copy=NULL;
	task_info* info=tasks_info_map[task_id];
	if(info!=NULL) {
		info_copy=new task_info;
		memcpy(info_copy,info,sizeof(*info_copy));
	}
	pthread_mutex_unlock(&map_mutex);
	taskDelete(task_id);
	create_task(info_copy);
	return OK;
}

STATUS taskPrioritySet(task_t task_id,int newPriority) {
	// pretend to change priority;
	// can't really change priority because
	// priorities work differently on Linux
	pthread_mutex_lock(&map_mutex);
	task_info* info=tasks_info_map[task_id];
	info->priority=newPriority;
	tasks_info_map[task_id]=info;
	pthread_mutex_unlock(&map_mutex);
	return OK;
}

STATUS taskPriorityGet(task_t task_id,int* pPriority) {
	pthread_mutex_lock(&map_mutex);
	task_info* info=tasks_info_map[task_id];
	*pPriority=info->priority;
	pthread_mutex_unlock(&map_mutex);
	return OK;
}

STATUS taskSafe() {
	task_t task_id=taskIdSelf();
	pthread_mutex_lock(&map_mutex);
	task_info* info=tasks_info_map[task_id];
	if(!info->safe) {
		pthread_mutex_lock(&info->safe_mutex);
		info->safe=true;
		pthread_mutex_unlock(&info->safe_mutex);
	}
	pthread_mutex_unlock(&map_mutex);
	return OK;
}

STATUS taskUnsafe() {
	task_t task_id=taskIdSelf();
	pthread_mutex_lock(&map_mutex);
	task_info* info=tasks_info_map[task_id];
	if(info->safe) {
		pthread_mutex_lock(&info->safe_mutex);
		info->safe=false;
		pthread_cond_signal(&info->safe_cond);
		pthread_mutex_unlock(&info->safe_mutex);
	}
	pthread_mutex_unlock(&map_mutex);
	return OK;
}

STATUS taskDelay(int ticks) {
	useconds_t delay_micro=(useconds_t)(ticks*microsPerTick);
	usleep(delay_micro);
	return OK;
}

task_t taskIdSelf() {
	pthread_t thread=pthread_self();
	pthread_mutex_lock(&map_mutex);
	task_t task_id=thread_task[thread];
	pthread_mutex_unlock(&map_mutex);
	return task_id;
}

STATUS taskIdVerify(task_t task_id) {
	std::map<task_t,pthread_t>::iterator task_iter=task_thread.find(task_id);
	if(task_iter==task_thread.end()) { // not found
		return ERROR;
	} else { // found
		return OK;
	}
}

// taskInfo
BOOL taskIsReady(task_t task_id) {
	// Tasks are ready and started by the time
	// taskLib.h::taskSpawn returns, so always
	// return TRUE here.
	return TRUE;
}

BOOL taskIsSuspended(task_t task_id) {
	// task/thread suspension is not supported
	// by pthreads, and thus not supported by
	// this implementation, so always return FALSE
	return FALSE;
}

int taskNameToId(const char* name) {
	task_info* info=find_task_by_name(name);
	if(info==NULL) {
		errnoSet(S_taskLib_NAME_NOT_FOUND);
		return ERROR;
	}
	return info->task_id;
}

// sigLib
int taskKill(task_t task_id,int sig) {
	pthread_mutex_lock(&map_mutex);
	pthread_t thread=task_thread[task_id];
	pthread_mutex_unlock(&map_mutex);
	return pthread_kill(thread,sig);
}
