/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include "errnoLib.h"

errno_t __local_errno; // strange name so it doesn't conflict with existing symbol errno

int errnoGet() {
    return __local_errno;
}

STATUS errnoSet(errno_t errorValue) {
	__local_errno=errorValue;
	return OK;
}
