#include "ship_instance.h"
#include "weapon_instance.h"

ShipCarrier::ShipCarrier(int id, std::vector<float> d) : Ship(id, 1000, 400, d, 9.5, 1000, 0.9, 0.75) {
	this->add_weapon(new WeaponStandardGun());
	this->add_weapon(new WeaponStandardCannon());
}
ShipScout::ShipScout(int id, std::vector<float> d) : Ship(id, 200, 100, d, .2, 500, .5, .5) {
	this->add_weapon(new WeaponStandardGun());
}
ShipFighter::ShipFighter(int id, std::vector<float> d) : Ship(id, 400, 200, d, .4, 200, .5, .5) {
	this->add_weapon(new WeaponStandardGun());
	this->add_weapon(new WeaponStandardCannon());
}
