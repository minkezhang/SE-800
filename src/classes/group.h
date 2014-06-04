#ifndef _GROUP_H
#define _GROUP_H

#include <vector>

#include "../classes/pilot.h"
#include "../classes/team.h"

class Pilot;
class Team;

class Group {
	public:
		Group(Team *team);
//		~Group();

		Team *get_team();
		int get_id();
		/**
		 * returns a escort from the group if no leader present (invoke select_leader)
		 *
		 * should never return NULL
		 */
		Pilot *get_leader();

		/* deletes matching pilot from this->escorts (if such a pilot exists) -- may need to call select_leader to find suitable candidate */
		void set_leader(Pilot *pilot);
		void del_leader();				// on ship destroy, reset and get new leader

		/* escort cannot be the current leader */
		void add_escort(Pilot *pilot);
		void del_escort(Pilot *pilot);

	private:
		int id;				// set in constructor
		Team *team;
		Pilot *leader;			// lead pilot -- other ships pilot around
		std::vector<Pilot *> escorts;

		/**
		 * select a pilot at random to be assigned the leadership role from group escorts
		 *
		 * consider possible race conditions here -- if the newly selected leader is marked is_dead at the same time
		 */
		Pilot *select_leader();
};

#endif
