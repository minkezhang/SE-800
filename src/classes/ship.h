#ifndef _SHIP_H
#define _SHIP_H

#include <vector>

#include "../classes/weapon.h"
#include "../engines/physics/projectile.h"

/**
 * all ships directly implement this interface
 */

class Ship : public Projectile {
	public:
		Ship(int id, float mass, float max_tolerance, std::vector<float> d, float size, float preset_a, float preset_p_dot, float preset_r_dot);
		virtual int get_weapon_index();			// get current weapon index

		void add_weapon(Weapon *weapon);	// add a weapon to the ship
		void sel_weapon(int index);		// sets currently active weapon

		void fire();				// fires the currently active weapon

	private:
		std::vector<Weapon *> weapons;
		int weapon_index;		// current active weapon
		float max_v;			// maximum cruising speed of the ship -- limits set_v() (override function from IProjectile)
		float max_a;			// maximum acceleration of the ship -- limits set_a()
};

#endif
