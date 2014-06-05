#ifndef _TEAM_H
#define _TEAM_H

#include "../classes/group.h"
#include <vector>

/**
 * each team consists of some groups of ships and is uniquely identified by a team id
 */

/**
 * circular dependencies
 *	cf. http://bit.ly/LlgKzd
 */
class Group;

class Team {
	public:
		Team();
		~Team();

		int get_id();
		std::vector<Group> get_groups();
		int get_groupNum();

		void add_group(Group *group);
		void del_group(Group *group);

	private:
		int id;
		int groupNum;
		std::vector<Group> groups;
};

#endif
