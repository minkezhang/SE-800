#ifndef _GRID_H
#define _GRID_H

/**
 * grid system in an MD simulation to facilitate collision detection
 */

#include <vector>
#include <map>

#include "../../engines/physics/projectile.h"

class Grid {
	public:
		Grid(int id, std::vector<float> corner, std::vector<float> size);
		~Grid();

		std::vector<Projectile *> get_projectiles();				// returns a list of all projectiles within the grid
		Projectile *get_projectile(int id);					// returns NULL if the projectile is not found in the grid

		void add_projectile(Projectile *projectile);				// add an object to the grid
		void del_projectile(Projectile *projectile);				// removes an object from the grid

		std::vector<Projectile *> get_clippable();
		std::vector<Projectile *> get_unclippable();

		std::vector<float> get_size();
		std::vector<float> get_corner();

	private:
		int id;									// globally unique grid id -- set in constructor

		std::vector<float> corner;						// lowermost corner of the box -- set in constructor
		std::vector<float> size;						// dimensions of the box -- set in constructor

		std::map<int, Projectile *> clippable;					// list of clippable objects (objects whose is_clippable() function returns true)
		std::map<int, Projectile *> unclippable;				// list of unclippable objects (do not need to check unclippable objects colliding with unclippable objects)
};

#endif
