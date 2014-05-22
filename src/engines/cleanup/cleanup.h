#ifndef _CLEANUP_ENGINE_H
#define _CLEANUP_ENGINE_H

#include "../common/engine.h"
#include "../physics/physics.h"

class CleanupEngine : public Engine {
	public:
		CleanupEngine(Environment *environment);

		void ignite() override;
		void cycle() override;
		void shutdown() override;

	private:
		Environment *environment;
};

#endif
