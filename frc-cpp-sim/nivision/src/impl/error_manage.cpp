/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "nivision.h"
#include "nivision-impl.h"

int imaq_error=ERR_SUCCESS;
const char* imaq_error_func="";

//============================================================================
//  Error Management functions
//============================================================================

int imaqClearError(void) {
	imaq_error=ERR_SUCCESS;
	imaq_error_func="";
	return RET_SUCCESS;
}

char* imaqGetErrorText(int errorCode) {
	// TODO Proper IMAQ error messages:
	// maybe use some sort of script to convert error code
	// comments in nivision.h into an std::map.
	return const_cast<char*>("Generic error");
}

int imaqGetLastError(void) {
	return imaq_error;
}

const char* imaqGetLastErrorFunc(void) {
	return imaq_error_func;
}

int imaqSetError(int errorCode, const char* function) {
	imaq_error=errorCode;
	imaq_error_func=function;
	return RET_SUCCESS;
}
