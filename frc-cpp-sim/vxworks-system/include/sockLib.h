/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef SOCKLIB_H_INC
#define SOCKLIB_H_INC

#include "vxWorks.h"
#include <sys/socket.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// sockLib
STATUS connectWithTimeout(int,sockaddr*,int,timeval*);

#ifdef __cplusplus
}
#endif

#endif // SOCKLIB_H_INC
