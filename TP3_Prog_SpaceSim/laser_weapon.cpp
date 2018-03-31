#include "laser_weapon.h"
#include "laser.h"

laser_weapon::laser_weapon(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 0.2f;
	modified_rof_ = default_rof_;
	last_shot_ = 0.0f;
	ammo = 500;
}

laser_weapon::~laser_weapon()
{
}

void laser_weapon::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}

projectile* laser_weapon::shoot_projectile(Vector2f direction, float angle, float delta_t)
{
	if (shot_available_ && ammo != 0)
	{
		last_shot_ = 0;
		shot_available_ = false;
		return new laser(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}

bool laser_weapon::init()
{
	if (!weapon_texture_.loadFromFile("Sprites\\laser_weapon_texture_16x16.png"))
		return false;
	return true;
}
