#ifndef _PILOT_H
#define _PILOT_H

#include "../classes/group.h"
#include "../classes/ship.h"

/**
 * AI and players directly implement this interface
 */

class Pilot {
	public:
		Pilot(std::string name);
		~Pilot();

		int get_id();
		std::string get_name();
		Group *get_group();		// get current group
		Ship *get_ship();		// get current ship

		void set_group(Group *group);	// assign a new group to the pilot
		void set_ship(Ship *ship);	// assign a new ship to the pilot (on old ship destruction)

		/**
		 * calls get_group() and checks if the current pilot is the leader or a escort of the group
		 *
		 * this will influence AI behavior
		 *
		 * TODO: should be implemented in the AI concrete class and is called by control()
		 */
		int is_leader();

		/**
		 * called to update the ship trajectory
		 *
		 * consider ways in which to make scheduling this command more tractable
		 */
		virtual void control();	// override this

	private:
		std::string name;	// pilot name -- set in constructor

		int id;			// unique global ID -- set in constructor
		Group *group;		// the group of pilots
		Ship *ship;		// the current ship which the pilot is controlling
};

#endif
