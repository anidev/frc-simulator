/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "nivision.h"
#include "nivision-impl.h"
#include "utils.h"

#define DEF_CODE2(SRC,DST) src_mode==IMAQ_##SRC&&dst_mode==IMAQ_##DST
#define DEF_CODE(SRC,DST) DEF_CODE2(SRC,DST)

int get_code(ColorMode src_mode,ColorMode dst_mode) {
	if(DEF_CODE(RGB,HSL)) {
		return CV_RGB2HLS;
	} else if(DEF_CODE(RGB,HSV)) {
		return CV_RGB2HSV;
	} else if(DEF_CODE(HSL,RGB)) {
		return CV_HLS2RGB;
	} else if(DEF_CODE(HSV,RGB)) {
		return CV_HSV2RGB;
	}
	std::cerr<<"ERROR nivision/src/impl.cpp::get_code: unrecognized src/dst mode combination."<<std::endl;
	return 0;
}

void convertModeTo(Image* image,ColorMode src_mode,ColorMode dst_mode) {
	cv::Mat dst_mat;
	int code=get_code(src_mode,dst_mode);
	cv::cvtColor(image->mat_data,dst_mat,code);
	image->mat_data=dst_mat;
	image->mode=dst_mode;
}

void niv::checkAndConvertMode(Image* image,ColorMode mode) {
	if(image->mode==mode) {
		return;
	}
	// if image is grayscale, make it RGB
	if(isGrayscale(image)) {
		cv::Mat dst_mat(image->mat_data.size(),image->mat_data.type());
		cv::cvtColor(image->mat_data,dst_mat,CV_GRAY2RGB);
		image->mat_data=dst_mat;
		image->type=IMAQ_IMAGE_RGB;
		image->mode=IMAQ_RGB;
	}
	// if src or dst is not RGB, then we need to do two conversions:
	// one to bring it RGB, and one to bring it to the desired mode.
	if(image->mode!=IMAQ_RGB&&mode!=IMAQ_RGB) {
		convertModeTo(image,image->mode,IMAQ_RGB);
	}
	convertModeTo(image,image->mode,mode);
}

bool niv::isGrayscale(Image* image) {
	ImageType type=image->type;
	return (type==IMAQ_IMAGE_U8||
	        type==IMAQ_IMAGE_U16||
	        type==IMAQ_IMAGE_I16||
	        type==IMAQ_IMAGE_SGL);
}

bool niv::isGrayscale(const Image* image) {
	return isGrayscale(const_cast<Image*>(image));
}
