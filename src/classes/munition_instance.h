#ifndef _MUNITION_INSTANCE_H
#define _MUNITION_INSTANCE_H

#include <vector>

#include "munition.h"

class MunitionBullet : public Munition {
	public:
		MunitionBullet(int id, std::vector<float> d, std::vector<float> v);
};

class MunitionBomb : public Munition {
	public:
		MunitionBomb(int id, std::vector<float> d, std::vector<float> v, float aoe);
};

#endif
