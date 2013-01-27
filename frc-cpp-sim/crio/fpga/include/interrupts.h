/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#ifndef INTERRUPT_H_INC
#define INTERRUPT_H_INC

#include <unordered_map>
#include "interfaces/tInterruptManager.h"

struct interrupts_callback {
	nFPGA::tInterruptHandler handler;
	void* param;
};

class interrupts {
private:
	static interrupts* global_instance;

	std::unordered_multimap<int,interrupts_callback> callbacks;

	interrupts();
	~interrupts();
public:
	static const int TIMER=1<<28;

	static interrupts* get_instance();

	void register_callback(int,interrupts_callback);
	void fire_interrupt(int);
};

#endif // INTERRUPT_H_INC
