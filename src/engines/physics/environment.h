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
		void del_projectile(Projectile *projectile);			// deletes the object from the appropriate grid

		Projectile *get_projectile(int id);

		std::vector<Projectile *> get_clippable();
		std::vector<Projectile *> get_unclippable();
		std::vector<Projectile *> get_neighbors(Projectile *projectile);// returns a list of all nearby projectiles (objects within one grid space and in direction of travel), given projectile ID

		std::vector<Grid *> get_grids();
	private:

		std::vector<int> n_grids;					// the number of grids per dimension
		Grid *get_grid(Projectile *projectile);				// returns the grid in which the projectile is in (based on p->d)
		std::vector<Grid *> grids;
};

#endif
