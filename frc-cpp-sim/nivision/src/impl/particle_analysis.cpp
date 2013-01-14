/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include "nivision.h"
#include "nivision-impl.h"
#include "utils.h"

//============================================================================
//  Particle Analysis functions
//============================================================================

// forget particle analysis...
// can't figure out how to do it in OpenCV, and
// don't have time to further investigate.
// TODO implement particle analysis.

int imaqCountParticles(Image* image,int connectivity8,int* numParticles) {
	NOTNULL(image,"imaqCountParticles");
	NOTNULL(numParticles,"imaqCountParticles");
	*numParticles=0; // i'll fix it some other time...
	return RET_SUCCESS;
}

int imaqMeasureParticle(Image* image,int particleNumber,int calibrated,MeasurementType measurement,double* value) {
	NOTNULL(image,"imaqMeasureParticle");
	NOTNULL(value,"imaqMeasureParticle");
	return RET_FAIL; // because obviously there are no particles to be found... so why the NOTNULL's above? good question...
}
