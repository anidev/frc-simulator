/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include <iostream>
#include "usrLib.h"

void printErrno(int __local_errno) { // strange name to avoid conflict with global errno
    // TODO add actual error messages
    std::cout<<"Unknown error: "<<__local_errno<<std::endl;
}
