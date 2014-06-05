#include "ship_instance.h"
#include "weapon_instance.h"

ShipCarrier::ShipCarrier(int id, std::vector<float> d) : Ship(id, 1000, 400, d, 9.5, 1000, 15, 15) {
	this->add_weapon(new WeaponStandardGun());
	this->add_weapon(new WeaponStandardCannon());
}
ShipScout::ShipScout(int id, std::vector<float> d) : Ship(id, 200, 100, d, .2, 500, 1.5,1.5) {
	this->add_weapon(new WeaponStandardGun());
}
ShipFighter::ShipFighter(int id, std::vector<float> d) : Ship(id, 400, 200, d, .4, 200, 1.5, 1.5) {
	this->add_weapon(new WeaponStandardGun());
	this->add_weapon(new WeaponStandardCannon());
}
