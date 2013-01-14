/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <cstdint>
#include "ni-emb.h"

bool user1_led=false;

int32_t UserSwitchInput(int32_t nSwitch) {
	// until netcontrol implemented...
	// assume the switch is off
	switch(nSwitch) {
	case 0:
		return 0;
		break;
	}
	return 0;
}

int32_t LedInput(int32_t led) {
	return user1_led;
}

int32_t LedOutput(int32_t led, int32_t value) {
	switch(led) {
	case 0:
		user1_led=value>0;
		return value>0;
		break;
	}
	return 0;
}
