#ifndef _MUNITION_H
#define _MUNITION_H

#include <vector>

#include "../engines/physics/projectile.h"

/**
 * bullets and bombs would inherit from tihs interface
 */

class Munition : public Projectile {
	public:
		Munition(std::vector<float> origin, std::vector<float> v);	// spawn in bullet with appropriate speed and direction
		~Munition();

		float get_range();						// origin - projectile.r

		/**
		 * if distance to surrounding ships < aoe, apply damage as returned by get_damage()
		 */
		virtual void explode();						// override this

	private:
		int render_class;
		std::vector<float> origin;					// object.r at which the bullet spawned -- set in constructor
		float range;							// distance the munition can travel -- set in constructor
		float aoe;							// area of effect

		/**
		 * for ships near the munition at explosion, get damage output
		 *
		 * called in explode()
		 */
		virtual int get_damage(float distance);				// override this
};

#endif
