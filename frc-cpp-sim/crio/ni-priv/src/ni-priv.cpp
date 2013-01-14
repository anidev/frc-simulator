/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vxWorks.h>
#include <nivision-impl.h>
#include "ni-priv.h"

int Priv_SetWriteFileAllowed(uint32_t value) {
	FILE* file=std::fopen("write-test","w");
	if(file==NULL&&errno==EACCES) {
		std::cerr<<"No write access to current directory!"<<std::endl;
		std::cerr<<"Fatal error; aborting."<<std::endl;
		std::exit(1);
	}
	std::fclose(file);
	return 0;
}

int Priv_ReadJPEGString_C(Image* image,const unsigned char* input,uint32_t length) {
	cv::Mat src_mat(cv::Size(length,1),CV_8UC1,static_cast<void*>(const_cast<unsigned char*>(input)));
	image->mat_data=cv::imdecode(src_mat,-1);
	return 0;
}

uint32_t niTimestamp32() {
	return (uint32_t)niTimestamp64();
}

uint64_t niTimestamp64() {
//                       clocks      seconds       milli micro
	double micros=std::clock()*1.0/CLOCKS_PER_SEC*1000*1000;
	double ticks=micros/ticksPerMicro;
	return (uint64_t)ticks;
}
