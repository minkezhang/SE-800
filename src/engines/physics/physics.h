#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include "../../engines/common/engine.h"
#include "../../engines/physics/environment.h"

class PhysicsEngine : public Engine {
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void set_environment(Environment *environment);

		/**
		 * public-facing functions -- given an object ID, modify the object in the world
		 */
		void toggle_a(int id);
		void toggle_p_dot(int id);
		void toggle_r_dot(int id);

	private:
		Environment *environment;
};

#endif
