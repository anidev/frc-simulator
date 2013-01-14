/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include "nivision.h"

//============================================================================
//  Pattern Matching functions
//============================================================================

EllipseMatch* imaqDetectEllipses(const Image* image,const EllipseDescriptor* ellipseDescriptor,const CurveOptions* curveOptions,
                                 const ShapeDetectionOptions* shapeDetectionOptions, const ROI* roi, int* numMatchesReturned) {
	// TODO use opencv's ellipse detection
	// not implementing now because it will take a long time
	// to convert these arguments into something opencv can use,
	// and the function will probably never be called anyway.
	return NULL;
}
