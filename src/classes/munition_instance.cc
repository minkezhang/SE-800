#include "munition_instance.h"

MunitionBullet::MunitionBullet(int id, std::vector<float> d, std::vector<float> v, std::vector<float> r) : Munition(id, 25, d, v, r, 0, 300) {}
MunitionBomb::MunitionBomb(int id, std::vector<float> d, std::vector<float> v, std::vector<float> r) : Munition(id, 100, d, v, r, 50, 300) {}
