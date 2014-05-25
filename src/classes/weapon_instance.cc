#include "weapon_instance.h"
#include "../engines/physics/projectile.h"

WeaponStandardGun::WeaponStandardGun() : Weapon("Standard Gun", -1, { 1, 0, 0 }, 0, ObjType::BULLET) { }
WeaponStandardCannon::WeaponStandardCannon() : Weapon("Standard Cannon", -1, { 1, 0, 0 }, 0, ObjType::BOMB) { }
