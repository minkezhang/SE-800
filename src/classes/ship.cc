#include "ship.h"
#include "../classes/weapon.h"
#include "../engines/physics/projectile.h"

Ship::Ship(int id, int clippable, float mass, float max_tolerance) :
		Projectile(id, clippable, mass, max_tolerance) {}

int Ship::get_weapon_index() {
	return this->weapon_index;
}

void Ship::del_weapon(Weapon *weapon) {
}

void Ship::add_weapon(Weapon *weapon) {
}

void Ship::sel_weapon(int index) {
}
