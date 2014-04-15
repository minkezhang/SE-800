#include "../interfaces/icube.cpp"
#include "../interfaces/iteam.cpp"

class IWorld {
	public:
		virtual std::vector<int> get_dim();
		virtual ITeam *get_teams();

		virtual void add_team();

		/* lose condition */
		virtual void del_team();
	private:
		ICube *cubes;
		std::vector<int> dim;
		ITeam *teams;
};
