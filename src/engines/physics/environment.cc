#include <stdio.h>
#include <cstddef>
#include "environment.h"
#include "../world/world.h"

Environment::Environment(std::vector<float> size, std::vector<int> n_grids) : size(size), n_grids(n_grids) {
	for(int i = 0; i < 3; i++) {
		grid_size.push_back(size.at(i) / n_grids.at(i));
	}
	for(int i = 0; i < n_grids.at(0); i++) {
		for(int j = 0; j < n_grids.at(1); j++) {
			for(int k = 0; k < n_grids.at(2); k++) {
				grids[{ i, j, k }] = new Grid({ i, j, k }, { i * grid_size.at(0), j * grid_size.at(1), k * grid_size.at(2) }, grid_size);
			}
		}
	}
}

void Environment::add_projectile(Projectile *p) { this->get_grid(p)->add_projectile(p); }
void Environment::del_projectile(Projectile *p) { this->get_grid(p)->del_projectile(p); }

Projectile *Environment::get_projectile(int id) {
	Projectile *p = NULL;
	for(std::vector<Grid *>::iterator i = this->get_grids().begin(); i != this->get_grids().end(); ++i) {
		p = (*i)->get_projectile(id);
		if(p != NULL) {
			break;
		}
	}
	return(p);
}

std::vector<Projectile *> Environment::get_clippable() {
	std::vector<Projectile *> p;
	for(long unsigned int i = 0; i < this->get_grids().size(); i++) {
		std::vector<Projectile *> grid_p = this->get_grids().at(i)->get_clippable();
		p.insert(p.end(), grid_p.begin(), grid_p.end());
	}
	return(p);
}

std::vector<Projectile *> Environment::get_unclippable() {
	std::vector<Projectile *> p;
	for(long unsigned int i = 0; i < this->get_grids().size(); i++) {
		std::vector<Projectile *> grid_p = this->get_grids().at(i)->get_unclippable();
		p.insert(p.end(), grid_p.begin(), grid_p.end());
	}
	return(p);
}

// optimization -- use the grid system to find nearby objects
std::vector<Projectile *> Environment::get_neighbors(Projectile *p) {
	std::vector<Projectile *> neighbors;

	std::vector<int> id = this->get_grid(p)->get_id();
	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			for(int k = -1; k < 2; k++) {
				Grid *g = this->get_grid({ id.at(0) + i, id.at(1) + j, id.at(2) + k });
				std::vector<Projectile *> clippable = g->get_clippable();
				std::vector<Projectile *> unclippable = g->get_unclippable();
				neighbors.insert(neighbors.end(), clippable.begin(), clippable.end());
				neighbors.insert(neighbors.end(), unclippable.begin(), unclippable.end());
			}
		}
	}
	return(neighbors);
}

/**
 * find grid via some sort of hashing based on grid->id and n_grids
 *
 * returns the grid which the projectile could possibly be located in
 * returns NULL if the projectile is not found
 */
Grid *Environment::get_grid(Projectile *p) {
	Grid *g = NULL;
	// special case
	if(this->grids.size() == 0) {
		return(g);
	}
	std::vector<float> d = p->get_d();
	// (int) of a float auto-truncates
	//	cf. http://bit.ly/1k6dyEW
	std::vector<int> id = { (int) (d.at(0) / this->grid_size.at(0)), (int) (d.at(1) / this->grid_size.at(1)), (int) (d.at(2) / this->grid_size.at(2)) };
	std::map<std::vector<int>, Grid *>::iterator targ = this->grids.find(id);
	if(targ != this->grids.end()) {
		g = targ->second;
	}
	return(g);
}

/**
 * finds a grid based in the id -- auto-wraps to the other side if grid id out of bounds
 * returns NULL if no grid found
 */
Grid *Environment::get_grid(std::vector<int> id) {
	Grid *g = NULL;
	for(int dim = 0; dim < 3; dim++) {
		if(id.at(dim) < 0) {
			id.at(dim) += this->n_grids.at(dim);
		} else if(id.at(dim) >= this->n_grids.at(dim)) {
			id.at(dim) -= this->n_grids.at(dim);
		}
	}
	std::map<std::vector<int>, Grid *>::iterator targ = this->grids.find(id);
	if(targ != this->grids.end()) {
		g = (*targ).second;
	}
	return(g);
}

std::vector<Grid *> Environment::get_grids() {
	std::vector<Grid *> g;
	for(std::map<std::vector<int>, Grid *>::iterator i = this->grids.begin(); i != this->grids.end(); ++i) {
		g.push_back((*i).second);
	}
	return(g);
}

std::vector<float> Environment::get_size() { return(this->size); }
