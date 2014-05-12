#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "world.h"
#include "../../classes/ship.h"

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

WorldEngine::WorldEngine(SchedulingEngine *scheduler) : scheduler(scheduler) {
	status = UNINITIALIZED;
}
WorldEngine::~WorldEngine() {}

std::vector<Team *> WorldEngine::get_teams() { return(this->teams); }

void WorldEngine::add_team(Team *team) { this->teams.push_back(team); }
void WorldEngine::del_team(Team *team) {}

void WorldEngine::win() {
	// do something for teams
	this->shutdown();
}

void WorldEngine::ignite() {
	this->status = INITIALIZED;
}

void WorldEngine::cycle() {
	std::cout << "calling world cycle" << std::endl;
	this->status = RUNNING;
	this->scheduler->ignite();
	while(this->scheduler->get_signal()) {
		sleep(1);
	}
}

void WorldEngine::shutdown() {
	this->status = STOPPED;
	this->scheduler->shutdown();
}

Ship *WorldEngine::join(Pilot *p) {
	Ship *s = new Ship(1, 10, 10, {1, 1, 1});
	return(s);
}

PhysicsEngine *WorldEngine::physics_engine() {
	return NULL;
}
