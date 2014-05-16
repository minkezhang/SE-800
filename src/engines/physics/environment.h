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
		Grid *get_grid(Projectile *projectile);				// returns the grid in which the projectile is in (based on p->d)

		std::vector<float> get_size();					// gets size of the world
	private:
		std::vector<float> grid_size;					// size of the grids -- cached for ease-of-use
		std::vector<float> size;					// size of environment -- cached
		std::vector<int> n_grids;					// the number of grids per dimension
		std::map<std::vector<int>, Grid *> grids;
		Grid *get_grid(std::vector<int> id);				// returns the grid with the appropriate id
};

#endif
