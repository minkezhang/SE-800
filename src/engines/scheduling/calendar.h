#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "../common/engine.h"

class Calendar {
	public:
		Calendar(float timestamp, Engine *engine);
		~Calendar();

		void run();
	private:
		float timestep;
		Engine *engine;
};

#endif
