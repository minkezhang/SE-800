#include "asteroid.h"
#include <vector>

Asteroid::Asteroid(int id, float mass, float max_tolerance, std::vector<float> d, float size, float preset_p_dot, float preset_r_dot) : Projectile(id, 1, mass, max_tolerance, d, { 0, 0, 0 }, size, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, 0, 0, 0, preset_p_dot, preset_r_dot, -1) {
        this->type = ObjType::ASTEROID;
}



