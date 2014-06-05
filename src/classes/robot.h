#ifndef _ROBOT_H
#define _ROBOT_H

#include <vector>

#include "pilot.h"
#include "ship.h"
#include "../engines/physics/projectile.h"

/**
 * each AI pilot runs an AIEngine
 */

enum strategy_type {
        LEADER_STRAT,
        ESCORT_STRAT
};

enum action_type {
	ARRIVE_AT,
    ATTACK,
    FOLLOW,
    FLEE,
    ESCORT
};

class Robot : public Pilot {
	public:
		Robot(Environment *environ);
		void act();
		void set_ship(Ship *ship);

//		void calculate_strategy();		// sets the state in which the AI should be in
//		void calculate_action();		// given tactic, calculate the action that the ship should take -- flee, attack, etc.

	private:
		Ship *ship;				// current ship the AI is piloting -- from this, the TEAM and GROUP of the AI can be determined
		Environment * env;
		strategy_type strategy;				// current strategy the AI is implementing
		action_type action;

		void usurp();				// set AI as group leader -- sets AI internal state to calculate more complex behavior

		std::vector<Projectile *> get_objectives(Environment *environment);		// call the PhysicsEngine for the Environment to determine nearby objectives
    
        std::vector<float> target;
        Projectile *target_obj;
        float prev_p_dot;
        float prev_r_dot;
		/* simple actions -- if delay_time == 0, carry out action immediately, else finish action before delay_time is exceeded */
		//void seek(std::vector<float> target, float delay);
		//void attack(std::vector<float> target, float delay);
		//void flee(std::vector<float> target, float delay);
		//void pursue(std::vector<float> target, float delay);

		/* complex behaviors */
		//void escort();				// flock with the current ship's group -- need to calculate the group velocity (perhaps cache it in the Group object)
};

#endif
