/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "FRCComm.h"

#include <iostream>
#include <cstdint>
#include <semaphore.h>
#include <semLib.h>

typedef struct {
	UINT16 digital;
	UINT16 digital_oe;
	UINT16 digital_pe;
	UINT16 pwm_compare[4];
	UINT16 pwm_period[2];
	UINT8 dac[2];
	UINT8 leds;
	union {
		struct {
			// Bits are inverted from cypress fw because of big-endian!
			UINT8 pwm_enable : 4;
			UINT8 comparator_enable : 2;
			UINT8 quad_index_enable : 2;
		};
		UINT8 enables;
	};
	UINT8 fixed_digital_out;
} output_t;  //data to IO (23 bytes)

typedef struct {
	UINT8 size; // Must be 25 (size remaining in the block not counting the size variable)
	UINT8 id; // Must be 18
	output_t data;
	UINT8 flags;
} status_block_t; // from WPILib/DriverStationEnhancedIO.h

// Some documentation for FRCComm.h available in the Java docs:
// http://k.thekks.net/frcdoc/edu/wpi/first/wpilibj/communication/FRCControl.html
// oh, the irony...

SEM_ID data_sem;
int packet_index=0;

int getCommonControlData(FRCCommonControlData* data, int wait_ms) {
	// until netcontrol is implemented, just give hardcoded values
	data->packetIndex=packet_index++;
	data->enabled=0;
	data->autonomous=0;
	data->fmsAttached=0;
	data->dsDigitalIn=0; // apparently digitalinputs on driverstation... no idea
	data->teamID=612; // 6 WHAT? 612!
	data->dsID_Alliance=0;
	data->dsID_Position=0;
	int8_t stickAxes[6]={0,0,0,0,0,0};
	std::copy(stickAxes,stickAxes+6,data->stick0Axes);
	std::copy(stickAxes,stickAxes+6,data->stick1Axes);
	std::copy(stickAxes,stickAxes+6,data->stick2Axes);
	data->stick0Buttons=data->stick1Buttons=data->stick2Buttons=0;
	data->analog1=data->analog2=data->analog3=data->analog4=0;
	data->cRIOChecksum=data->FPGAChecksum0=data->FPGAChecksum1=data->FPGAChecksum2=data->FPGAChecksum3=0;
	char version_data[8]={0,0,0,0,0,0,0,0};
	std::copy(version_data,version_data+8,data->versionData);
	return 0;
}

int getDynamicControlData(UINT8 type,char* dynamicData,INT32 maxLength,int wait_ms) {
	// don't really know what this is supposed to be for...
	// even if I did, sane values can't be returned
	// because netcontrol has not yet been implemented.
	// so, just return 1 to indicate no new data...
	return 1;
}

int setErrorData(const char* errors,int errors_len,int wait_ms) {
	// until netcontrol is implemented, just cout
	std::cout<<"Errors: "<<errors<<std::endl;
	return 0; // what the heck am I supposed to return??
}

void setNewDataSem(SEM_ID sem) {
	data_sem=sem;
	// so what the heck am I supposed to do with this semaphore?
}

int setStatusData(float battery,uint8_t dsDigitalOut,uint8_t updateNumber,
                  const char* userDataHigh,int userDataHighLength,
                  const char* userDataLow,int userDataLowLength,int wait_ms) {
	// do something until netcontrol is implemented
	std::cout<<"Update "<<updateNumber<<": battery is at "<<battery<<"."<<std::endl;
	return 0;
}

int setUserDsLcdData(const char* lcd_data,int lcd_data_len,int wait_ms) {
	// until netcontrol is implemented, just cout
	std::cout<<"LCD data: "<<lcd_data<<std::endl;
	return 0;
}

void FRC_NetworkCommunication_getVersionString(char *version) {
	version=const_cast<char*>("2012");
}

void FRC_NetworkCommunication_observeUserProgramStarting() {
	std::cout<<"frccomm: user program STARTING"<<std::endl;
}

void FRC_NetworkCommunication_observeUserProgramDisabled() {
	std::cout<<"frccomm: user program DISABLED"<<std::endl;
}

void FRC_NetworkCommunication_observeUserProgramAutonomous() {
	std::cout<<"frccomm: user program AUTONOMOUS"<<std::endl;
}

void FRC_NetworkCommunication_observeUserProgramTeleop() {
	std::cout<<"frccomm: user program TELEOP"<<std::endl;
}

int overrideIOConfig(const char* config_chars,int wait_ms) {
//	status_block_t* config=reinterpret_cast<status_block_t*>(const_cast<char*>(config_chars)); // unused  currently
	// until netcontrol is implemented, do absolutely nothing whatsoever.
	return 0;
}
