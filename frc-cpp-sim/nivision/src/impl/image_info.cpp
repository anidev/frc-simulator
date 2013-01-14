/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include "nivision.h"
#include "nivision-impl.h"

//============================================================================
//  Image Information functions
//============================================================================

int imaqGetImageSize(const Image* image,int* width,int* height) {
	NOTNULL(image,"imaqGetImageSize");
	NOTNULL(width,"imaqGetImageSize");
	NOTNULL(height,"imaqGetImageSize");
	cv::Mat mat=image->mat_data;
	*width=mat.cols;
	*height=mat.rows;
	return RET_SUCCESS; // what could possibly go wrong...
}
