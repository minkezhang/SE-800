#ifndef _SHIP_H
#define _SHIP_H

#include <vector>

#include "../engines/physics/projectile.h"

class Asteroid : public Projectile {
	public:
		Asteroid(int id, float mass, float max_tolerance, float size, float preset_p_dot, float preset_r_dot);
};

#endif
