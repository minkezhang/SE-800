#include "calendar.h"

Calendar::Calendar(float timestamp, Engine *engine) {
	timestamp = timestamp;
	engine = engine;
	signal = 1;
}

Calendar::~Calendar() {}

void Calendar::run() {
	while(this->signal) {
		// sleep for timestamp
		this->engine->cycle();
	}
}

void Calendar::shutdown() {
	this->engine->shutdown();
}

void Calendar::set_signal() {
	this->signal = 0;
}
