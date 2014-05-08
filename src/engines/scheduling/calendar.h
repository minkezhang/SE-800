#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "../common/engine.h"

class Calendar {
	public:
		Calendar(float timestamp, Engine *engine);
		~Calendar();

		void run();
		void shutdown();

		void set_signal();
	private:
		float timestep;
		Engine *engine;

		// run engine.cycle() until outside signal is received
		int signal;
};

#endif
