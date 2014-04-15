#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <vector>

#include "box.h"
#include "iprojectile.h"

class Environment {
	public:
		Environment(int dimension, std::vector<float> size);
		~Environment();

		void add_projectile(IProjectile *projectile);
		void del_projectile(IProjectile *projectile);

	private:
		int dimension;
		Box *boxes;
};

#endif
