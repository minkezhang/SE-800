#include <cstddef>
#include "environment.h"
#include "../world/world.h"

Environment::Environment(std::vector<float> size, std::vector<int> n_grids) : n_grids(n_grids) {
	std::vector<float> grid_size;
	for(int i = 0; i < 3; i++) {
		grid_size.push_back(size.at(i) / n_grids.at(i));
	}
	for(int i = 0; i < n_grids.at(0); i++) {
		for(int j = 0; j < n_grids.at(1); j++) {
			for(int k = 0; k < n_grids.at(2); k++) {
				grids.push_back(new Grid(i * j * k, { i * grid_size.at(0), j * grid_size.at(1), k * grid_size.at(2) }, grid_size));
			}
		}
	}
}

void Environment::add_projectile(Projectile *p) { this->get_grid(p)->add_projectile(p); }
void Environment::del_projectile(Projectile *p) { this->get_grid(p)->del_projectile(p); }

Projectile *Environment::get_projectile(int id) {
	WorldEngine *w = new WorldEngine(NULL);
	return w->join(NULL);
}

// optimization -- use the grid system to find nearby objects
std::vector<Projectile *> Environment::get_neighbors(int id) {
	std::vector<Projectile *> p;
	for(std::vector<Grid *>::iterator i = this->grids.begin(); i != this->grids.end(); ++i) {
		std::vector<Projectile *> grid_p = (*i)->get_projectiles();
		p.insert(p.end(), grid_p.begin(), grid_p.end());
	}
	return(p);
}
/**
 * returns the grid which the projectile could possibly be located in
 * returns NULL if the projectile is not found
 */
// optimization -- find grid via some sort of hashing based on grid->id and n_grids
Grid *Environment::get_grid(Projectile *p) {
	Grid *g = NULL;
	std::vector<float> d = p->get_d();
	for(std::vector<Grid *>::iterator i = this->grids.begin(); i != this->grids.end(); ++i) {
		g = *i;
		std::vector<float> corner = g->get_corner();
		std::vector<float> size = g->get_size();
		// check if the projectile is within the grid
		int within = 0;
		for(int j = 0; j < 3; j++) {
			if((corner.at(j) < d.at(j)) && (d.at(j) < (corner.at(j) + size.at(j)))) {
				within++;
				break;
			}
			break;
		}
		if(within == 3) {
			break;
		}
	}
	return(g);
}
