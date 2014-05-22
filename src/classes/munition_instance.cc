#include "munition_instance.h"

MunitionBullet::MunitionBullet(int id, std::vector<float> origin, std::vector<float> v) : Munition(id, 50, origin, v, 0, 300) {}
MunitionBomb::MunitionBomb(int id, std::vector<float> origin, std::vector<float> v, float aoe) : Munition(id, 40, origin, v, aoe, 200) {}
