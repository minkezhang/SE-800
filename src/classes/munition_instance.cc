#include "munition_instance.h"
#include "../engines/physics/projectile.h"

MunitionBullet::MunitionBullet(int id, std::vector<float> d, std::vector<float> v, std::vector<float> r) : Munition(id, 25, d, v, r, 0, 600) {
	this->type = ObjType::BULLET;
}
MunitionBomb::MunitionBomb(int id, std::vector<float> d, std::vector<float> v, std::vector<float> r) : Munition(id, 100, d, v, r, 50, 300) {
	this->type = ObjType::BOMB;
}
