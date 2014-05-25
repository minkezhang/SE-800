#include "weapon_instance.h"

WeaponStandardGun::WeaponStandardGun() : Weapon("Standard Gun", -1, { 1, 0, 0 }, 0, m_type::MUNITION_BULLET) {}
WeaponStandardCannon::WeaponStandardCannon() : Weapon("Standard Cannon", -1, { 1, 0, 0 }, 0, m_type::MUNITION_BOMB) {}
