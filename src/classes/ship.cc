#include "ship.h"
#include "../classes/weapon.h"
#include "../engines/physics/projectile.h"

Ship::Ship(int id, float mass, float max_tolerance, std::vector<float> d, float size, float preset_a, float preset_p_dot, float preset_r_dot) : Projectile(id, 1, mass, max_tolerance, d, { 0, 0, 0 }, size, { 0, 0, 0 }, { 0, 0, 0 }, 0, 0, preset_a, preset_p_dot, preset_r_dot) {
	this->type = ObjType::SHIP;
}

int Ship::get_weapon_index() {
	return this->weapon_index;
}

void Ship::del_weapon(Weapon *weapon) {
}

void Ship::add_weapon(Weapon *weapon) {
}

void Ship::sel_weapon(int index) {
}
