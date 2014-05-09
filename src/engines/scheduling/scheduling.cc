#include <stdio.h>
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

void SchedulingEngine::ignite() {
	for(uint32_t i = 0; i < this->calendars.size(); i++) {
		std::thread t = std::thread(&Calendar::run, this->calendars.at(i));
		this->threads.push_back(&t);
	}
	this->status = INITIALIZED;
}

void SchedulingEngine::cycle() {
	this->status = RUNNING;
}

void SchedulingEngine::shutdown() {
	this->status = STOPPED;
	this->signal = 0;
	for(uint32_t i = 0; i < this->calendars.size(); i++) {
		this->calendars.at(i)->shutdown();
	}
	for(uint32_t i = 0; i < this->calendars.size(); i++) {
		this->threads.at(i)->join();
	}
}
