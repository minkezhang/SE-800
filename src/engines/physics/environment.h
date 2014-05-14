#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include "../../engines/physics/grid.h"
#include "../../engines/physics/projectile.h"
#include <vector>

class Environment {
	public:
		Environment(std::vector<float> size, std::vector<int> n_grids);	// constructor -- automatically subdivides space into n_grid chunks
		~Environment();

		void add_projectile(Projectile *projectile);			// finds the appropriate grid in which to add an object
		void del_projectile(int id);					// deletes the object from the appropriate grid

		std::vector<Projectile *> get_neighbors(int id);		// returns a list of all nearby projectiles (objects within one grid space and in direction of travel), given projectile ID

		Projectile *get_projectile(int id);				// gets a projectile by ID

	private:
		std::vector<Grid *> grids;
};

#endif
