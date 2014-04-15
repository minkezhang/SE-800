#include "../interfaces/ipilot.cpp"
#include "../interfaces/iteam.cpp"

class IGroup {
	public:
		virtual ITeam *get_team();
		virtual IPilot *get_pilots();
		virtual int get_id();
		/**
		 * returns a escort from the group if no leader present (invoke select_leader)
		 *
		 * should never return NULL
		 */
		virtual IPilot *get_leader();

		virtual void set_team(ITeam *team);
		/* deletes matching pilot from this->escorts (if such a pilot exists) */
		virtual void set_leader(IPilot *pilot);
		/* escort cannot be the current leader */
		virtual void add_escort(IPilot *pilot);
		virtual void del_escort(IPilot *pilot);

	private:
		int id;
		ITeam *team;
		IPilot *leader;
		IPilot *escorts;

		/* makes sure the id doesn't collide with any other group ids on the team */
		virtual void set_id(int id);

		/**
		 * select a pilot at random to be assigned the leadership role from group escorts
		 *
		 * consider possible race conditions here -- if the newly selected leader is marked is_dead at the same time
		 */
		virtual IPilot *select_leader();
};
