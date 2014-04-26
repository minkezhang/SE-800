#ifndef _GRID_H
#define _GRID_H

/**
 * grid system in an MD simulation to facilitate collision detection
 */

#include <vector>

#include "../../engines/physics/projectile.h"

class Grid {
	public:
		Grid(int id, std::vector<float> size, std::vector<float> corner);
		~Grid();

		Projectile *get_projectiles();			// returns a list of all projectiles within the grid

		void add_projectile(Projectile *projectile);	// add an object to the grid
		void del_projectile(Projectile *projectile);	// removes an object from the grid

	private:
		int id;						// globally unique grid id -- set in constructor

		std::vector<float> size;			// dimensions of the box -- set in constructor
		std::vector<float> corner;			// lowermost corner of the box -- set in constructor
		Projectile *clippable_projectiles;		// list of clippable objects (objects whose is_clippable() function returns true)
		Projectile *unclippable_projectiles;		// list of unclippable objects (do not need to check unclippable objects colliding with unclippable objects)
};

#endif
