/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef IMPL_H_INC
#define IMPL_H_INC

#include <opencv2/core/core.hpp>
#include "nivision.h"

// I know this is evil... but easiest way to do it
#define NOTNULL(VAR,FUNC_NAME) if(VAR==NULL) { \
                           imaqSetError(ERR_NULL_POINTER,FUNC_NAME); \
                           return RET_FAIL; \
                     }

// The below two as per WPILib/Vision2009/VisionAPI.cpp comments:
static const int RET_SUCCESS=1;
static const int RET_FAIL=0;

typedef enum {
	NIVISION_TYPE_IMAGE,
	NIVISION_TYPE_ROI
} nivision_type_t;

typedef struct {
	nivision_type_t data_type;
} base_object;

struct Image_struct : public base_object {
	nivision_type_t data_type;
	cv::Mat mat_data;
	ImageType type;
	ColorMode mode;
};

struct ROI_struct : public base_object {
	nivision_type_t data_type;
};

#endif // IMPL_H_INC
