/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef NIPRIV_H_INC
#define NIPRIV_H_INC

#include <cstdint>
#include <nivision.h>

#ifdef __cplusplus
extern "C"
{
#endif

int Priv_SetWriteFileAllowed(uint32_t);
int Priv_ReadJPEGString_C(Image*,const unsigned char*,uint32_t);

uint32_t niTimestamp32(void);
uint64_t niTimestamp64(void);

#ifdef __cplusplus
}
#endif

#endif // NIPRIV_H_INC
