#include "ship.h"
#include "../classes/weapon.h"
#include "../engines/physics/projectile.h"

Ship::Ship(int id, float mass, float max_tolerance, std::vector<float> d, float size, float preset_a, float preset_p_dot, float preset_r_dot) : Projectile(id, 1, mass, max_tolerance, d, { 0, 0, 0 }, size, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, 0, 0, preset_a, preset_p_dot, preset_r_dot, -1) {
	this->type = ObjType::SHIP;
	this->weapon_index = 0;
}

int Ship::get_weapon_index() {
	return this->weapon_index;
}

void Ship::fire(Environment *e) {
	this->weapons.at(this->weapon_index)->fire(this->get_d(), this->get_p_dot(), this->get_r_dot(), this->get_y(), this->get_v(), this->get_size(), e);
}

void Ship::add_weapon(Weapon *weapon) { this->weapons.push_back(weapon); }
void Ship::sel_weapon(int index) {}
