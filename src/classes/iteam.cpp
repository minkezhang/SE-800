#include "../interfaces/igroup.cpp"

/**
 * each team consists of some groups of ships and is uniquely identified by a team id
 */

class ITeam {
	public:
		virtual int get_id();
		virtual IGroup *get_groups();

		virtual void add_group(IGroup *group);
		virtual void del_group(IGroup *group);

	private:
		int id;
		IGroup *groups;
};
