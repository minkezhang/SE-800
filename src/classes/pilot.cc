#include "pilot.h"
#include "../classes/ship.h"

int PILOT_COUNT = 1;

Pilot::Pilot(std::string name, int is_player) : name(name), is_player(is_player) {
	this->id = PILOT_COUNT;
	PILOT_COUNT++;
}

int Pilot::get_id() { return this->id; }

std::string Pilot::get_name() {	return this->name; }
int Pilot::get_is_player() { return(this->is_player); }

Ship * Pilot::get_ship() { return this->ship; }

void Pilot::set_ship(Ship *ship) {
	this->ship_l.lock();
	this->ship = ship;
	this->ship_l.unlock();
}

int Pilot::is_leader() { return 1; }

void Pilot::control() {}

