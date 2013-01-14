/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "nivision.h"
#include "nivision-impl.h"
#include "utils.h"

//============================================================================
//  File I/O functions
//============================================================================

int imaqReadFile(Image* image,const char* fileName,RGBValue* colorTable,int* numColors) {
	// UNUSED: colorTable - no documentation
	// UNUSED: numColors - no documentation
	NOTNULL(image,"imaqReadFile");
	NOTNULL(fileName,"imaqReadFile");
	const std::string file_name_str(fileName);
	cv::Mat image_mat=cv::imread(file_name_str,-1); // -1: read image as-is vs forcing 3 channels (1) or grayscale (0)
	if(image_mat.data==NULL) {
		return RET_FAIL;
	}
	image->mat_data=image_mat;
	return RET_SUCCESS;
}

int imaqWriteFile(const Image* image,const char* fileName,const RGBValue* colorTable) {
	// UNUSED: colorTable - no documentation
	NOTNULL(image,"imaqWriteFile");
	NOTNULL(fileName,"imaqWriteFile");
	const std::string file_name_str(fileName);
	// not sure how well this works; the documentation talks about some limitations, but one can hope
	bool success=cv::imwrite(file_name_str,image->mat_data);
	return niv::successful(success);
}
