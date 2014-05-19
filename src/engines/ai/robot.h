#ifndef _AIENGINE_H
#define _AIENGINE_H

#include <vector>

#include "../../classes/pilot.h"
#include "../../engines/physics/projectile.h"

/**
 * each AI pilot runs an AIEngine
 */

enum strategy_type {
        LEADER,
        ESCORT,
};

enum action_type {
	ATTACK,
	DEFEND,
	FLEE,
};

class Robot : public Pilot {
	public:
		Robot();

		void calculate_strategy();		// sets the state in which the AI should be in
		void calculate_action();		// given tactic, calculate the action that the ship should take -- flee, attack, etc.

	private:
		Ship *ship;				// current ship the AI is piloting -- from this, the TEAM and GROUP of the AI can be determined
		int strategy;				// current strategy the AI is implementing
		int action;

		void usurp();				// set AI as group leader -- sets AI internal state to calculate more complex behavior

		Projectile *get_objectives();		// call the PhysicsEngine for the Environment to determine nearby objectives

		/* simple actions -- if delay_time == 0, carry out action immediately, else finish action before delay_time is exceeded */
		void seek(std::vector<float> target, float delay);
		void attack(std::vector<float> target, float delay);
		void flee(std::vector<float> target, float delay);
		void pursue(std::vector<float> target, float delay);

		/* complex behaviors */
		void escort();				// flock with the current ship's group -- need to calculate the group velocity (perhaps cache it in the Group object)
};

#endif
