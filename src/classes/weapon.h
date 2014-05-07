#ifndef _WEAPON_H
#define _WEAPON_H

#include "../classes/munition.h"

#include <string>

using namespace std;

/**
 * all weapons should inherit from this class
 */

class Weapon {
	public:
		Weapon(string name, Munition *munition);
		~Weapon();

		string get_name();
		int get_max_ammo();			// get maximum ammo
		int get_cur_ammo();			// get current ammo
		float get_rate();			// get the rate of fire
		Munition *get_munition();		// get munition type

		/**
		 * creates an instance of the munition and sets instance r and v
		 *
		 * delays in some way the firing if
		 *	current_time - last_fire < rate
		 *
		 * set last to update the last time a munition is fired and decrement ammo
		 */
		virtual void fire();			// override this

	private:
		string name;			// weapon name -- set in constructor
		int cur_ammo;
		int max_ammo;

		float rate;				// minimum time between shots
		float last;				// last time that a munition was fired
		Munition *munition;			// bullet type -- set in constructor
};

#endif
