#include "calendar.h"

Calendar::Calendar(float timestep, Engine *engine) : timestep(timestep), engine(engine) {
	signal = 1;
}

Calendar::~Calendar() {}

void Calendar::run() {
	while(this->signal) {
		// sleep for timestep
		this->engine->cycle();
	}
}

void Calendar::shutdown() {
	this->signal = 0;
	this->engine->shutdown();
}
