/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <algorithm>
#include <cstdint>
#include <opencv2/core/core.hpp>
#include "nivision.h"
#include "nivision-impl.h"
#include "utils.h"

//============================================================================
//  Pixel Manipulation functions
//============================================================================

int imaqExtractColorPlanes(const Image* image,ColorMode mode,Image* plane1,Image* plane2,Image* plane3) {
	NOTNULL(image,"imaqExtractColorPlanes");
	if(mode==IMAQ_HSI) {
		imaqSetError(ERR_INVALID_COLOR_MODE,"imaqExtractColorPlanes");
		return RET_FAIL;
	}
	niv::checkAndConvertMode(const_cast<Image*>(image),mode);
	Image* img_planes[]={plane1,plane2,plane3};
	int num_channels=image->mat_data.channels();
	cv::Mat* mat_planes=new cv::Mat[num_channels];
	cv::split(image->mat_data,mat_planes);
	for(int i=0;i<std::min(num_channels,3);i++) {
		if(img_planes[i]==NULL) {
			continue;
		}
		img_planes[i]->mat_data=mat_planes[i];
		img_planes[i]->type=IMAQ_IMAGE_U8;
		img_planes[i]->mode=image->mode;
	}
	delete[] mat_planes;
	return RET_SUCCESS;
}

int imaqGetPixel(const Image* image,Point pixel,PixelValue* value) {
	NOTNULL(image,"imaqGetPixel");
	NOTNULL(value,"imaqGetPixel");
	cv::Vec3b mat_pixel;
	switch(image->type) {
	case IMAQ_IMAGE_HSL:
		niv::checkAndConvertMode(const_cast<Image*>(image),IMAQ_HSL);
		mat_pixel=image->mat_data.at<cv::Vec3b>(pixel.x,pixel.y);
		value->hsl.H=mat_pixel[0];
		value->hsl.S=mat_pixel[1];
		value->hsl.L=mat_pixel[2];
		break;
	case IMAQ_IMAGE_RGB:
		niv::checkAndConvertMode(const_cast<Image*>(image),IMAQ_RGB);
		mat_pixel=image->mat_data.at<cv::Vec3b>(pixel.x,pixel.y);
		value->rgb.R=mat_pixel[0];
		value->rgb.G=mat_pixel[1];
		value->rgb.B=mat_pixel[2];
		break;
	case IMAQ_IMAGE_U8:
		value->grayscale=image->mat_data.at<uint8_t>(pixel.x,pixel.y);
		break;
	default:
		return RET_FAIL;
	}
	return RET_SUCCESS;
}

int imaqReplaceColorPlanes(Image* dest,const Image* source,ColorMode mode,const Image* plane1,const Image* plane2,const Image* plane3) {
	NOTNULL(dest,"imaqReplaceColorPlanes");
	NOTNULL(source,"imaqReplaceColorPlanes");
	niv::checkAndConvertMode(const_cast<Image*>(source),mode);
	const Image* img_planes[]={plane1,plane2,plane3};
	int num_channels=source->mat_data.channels();
	cv::Mat* mat_planes=new cv::Mat[num_channels];
	cv::split(source->mat_data,mat_planes);
	num_channels=std::min(num_channels,3);
	cv::Mat* replaced_planes=new cv::Mat[num_channels];
	for(int i=0;i<num_channels;i++) {
		if(img_planes[i]==NULL) {
			replaced_planes[i]=mat_planes[i];
		} else {
			replaced_planes[i]=img_planes[i]->mat_data;
		}
	}
	cv::merge(replaced_planes,num_channels,dest->mat_data);
	delete[] replaced_planes;
	delete[] mat_planes;
	return RET_SUCCESS;
}
