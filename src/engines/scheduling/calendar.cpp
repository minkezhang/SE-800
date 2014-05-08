#include "calendar.h"

Calendar::Calendar(float timestamp, Engine *engine) {
	timestamp = timestamp;
	engine = engine;
}

Calendar::~Calendar() {}

void Calendar::run() {
	// sleep for timestamp
	this->engine->cycle();
}
