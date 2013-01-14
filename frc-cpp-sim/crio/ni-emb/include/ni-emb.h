/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef NIEMB_H_INC
#define NIEMB_H_INC

#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

int32_t UserSwitchInput(int32_t nSwitch);
int32_t LedInput(int32_t led);
int32_t LedOutput(int32_t led, int32_t value);

#ifdef __cplusplus
}
#endif

#endif // NIEMB_H_INC
