/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef UTILS_H_INC
#define UTILS_H_INC

#include "nivision-impl.h"

namespace niv {
	inline int successful(bool success) {
		if(success) {
			return RET_SUCCESS;
		} else {
			return RET_FAIL;
		}
	}
	
	void checkAndConvertMode(Image*,ColorMode);
	bool isGrayscale(Image*);
	bool isGrayscale(const Image*);
}

#endif // UTILS_H_INC
