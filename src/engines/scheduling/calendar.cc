#include <thread>
#include <chrono>

#include <ctime>
#include <time.h>

#include "calendar.h"

Calendar::Calendar(float frequency, Engine *engine) : engine(engine) {
	this->timestep = 1.0 / frequency;
	signal = 1;
}

Calendar::~Calendar() {}

void Calendar::run() {
	clock_t timekeeper;
	float elapsed_time;
	while(this->signal) {
		timekeeper = clock();
		this->engine->cycle();
		timekeeper = clock() - timekeeper;
		elapsed_time = ((float) timekeeper) / CLOCKS_PER_SEC;
		if(elapsed_time < this->timestep) {
			/**
			 * high resolution sleep functions
			 *	cf. http://bit.ly/QUnZzL
			 *	cf. http://bit.ly/1gTF9EL
			 */
			std::this_thread::sleep_for(std::chrono::duration<float>(this->timestep - elapsed_time));
		}
	}
}

void Calendar::shutdown() {
	this->signal = 0;
	this->engine->shutdown();
}
