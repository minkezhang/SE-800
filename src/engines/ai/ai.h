#ifndef _AIENGINE_H
#define _AIENGINE_H

#include <map>
#include <mutex>

#include "../../classes/pilot.h"
#include "../../classes/ship.h"
#include "../common/engine.h"

class AIEngine : public Engine {
	public:
		AIEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		void add_pilot(Pilot *pilot);
		void del_pilot(Pilot *pilot);

	private:
		std::map<int, Pilot *> players;
		std::map<int, Pilot *> robots;

		std::mutex l;				// lock when modifying players and robots
};

#endif
