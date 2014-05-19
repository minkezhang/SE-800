#ifndef _ASTEROID_H
#define _ASTEROID_H

#include <vector>

#include "../engines/physics/projectile.h"

class Asteroid : public Projectile {
	public:
		Asteroid(int id, float mass, float max_tolerance, std::vector<float> d, float size, float preset_p_dot, float preset_r_dot);
};

#endif
