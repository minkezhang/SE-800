#ifndef _SCHEDULINGENGINE_H
#define _SCHEDULINGENGINE_H

#include "../common/engine.h"
#include "calendar.h"

class SchedulingEngine : public Engine {
	public:
		SchedulingEngine();
		~SchedulingEngine();

		void add_calendar(Calendar *calendar);
		void del_calendar(Calendar *calendar);

	private:
		Calendar *calendars;
};

#endif
