#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <vector>

#include "grid.h"
#include "projectile.h"

class Environment {
	public:
		Environment(std::vector<float> size, std::vector<int> n_grids);	// constructor -- automatically subdivides space into n_grid chunks
		~Environment();

		void add_projectile(Projectile *projectile);			// finds the appropriate grid in which to add an object
		void del_projectile(Projectile *projectile);			// deletes the object from the appropriate grid

		Projectile *get_neighbors(int id);				// returns a list of all nearby projectiles (objects within one grid space and in direction of travel), given projectile ID

	private:
		Grid *grids;
};

#endif
