/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include "nivision.h"
#include "nivision-impl.h"

//============================================================================
//  Image Management functions
//============================================================================

Image* imaqCreateImage(ImageType type,int borderSize) {
	// UNUSED: borderSize - no documentation
	// create 1x1 matrix because no size specified yet
	Image* image=new Image;
	image->data_type=NIVISION_TYPE_IMAGE;
	cv::Mat mat;
	switch(type) {
	case IMAQ_IMAGE_U8:
		mat.create(1,1,CV_8UC1);
		image->mode=(ColorMode)-1;
		// image->mode disregarded
		break;
	case IMAQ_IMAGE_U16:
		mat.create(1,1,CV_16UC1);
		image->mode=(ColorMode)-1;
		// image->mode disregarded
		break;
	case IMAQ_IMAGE_I16:
		mat.create(1,1,CV_16SC1);
		image->mode=(ColorMode)-1;
		// image->mode disregarded
		break;
	case IMAQ_IMAGE_SGL:
		mat.create(1,1,CV_32FC1);
		image->mode=(ColorMode)-1;
		// image->mode disregarded
		break;
	case IMAQ_IMAGE_RGB:
		mat.Mat::create(1,1,CV_8UC3);
		image->mode=IMAQ_RGB;
		break;
	case IMAQ_IMAGE_HSL:
		mat.Mat::create(1,1,CV_8UC3);
		image->mode=IMAQ_HSL;
		break;
	default:
		// assume RGB
		mat.Mat::create(1,1,CV_8UC3);
		image->mode=IMAQ_RGB;
		type=IMAQ_IMAGE_RGB;
		break;
	}
	image->type=type;
	image->mat_data=mat;
	return image;
}
