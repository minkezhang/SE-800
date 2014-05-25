#include "munition_instance.h"
#include "../engines/physics/projectile.h"

MunitionBullet::MunitionBullet(int id, std::vector<float> d, std::vector<float> v, std::vector<float> p, std::vector<float> r, std::vector<float> y) : Munition(id, 25, d, v, p, r, y, 0, 600) {
	this->type = ObjType::BULLET;
}
MunitionBomb::MunitionBomb(int id, std::vector<float> d, std::vector<float> v, std::vector<float> p, std::vector<float> r, std::vector<float> y) : Munition(id, 100, d, v, p, r, y, 50, 300) {
	this->type = ObjType::BOMB;
}
