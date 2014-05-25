#include "weapon.h"
#include "munition_instance.h"

Weapon::Weapon(std::string name, int max_ammo, std::vector<float> offset, float rate, int munition_type) : name(name), max_ammo(max_ammo), cur_ammo(max_ammo), offset(offset), rate(rate), last(0), munition_type(munition_type) {}
std::string Weapon::get_name() { return(this->name); }
int Weapon::get_max_ammo() { return(this->max_ammo); }
int Weapon::get_cur_ammo() { return(this->cur_ammo); }
float Weapon::get_rate() { return(this->rate); }
Munition *Weapon::get_munition(std::vector<float> pos, std::vector<float> r, std::vector<float> v) {
	if(this->munition_type == ObjType::BULLET) {
		return(new MunitionBullet((int) (1001 + pos.at(0) + v.at(1) + r.at(2)), pos, v, r));
	} else if (this->munition_type == ObjType::BOMB) {
		return(new MunitionBomb((int) (1001 + pos.at(0) + v.at(1) + r.at(2)), pos, v, r));
	}
	return NULL;
}
void Weapon::fire(std::vector<float> d, std::vector<float> r, std::vector<float> v, float size, Environment *e) {
	if((this->max_ammo > 0) && (this->cur_ammo == 0)) {
		return;
	}
	std::vector<float> pos = { 0, 0, 0 };
	for(int i = 0; i < 2; i++) {
		pos.at(i) = size * this->offset.at(i) + d.at(i);
	}
	e->add_projectile(this->get_munition(pos, r, v));
	this->cur_ammo--;
}
