#include "../interfaces/icube.cpp"
#include "../interfaces/iteam.cpp"

/**
 * consider implementing an IGame interface to handle network events and building and destroying the world
 */

class IWorld {
	public:
		virtual std::vector<int> get_dim();
		virtual ITeam *get_teams();

		/* spawns in the world and creates the cubes and teams */
		virtual void initialize();
		/* adds a new pilot into a <team, group> */
		virtual void join(IPilot *pilot);
		virtual void add_team();
		/* on a team meeting the losing condition, drop the team from the roster */
		virtual void del_team();
		/* execute upon the winning condition */
		virtual void win();

	private:
		ICube *cubes;
		std::vector<int> dim;
		ITeam *teams;
};
