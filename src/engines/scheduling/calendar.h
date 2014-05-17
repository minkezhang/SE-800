#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "../common/engine.h"

class Calendar {
	public:
		Calendar(float frequency, Engine *engine);
		~Calendar();

		void run();
		void shutdown();

	public:
		float timestep;			// time in seconds between each step
		Engine *engine;

		// run engine.cycle() until outside signal is received
		int signal;
};

#endif
