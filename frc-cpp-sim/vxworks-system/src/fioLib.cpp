/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include <unistd.h>
#include <iostream>
#include "fioLib.h"

// fioLib
int fioRead(int fd,char* buffer,int maxbytes) {
	return read(fd,buffer,maxbytes);
}
