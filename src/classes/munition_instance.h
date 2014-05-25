#ifndef _MUNITION_INSTANCE_H
#define _MUNITION_INSTANCE_H

#include "munition.h"

class MunitionBullet : public Munition {
	public:
		MunitionBullet(int id, std::vector<float> d, std::vector<float> v, std::vector<float> p, std::vector<float> r, std::vector<float> y);
};

class MunitionBomb : public Munition {
	public:
		MunitionBomb(int id, std::vector<float> d, std::vector<float> v, std::vector<float> p, std::vector<float> r, std::vector<float> y);
};

#endif
