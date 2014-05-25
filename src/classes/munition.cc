#include "munition.h"

Munition::Munition(int id, float max_tolerance, std::vector<float> d, std::vector<float> v, std::vector<float> p, std::vector<float> r, std::vector<float> y, float aoe, int lifetime) : Projectile(id, 0, 10, max_tolerance, d, v, 1, p, r, y, 0, 0, 0, 0, 0, lifetime), aoe(aoe) {}

// TODO : put into projectile.h
void explode() {}

float get_damage(float distance) {}
