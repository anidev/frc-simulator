/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef FIOLIB_H_INC
#define FIOLIB_H_INC

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

// fioLib
int fioRead(int,char*,int);

#ifdef __cplusplus
}
#endif

#endif // FIOLIB_H_INC
