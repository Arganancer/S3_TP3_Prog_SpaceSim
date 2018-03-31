#include "gatling_gun.h"
#include "gatling_bullet.h"


gatling_gun::gatling_gun(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 0.01f;
	modified_rof_ = default_rof_;
	last_shot_ = 0.0f;
	ammo = 300;
}

gatling_gun::~gatling_gun()
{
	
}


void gatling_gun::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}

projectile* gatling_gun::shoot_projectile(Vector2f direction, float angle, float delta_t)
{
	if (shot_available_ && ammo != 0)
	{
		ammo--;
		last_shot_ = 0;
		shot_available_ = false;
		return new gatling_bullet(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}

bool gatling_gun::init()
{
	if (!weapon_texture_.loadFromFile("Sprites\\laser_weapon_texture_16x16.png")) //Change to gatling sprite when ready
		return false;
	return true;
}
