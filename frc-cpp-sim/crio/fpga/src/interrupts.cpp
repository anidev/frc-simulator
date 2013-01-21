/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include <unordered_map>
#include "interfaces/tInterruptManager.h"
#include "interrupts.h"

interrupts* interrupts::global_instance=new interrupts();

interrupts* interrupts::get_instance() {
	return global_instance;
}

interrupts::interrupts() {
}

interrupts::~interrupts() {
}

void interrupts::register_callback(int mask,interrupts_callback callback) {
	callbacks.insert(std::pair<int,interrupts_callback>(mask,callback));
}

void interrupts::fire_interrupt(int mask) {
	for(auto iterate=callbacks.begin();iterate!=callbacks.end();iterate++) {
		if((iterate->first&mask)==mask) {
			interrupts_callback callback=iterate->second;
			callback.handler(mask,callback.param);
		}
	}
}
