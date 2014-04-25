#ifndef _AIENGINE_H
#define _AIENGINE_H

#include <vector>

#include "../../classes/ship.h"
#include "../physics/projectile.h"

/**
 * each AI pilot runs an AIEngine
 */

class AIEngine : public Engine {
	public:
		AIEngine();
		~AIEngine();

		void set_ship(Ship *ship);		// set an AI as the command of a particular ship
		void usurp();				// set AI as group leader -- sets AI internal state to calculate more complex behavior

	private:
		Ship *ship;				// current ship the AI is piloting -- from this, the TEAM and GROUP of the AI can be determined
		int strategy;				// current strategy the AI is implementing
		int action;

		Projectile *get_objectives();		// call the PhysicsEngine for the Environment to determine nearby objectives

		void calculate_strategy();		// sets the state in which the AI should be in
		void calculate_action();		// given tactic, calculate the action that the ship should take -- flee, attack, etc.

		/* simple actions -- if delay_time == 0, carry out action immediately, else finish action before delay_time is exceeded */
		void seek(std::vector<float> target, float delay);
		void attack(std::vector<float> target, float delay);
		void flee(std::vector<float> target, float delay);
		void pursue(std::vector<float> target, float delay);

		/* complex behaviors */
		void escort();				// flock with the current ship's group -- need to calculate the group velocity (perhaps cache it in the Group object)

		/**
		 * these should be under the ControlEngine -- Steven and Justin should be working on this interface
		 * Controls --
		 *	void thrust();
		 *	void left();
		 *	void right();
		 *	void brake();
		 */
};

#endif
