#include "plasma_weapon.h"
#include "plasma.h"

plasma_weapon::plasma_weapon(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 1.0f;
	modified_rof_ = default_rof_;
	last_shot_ = 0;
	ammo = 10;
}

plasma_weapon::~plasma_weapon()
{
}

projectile* plasma_weapon::shoot_projectile(Vector2f direction, float angle, float delta_t)
{
	if (shot_available_ && ammo != 0)
	{
		ammo--;
		last_shot_ = 0;
		shot_available_ = false;
		return new plasma(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}

void plasma_weapon::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}
