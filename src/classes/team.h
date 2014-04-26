#ifndef _TEAM_H
#define _TEAM_H

#include "../classes/group.h"

/**
 * each team consists of some groups of ships and is uniquely identified by a team id
 */

class Team {
	public:
		Team();
		~Team();

		int get_id();
		Group *get_groups();

		void add_group(Group *group);
		void del_group(Group *group);

	private:
		int id;
		Group *groups;
};

#endif
