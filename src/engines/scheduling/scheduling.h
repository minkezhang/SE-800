#ifndef _SCHEDULINGENGINE_H
#define _SCHEDULINGENGINE_H

#include <vector>

#include "../common/engine.h"
#include "calendar.h"

class SchedulingEngine : public Engine {
	public:
		SchedulingEngine();
		~SchedulingEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		void add_calendar(Calendar *calendar);

	private:
		std::vector<Calendar *> calendars;
};

#endif
