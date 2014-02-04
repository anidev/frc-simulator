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

// TODO implement particle analysis.

int imaqCountParticles(Image* image,int connectivity8,int* numParticles) {
	NOTNULL(image,"imaqCountParticles");
	NOTNULL(numParticles,"imaqCountParticles");
	*numParticles=0; // i'll fix it some other time...
	return RET_FAIL;
}

int imaqMeasureParticle(Image* image,int particleNumber,int calibrated,MeasurementType measurement,double* value) {
	NOTNULL(image,"imaqMeasureParticle");
	NOTNULL(value,"imaqMeasureParticle");
	return RET_FAIL; // because obviously there are no particles to be found... so why the NOTNULL's above? good question...
}

int imaqParticleFilter4(Image* dest,Image* source,const ParticleFilterCriteria2* criteria,int criteriaCount,const ParticleFilterOptions2* options,const ROI* roi,int* numParticles) {
	NOTNULL(source,"imaqParticleFilter4");
	NOTNULL(dest,"imaqParticleFilter4");
	NOTNULL(criteria,"imaqParticleFilter4");
	NOTNULL(options,"imaqParticleFilter4");
	NOTNULL(roi,"imaqParticleFilter4");
	NOTNULL(numParticles,"imaqParticleFilter4");
	return RET_FAIL;
}

//============================================================================
//  Morphology functions
//============================================================================

// TODO implement morphology

int imaqConvexHull(Image* dest,Image* source,int connectivity8) {
	NOTNULL(source,"imaqConvexHull");
	NOTNULL(dest,"imaqConvexHull");
	dest->mat_data=source->mat_data;
	return RET_FAIL;
}

int imaqSizeFilter(Image* dest,Image* source,int connectivity8,int erosions,SizeType keepSize,const StructuringElement* structuringElement) {
	NOTNULL(source,"imaqSizeFilter");
	NOTNULL(dest,"imaqSizeFilter");
	NOTNULL(structuringElement,"imaqSizeFilter");
	return RET_FAIL;
}
