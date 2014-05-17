#include "asteroid.h"

Asteroid::Asteroid(int id, float mass, float max_tolerance, float size, float preset_p_dot, float preset_r_dot) : Projectile(id, 1, mass, max_tolerance, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0, 0 }, 0, 0, 0, preset_p_dot, preset_r_dot) {
        this->type = ObjType::ASTEROID;
}



