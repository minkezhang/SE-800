#include "ship.h"
#include "../classes/weapon.h"
#include "../engines/physics/projectile.h"

Ship::Ship(int id, float mass, float max_tolerance, std::vector<float> d) : Projectile(id, 1, mass, max_tolerance, d, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0) {}

int Ship::get_weapon_index() {
	return this->weapon_index;
}

void Ship::del_weapon(Weapon *weapon) {
}

void Ship::add_weapon(Weapon *weapon) {
}

void Ship::sel_weapon(int index) {
}
