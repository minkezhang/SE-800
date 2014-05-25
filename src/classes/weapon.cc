#include "weapon.h"

Weapon::Weapon(std::string name, int max_ammo, std::vector<float> offset, float rate, int munition_type) : name(name), max_ammo(max_ammo), cur_ammo(max_ammo), offset(offset), rate(rate), last(0), munition_type(munition_type) {}
std::string Weapon::get_name() { return(this->name); }
int Weapon::get_max_ammo() { return(this->max_ammo); }
int Weapon::get_cur_ammo() { return(this->cur_ammo); }
float Weapon::get_rate() { return(this->rate); }
// Munition *Weapon::get_munition();
void Weapon::fire(std::vector<float> d, std::vector<float> r, std::vector<float> v) {
}
