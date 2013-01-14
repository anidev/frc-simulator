/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include "nivision.h"
#include "nivision-impl.h"

//============================================================================
//  Memory Management functions
//============================================================================

int imaqDispose(void* object) {
	NOTNULL(object,"imaqDispose");
	base_object* base=static_cast<base_object*>(object); // if not base_object, then error
	Image* image;
	ROI* roi;
	switch(base->data_type) {
	case NIVISION_TYPE_IMAGE:
		image=(Image*)object;
		// apparently opencv 2.x C++ functions take care of
		// automatic memory deletion, so just delting
		// the Image* should deconstruct and automatically
		// delete mat_data.
		delete image;
		break;
	case NIVISION_TYPE_ROI:
		roi=(ROI*)object;
		delete roi;
	}
	return RET_SUCCESS; // if something fails, we've probably segfaulted and won't get to this point...
}
