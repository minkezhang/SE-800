#ifndef _WORLDENGINE_H
#define _WORLDENGINE_H

#include <vector>

#include "../common/engine.h"
#include "../../classes/team.h"

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

class WorldEngine : Engine {
	public:
		WorldEngine();
		~WorldEngine();

		std::vector<Team *> get_teams();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		/* adds a new pilot into a <team, group> */
		void join(Pilot *pilot);

		void add_team(Team *team);
		/* on a team meeting the losing condition, drop the team from the roster */
		void del_team(Team *team);

		/* execute upon the winning condition */
		void win();

	private:
		std::vector<Team *> teams;
};

#endif
