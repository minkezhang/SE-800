#ifndef _CLEANUP_ENGINE_H
#define _CLEANUP_ENGINE_H

#include "../common/engine.h"
#include "../physics/physics.h"
#include "../../classes/event.h"
#include <mutex>

class CleanupEngine : public Engine {
	public:
		CleanupEngine(Environment *environment);

		void ignite() override;
		void cycle() override;
		void shutdown() override;
		std::vector<Event *> send_event_vec();

	private:
		Environment *environment;
		std::map<std::vector<int>, Event *> event_list;
		std::mutex event_list_lock;
};

#endif
