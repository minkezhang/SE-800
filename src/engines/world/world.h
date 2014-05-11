#ifndef _WORLDENGINE_H
#define _WORLDENGINE_H

#include <vector>

#include "../common/engine.h"
#include "../scheduling/scheduling.h"
#include "../../classes/team.h"
#include "../../classes/ship.h"
#include "../../classes/pilot.h"
#include "../physics/physics.h"

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

class WorldEngine : Engine {
	public:
		WorldEngine(SchedulingEngine *scheduler);
		~WorldEngine();

		std::vector<Team *> get_teams();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		/* adds a new pilot into a <team, group> */
		Ship *join(Pilot *pilot);

		void add_team(Team *team);
		/* on a team meeting the losing condition, drop the team from the roster */
		void del_team(Team *team);

		/* execute upon the winning condition */
		void win();

	private:
		std::vector<Team *> teams;
		SchedulingEngine *scheduler;

		PhysicsEngine *physics_engine();
};

#endif
