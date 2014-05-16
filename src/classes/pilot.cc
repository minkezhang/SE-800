#include "pilot.h"
#include "../classes/ship.h"

int PILOT_COUNT = 1;

Pilot::Pilot(std::string name) {
	this->id = PILOT_COUNT;
	PILOT_COUNT++;
}

Pilot::~Pilot() {
}

int Pilot::get_id() {
	return 1;
}

std::string Pilot::get_name() {
	return "";
}

Ship * Pilot::get_ship() {
	return NULL;
}

void Pilot::set_ship(Ship *ship) {
}

int Pilot::is_leader() {
	return 1;
}

void Pilot::control() {
}

