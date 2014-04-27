#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "../common/engine.h"

class Calendar {
	public:
		Calendar(float timestamp, Engine *engine);
		~Calendar();

	private:
		float timestep;
		Engine *engine;
};

#endif
