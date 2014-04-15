#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "../common/iengine.h"

class Calendar {
	public:
		Calendar(float timestamp, IEngine engine);
		~Calendar();

		float get_timestamp();
		IEngine get_engine();

	private:
		float timestep;
		IEngine *engine;
};

#endif
