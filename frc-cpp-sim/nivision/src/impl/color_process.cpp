/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "nivision.h"
#include "nivision-impl.h"
#include "utils.h"

//============================================================================
//  Color Processing functions
//============================================================================

int imaqColorEqualize(Image* dest,const Image* source,int colorEqualization) {
	if(colorEqualization==TRUE) {
		// equalize only the luminance plane,
		// so convert to HSL
		niv::checkAndConvertMode(const_cast<Image*>(source),IMAQ_HSL);
		cv::Mat lum_mat(source->mat_data.size(),CV_8UC1);
		// HLS: assuming luminance is second plane
		int pairs1[]={1,0};
		cv::mixChannels(&source->mat_data,1,&lum_mat,1,pairs1,1);
		cv::Mat lum_mat_eq;
		cv::equalizeHist(lum_mat,lum_mat_eq);
		int pairs2[]={0,1};
		cv::mixChannels(&lum_mat_eq,1,&dest->mat_data,1,pairs2,1);
		return RET_SUCCESS;
	} else {
		// equalize all planes
		// extract each plane, equalize separately,
		// and merge back together
		// color space does not matter
		cv::Mat* planes;
		cv::Mat* planes_eq;
		int num_planes;
		if(niv::isGrayscale(source)) {
			planes=const_cast<cv::Mat*>(&source->mat_data);
			num_planes=1;
		} else {
			num_planes=source->mat_data.channels();
			planes=new cv::Mat[num_planes];
			cv::split(source->mat_data,planes);
		}
		planes_eq=new cv::Mat[num_planes];
		for(int i=0;i<num_planes;i++) {
			cv::equalizeHist(planes[i],planes_eq[i]);
		}
		cv::merge(planes_eq,num_planes,dest->mat_data);
		delete[] planes_eq;
		if(!niv::isGrayscale(source)) {
			delete[] planes;
		}
		return RET_SUCCESS;
	}
}

int imaqColorThreshold(Image* dest,const Image* source,int replaceValue,ColorMode mode,const Range* plane1Range,const Range* plane2Range,const Range* plane3Range) {
	NOTNULL(dest,"imaqColorThreshold");
	NOTNULL(source,"imaqColorThreshold");
	if(mode==IMAQ_HSI) {
		imaqSetError(ERR_INVALID_COLOR_MODE,"imaqColorThreshold");
		return RET_FAIL;
	}
	int range1_min=(plane1Range==NULL?0:plane1Range->minValue);
	int range1_max=(plane1Range==NULL?0:plane1Range->maxValue);
	int range2_min=(plane2Range==NULL?0:plane2Range->minValue);
	int range2_max=(plane2Range==NULL?0:plane2Range->maxValue);
	int range3_min=(plane3Range==NULL?0:plane3Range->minValue);
	int range3_max=(plane3Range==NULL?0:plane3Range->maxValue);
	// See if source image is in the colorspace specified by mode;
	// if not, then convert it immediately.
	niv::checkAndConvertMode(const_cast<Image*>(source),mode);
	cv::Mat src_mat=source->mat_data;
	dest->mat_data.create(src_mat.size(),CV_8UC1);
	for(int y=0;y<src_mat.rows;y++) {
		for(int x=0;x<src_mat.cols;x++) {
			cv::Vec3b pixel=src_mat.at<cv::Vec3b>(x,y);
			// assuming ranges are inclusive
			if(pixel[0]>=range1_min&&pixel[0]<=range1_max&&
			   pixel[1]>=range2_min&&pixel[1]<=range2_max&&
			   pixel[2]>=range3_min&&pixel[2]<=range3_max) { // in the range
				dest->mat_data.at<uint8_t>(x,y)=replaceValue;
			} else {
				dest->mat_data.at<uint8_t>(x,y)=0;
			}
		}
	}
	return RET_SUCCESS;
}
