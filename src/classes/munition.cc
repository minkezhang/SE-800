#include "../../lib/exception.h"
#include "munition.h"

Munition::Munition(int id, float max_tolerance, std::vector<float> origin, std::vector<float> v, float aoe, int lifetime) : Projectile(id, 0, 10, max_tolerance, origin, v, .01, { 1, 0, 0 }, { 0, 1, 0 }, 0, 0, 0, 0, 0, lifetime), aoe(aoe) {}

// TODO : put into projectile.h
void explode() {
	throw BaseClassUnimplementedError();
}

float get_damage(float distance) {
	throw BaseClassUnimplementedError();
}
