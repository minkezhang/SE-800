#ifndef _WORLDENGINE_H
#define _WORLDENGINE_H

#include <vector>
#include <map>

#include "../common/engine.h"
#include "../scheduling/scheduling.h"
#include "../../classes/team.h"
#include "../../classes/ship.h"
#include "../../classes/pilot.h"
#include "../physics/physics.h"
#include "../ai/ai.h"
#include <mutex>

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

class WorldEngine : Engine {
	public:
		WorldEngine(SchedulingEngine *scheduler);
		~WorldEngine();

		std::vector<Team *> get_teams();
		std::mutex obj_count_lock;
		int obj_count;

		void ignite(char *mode);
		void ignite(char *mode, int n_teams);
		void cycle() override;
		void shutdown() override;

		/* adds a new pilot into a <team, group> */
		Ship *join(Pilot *pilot);

		void set_ai_engine(AIEngine *ai_engine);
		void set_physics_engine(PhysicsEngine *physics_engine);

		void add_team(Team *team);
		/* on a team meeting the losing condition, drop the team from the roster */
		void del_team(Team *team);

		/* execute upon the winning condition */
		void win();

		PhysicsEngine *get_physics_engine();
		AIEngine *get_ai_engine();

	private:
		std::map<int, Team *> teams;
		SchedulingEngine *scheduler;
		PhysicsEngine *physics_engine;				// is a shortcut to the physics engine of the game running in the scheduler
		AIEngine *ai_engine;
};

#endif
