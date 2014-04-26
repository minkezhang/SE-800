#ifndef _WORLDENGINE_H
#define _WORLDENGINE_H

#include "../interfaces/team.h"

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

class WorldEngine {
	public:
		WorldEngine();
		~WorldEngine();

		Team *get_teams();

		/* adds a new pilot into a <team, group> */
		void join(Pilot *pilot);

		void add_team();
		/* on a team meeting the losing condition, drop the team from the roster */
		void del_team();
		/* execute upon the winning condition */

		void win();

	private:
		Team *teams;
};

#endif
