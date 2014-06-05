#include <vector>
#include <math.h>
#include <iostream>

#include "pilot.h"
#include "robot.h"
#include "../engines/physics/environment.h"

/**
 * each AI pilot runs an AIEngine
 */
Robot::Robot(Environment *environ) : Pilot("AI", 0) {
	this->env = environ;
	this->ship = NULL;
	this->action = action_type::ARRIVE_AT;
	this->strategy = strategy_type::ESCORT_STRAT;
	this->prev_r_dot = 0.0;
	this->prev_p_dot = 0.0;
	std::vector<float> tar = { 0.0, 100.0, 50.0 };
	this->target = tar;
}

void Robot::set_ship(Ship *ship) {
	this->ship_l.lock();
	this->ship = ship;
	//this->ship->set_a(1.0);
	this->ship_l.unlock();
}

//Robot::calculate_strategy();		// sets the state in which the AI should be in
//Robot::calculate_action();		// given tactic, calculate the action that the ship should take -- flee, attack, etc.
void Robot::usurp(){
	if(this->strategy == strategy_type::ESCORT_STRAT){
		this->strategy = strategy_type::LEADER_STRAT;
	}
}// set AI as group leader -- sets AI internal state to calculate more complex behavior

std::vector<Projectile *> Robot::get_objectives(Environment *environment){
	return this->env->get_neighbors(this->ship);
}

void Robot::act(){
	if(this->strategy == strategy_type::ESCORT_STRAT){
		if(this->action == ARRIVE_AT){
			float scaled;
			float distance = sqrt((pow(this->ship->get_d().at(0)-target.at(0),2)) + (pow(this->ship->get_d().at(1)-target.at(1),2)) + (pow(this->ship->get_d().at(2)-target.at(2),2)));
			if((distance/100)>10){
				scaled = 0.01;
			}
			else if ((distance/100)<1){
				scaled = .1;
			}
			else {
				scaled = 10/distance;
			}
			if(this->ship->get_p_dot()>((asin(target.at(1)/distance))+.15)){
				this->prev_p_dot = prev_p_dot-scaled;
				this->ship->set_p_dot(this->prev_p_dot);
			}
			else if(this->ship->get_p_dot()<((asin(target.at(1)/distance))-.15)){
				this->prev_p_dot = prev_p_dot+scaled;
				this->ship->set_p_dot(this->prev_p_dot);
			}
			if(this->ship->get_r_dot()>((asin(target.at(0)/distance))+.15)){
				this->prev_r_dot = prev_r_dot-scaled;
				this->ship->set_r_dot(this->prev_r_dot);
			}
			else if(this->ship->get_r_dot()<((asin(target.at(0)/distance))-.15)){
				this->prev_r_dot = prev_r_dot+scaled;
				this->ship->set_r_dot(this->prev_r_dot);
			} else {
				this->ship->set_p_dot(0.0);
				this->ship->set_r_dot(0.0);
				this->ship_l.unlock();
			}
			std::cout << "NEW ROBOT P DOT IS " << this->ship->get_p_dot() << std::endl;
			std::cout << "NEW ROBOT R DOT IS " << this->ship->get_r_dot() << std::endl;
		}
		else if(this->action == action_type::ATTACK){
				//this is same as follow, but involves shooting at as well. Just need to add in ray collision between velocity vector and bounding box of target. And asteroids.
		}
		else if(this->action == action_type::FLEE){
			/*
					this->ship_l.lock();
					float scaled;
					float distance = sqrt(((this->ship->get_d.at(0)-target_ship->get_d.at(0))^2) + ((this->ship->get_d.at(1)-target_ship->get_d.at(1))^2) + ((this->ship->get_d.at(2)-target_ship->get_d.at(2))^2));
					if((distance/100)>10){
							scaled = 0.01;
					}
					else if(distance/100)<1){
							scaled = .1;
					}
					else {
							scaled = 10/distance;
					}
					if(this->ship->get_p_dot()>(target_ship->get_p_dot-.15)){
							this->prev_p_dot = prev_p_dot-scaled
							this->ship->set_p_dot(this->prev_p_dot)
					}
					else if(this->ship->get_p_dot()<(target_ship->get_p_dot+.15)){
							this->prev_p_dot = prev_p_dot+scaled
							this->ship->set_p_dot(this->prev_p_dot)
					}
					if(this->ship->get_r_dot()>(target_ship->get_r_dot-.15)){
							this->prev_r_dot = prev_r_dot-scaled
							this->ship->set_r_dot(this->prev_r_dot)
					}
					else if(this->ship->get_p_dot()<(target_ship->get_r_dot+.15)){
							this->prev_r_dot = prev_r_dot+scaled
							this->ship->set_r_dot(this->prev_r_dot)
					}
					this->ship_l.unlock();
			}
			else if(this->strategy == FOLLOW){
					this->ship_l.lock();
					float scaled;
					float distance = sqrt(((this->ship->get_d.at(0)-target_ship->get_d.at(0))^2) + ((this->ship->get_d.at(1)-target_ship->get_d.at(1))^2) + ((this->ship->get_d.at(2)-target_ship->get_d.at(2))^2));
					if((distance/100)>10){
							scaled = 0.01;
					}
					else if(distance/100)<1){
							scaled = .1;
					}
					else {
							scaled = 10/distance;
					}
					if(this->ship->get_p_dot()>((asin(target_ship->get_d.at(1)/distance))+.15)){
							this->prev_p_dot = prev_p_dot-scaled
							this->ship->set_p_dot(this->prev_p_dot)
					}
					else if(this->ship->get_p_dot()<((asin(target_ship->get_d.at(0)/distance))-.15)){
							this->prev_p_dot = prev_p_dot+scaled
							this->ship->set_p_dot(this->prev_p_dot)
					}
					if(this->ship->get_r_dot()>((asin(target_ship->get_d.at(1)/distance))+.15)){
							this->prev_r_dot = prev_r_dot-scaled
							this->ship->set_r_dot(this->prev_r_dot)
					}
					else if(this->ship->get_p_dot()<((asin(target_ship->get_d.at(0)/distance))-.15)){
							this->prev_r_dot = prev_r_dot+scaled
							this->ship->set_r_dot(this->prev_r_dot)
					}
					this->ship_l.unlock();
			}
			else if(this->strategy == ESCORT){
					this->ship_l.lock();
					if(this->ship->get_p_dot()>(this->ship->get_group()->get_leader()->get_p_dot() + .05){
							this->prev_p_dot = prev_p_dot-.01
							this->ship->set_p_dot(this->prev_p_dot)
					}
					else if(this->ship->get_p_dot()<(this->ship->get_group()->get_leader()->get_p_dot() - .05){
							this->prev_p_dot = prev_p_dot+.01
							this->ship->set_p_dot(this->prev_p_dot)
					}
					if(this->ship->get_r_dot()<(this->ship->get_group()->get_leader()->get_r_dot() - .05){
							this->prev_r_dot = prev_r_dot+.01
							this->ship->set_r_dot(this->prev_r_dot)
					}
					else if(this->ship->get_p_dot()>(this->ship->get_group()->get_leader()->get_p_dot() + .05){
							this->prev_r_dot = prev_r_dot-.01
							this->ship->set_r_dot(this->prev_r_dot)
					}
					this->ship_l.unlock();
			}
			*/
	}
	else if(this->strategy == strategy_type::LEADER_STRAT){
			//Do some other stuff based on game state. I'd rather escort AI be solved first.
	}
}
// call the PhysicsEngine for the Environment to determine nearby objectives

		/* simple actions -- if delay_time == 0, carry out action immediately, else finish action before delay_time is exceeded */
/*Robot::seek(std::vector<float> target, float delay){
		this->ship->toggle_a(this->ship->get_id, 1);
		while(this->ship->get_d()!=target){
				this->ship->toggle_r_dot(this->ship->get_id, -0.1);
				this->ship->toggle_p_dot(this->ship->get_id, -0.1);
		}//What exactly is d? Is it an angle? a direction vector?
}
Robot::attack(std::vector<float> target, float delay);
Robot::flee(std::vector<float> target, float delay);
Robot::pursue(std::vector<float> target, float delay);
*/
/* complex behaviors */
//Robot::escort();				// flock with the current ship's group -- need to calculate the group velocity (perhaps cache it in the Group object)
}
