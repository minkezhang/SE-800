#include "world.h"

/**
 * consider implementing an Game interface to handle network events and building and destroying the world
 */

WorldEngine::WorldEngine() {
	status = UNINITIALIZED;
	scheduler = SchedulingEngine();
}
WorldEngine::~WorldEngine() {}

std::vector<Team *> WorldEngine::get_teams() { return(this->teams); }

void WorldEngine::add_team(Team *team) { this->teams.push_back(team); }
void WorldEngine::del_team(Team *team) {}

void WorldEngine::win() { /* stop engines */ }

void WorldEngine::ignite() {
	this->status = INITIALIZED;
}

void WorldEngine::cycle() {
	this->status = RUNNING;
	this->scheduler.ignite();
}

void WorldEngine::shutdown() {
	this->status = STOPPED;
	this->scheduler.shutdown();
}
