#include "../interfaces/igroup.cpp"
#include "../interfaces/iship.cpp"

/**
 * AI and players directly implement this interface
 */

class IPilot {
	public:
		virtual std::string get_name();
		virtual IGroup *get_group();
		virtual int get_id();

		virtual void set_name(std::string name);
		virtual void set_group(IGroup *group);

		/**
		 * calls get_group() and checks if the current pilot is the leader or a escort of the group
		 *
		 * this will influence AI behavior
		 *
		 * TODO: should be implemented in the AI concrete class and is called by control()
		 */
		// virtual int is_leader();
		/**
		 * called to update the ship trajectory
		 *
		 * consider ways in which to make scheduling this command more tractable
		 */
		virtual void control();

	private:
		int id;
		std::string name;
		IGroup *group;		// the group of pilots
		IShip *ship;		// the current ship which the pilot is controlling
};
