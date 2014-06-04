#include "weapon.h"
#include "munition_instance.h"

#include <osg/Vec3>
#include <osg/Quat>
#include <osg/Matrixd>
#include <iostream>

Weapon::Weapon(std::string name, int max_ammo, std::vector<float> d_offset, std::vector<float> v_offset, float rate, int munition_type) : name(name), max_ammo(max_ammo), cur_ammo(max_ammo), d_offset(d_offset), v_offset(v_offset), rate(rate), last(0), munition_type(munition_type) {}
std::string Weapon::get_name() { return(this->name); }
int Weapon::get_max_ammo() { return(this->max_ammo); }
int Weapon::get_cur_ammo() { return(this->cur_ammo); }
float Weapon::get_rate() { return(this->rate); }

Munition *Weapon::get_munition(std::vector<float> pos, std::vector<float> p, std::vector<float> r, std::vector<float> y, std::vector<float> v) {
	if(this->munition_type == ObjType::BULLET) {
		return(new MunitionBullet((int) (1001 + pos.at(0) + v.at(1) + r.at(2)), pos, v, p, r, y));
	} else if (this->munition_type == ObjType::BOMB) {
		return(new MunitionBomb((int) (1001 + pos.at(0) + v.at(1) + r.at(2)), pos, v, p, r, y));
	}
	return NULL;
}

void Weapon::fire(std::vector<float> d, float p, float r, std::vector<float> y, std::vector<float> v, float size, Environment *e) {
	if((this->max_ammo > 0) && (this->cur_ammo == 0)) {
		return;
	}
	// Calculate normalized roll vector from r dot.
	osg::Quat r_quat = osg::Quat(osg::DegreesToRadians((r * 180 / M_PI)), osg::Vec3(0, 1, 0));
	osg::Matrixd r_mat = osg::Matrixd(r_quat);
	osg::Vec3 old_r_vec = osg::Vec3(0, 1, 0);
	osg::Vec3 new_r_vec = r_mat * old_r_vec;
	std::vector<float> r_vec = {new_r_vec.x(), new_r_vec.y(), new_r_vec.z()};

	// Calculate normalized pitch vector from p dot.
	osg::Quat p_quat = osg::Quat(osg::DegreesToRadians((-p * 180 / M_PI)), osg::Vec3(1, 0, 0));
	osg::Matrixd p_mat = osg::Matrixd(p_quat);
	osg::Vec3 old_p_vec = osg::Vec3(0, 1, 0);
	osg::Vec3 new_p_vec = p_mat * old_p_vec;
	std::vector<float> p_vec = {new_p_vec.x(), new_p_vec.y(), new_p_vec.z()};

	std::vector<float> pos = { 0, 0, 0 };
	std::vector<float> vel = { 0, 0, 0 };
	for(int i = 0; i < 3; i++) {
		pos.at(i) = d.at(i) + (MUNITION_SIZE + size) * r_vec.at(i);
		vel.at(i) = v.at(i) + MUNITION_VEL * r_vec.at(i);
	}

	e->add_projectile(this->get_munition(pos, p_vec, r_vec, y, vel));
	this->cur_ammo--;
}
