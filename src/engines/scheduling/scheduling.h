#ifndef _SCHEDULING_H
#define _SCHEDULING_H

#include "../common/iengine.h"
#include "calendar.h"

class SchedulingEngine : public IEngine {
	public:
		void add_calendar(Calendar *calendar);
		void del_calendar(Calendar *calendar);

	private:
		Calendar *calendars;
};

#endif
