#include "pilot.h"
#include "../classes/ship.h"

int PILOT_COUNT = 1;

Pilot::Pilot(std::string name) {
	this->name = name;
	this->id = PILOT_COUNT;
	PILOT_COUNT++;
}

Pilot::~Pilot() {
}

int Pilot::get_id() {
	return this->id;
}

std::string Pilot::get_name() {
	return name;
}

Ship * Pilot::get_ship() {
	return this->ship;
}

void Pilot::set_ship(Ship *ship) {
	this->ship = ship;
}

int Pilot::is_leader() {
	return 1;
}

void Pilot::control() {
}

