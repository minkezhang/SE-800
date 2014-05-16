#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include "../../engines/common/engine.h"
#include "../../engines/physics/environment.h"
#include <cmath>

class PhysicsEngine : public Engine {
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void set_environment(Environment *environment);
		Environment *get_environment();

		/**
		 * public-facing functions -- given an object ID, modify the object in the world
		 *	values are between [ -1, 1 ], where values < 0 indicate braking (toggle_a) or counter-clockwise intensity (toggle_..._dot)
		 */
		void toggle_a(int id, int val);
		void toggle_p_dot(int id, float val);
		void toggle_r_dot(int id, float val);

		void ignite() override;
		void cycle() override;
		void shutdown() override;

	private:
		Environment *environment;
		void apply_rotation(float angle, int flag, Projectile *p);
		void verlet_step(float t, Projectile *p);
		void collision_check(Projectile *p);
		void collide(Projectile *p, Projectile *q);
};

#endif
