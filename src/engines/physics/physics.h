#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "../common/iengine.h"
#include "environment.h"

class PhysicsEngine : public IEngine {
	public:
		PhysicsEngine(int dimension);
		~PhysicsEngine();

	private:
		Environment *environment;
};

#endif
