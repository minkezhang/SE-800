#include <algorithm>

#include "scheduling.h"

SchedulingEngine::SchedulingEngine() {
	status = UNINITIALIZED;
	signal = 1;
}
SchedulingEngine::~SchedulingEngine() {}

void SchedulingEngine::add_calendar(Calendar *calendar) {
	if(this->status < RUNNING) {
		this->calendars.push_back(calendar);
	}
}

void SchedulingEngine::ignite() { this->status = INITIALIZED; }

void SchedulingEngine::cycle() {
	this->status = RUNNING;
	while(this->signal != 0) {
		for(uint32_t i = 0; i < this->calendars.size(); i++) {
			
		}
	}
	this->shutdown();
}

void SchedulingEngine::shutdown() {
	this->status = STOPPED;
	this->signal = 0;
}
