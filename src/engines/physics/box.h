#ifndef _BOX_H
#define _BOX_H

/**
 * grid system in an MD simulation to facilitate collision detection
 */

#include <vector>

#include "iprojectile.h"

class Box {
	public:
		/* corner represents the lowermost bound on the (x, y, ...) tuple */
		Box(int dimension, std::vector<float> size, std::vector<float> corner);
		~Box();

		void add_projectile(IProjectile *projectile);
		void del_projectile(IProjectile *projectile);

	private:
		int dimension;
		std::vector<float> size;
		std::vector<float> corner;
		IProjectile *projectiles;
};

#endif
