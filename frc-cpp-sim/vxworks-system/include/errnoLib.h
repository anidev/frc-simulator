/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef ERRNOLIB_H_INC
#define ERRNOLIB_H_INC

#include "vxWorks.h"

typedef INT32 errno_t;
// below are errno's required by WPILib/Task.cpp
static const errno_t S_objLib_OBJ_ID_ERROR=0x1;
static const errno_t S_objLib_OBJ_DELETED=0x2;
static const errno_t S_taskLib_ILLEGAL_OPTIONS=0x3;
static const errno_t S_memLib_NOT_ENOUGH_MEMORY=0x4;
static const errno_t S_taskLib_ILLEGAL_PRIORITY=0x5;
static const errno_t S_taskLib_NAME_NOT_FOUND=0x6;
static const errno_t S_hostLib_INVALID_PARAMETER=0x7;
static const errno_t S_hostLib_UNKNOWN_HOST=0x8;

#ifdef __cplusplus
extern "C" {
#endif

// errnoLib
int errnoGet();
STATUS errnoSet(errno_t);

#ifdef __cplusplus
}
#endif

#endif // ERRNOLIB_H_INC
