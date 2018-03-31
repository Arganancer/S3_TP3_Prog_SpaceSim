#include "missile_launcher.h"
#include "missile.h"


missile_launcher::missile_launcher(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 3.00f;
	modified_rof_ = default_rof_;
	last_shot_ = 0.0f;
	ammo = 10;
}

missile_launcher::~missile_launcher()
{

}


void missile_launcher::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}

projectile* missile_launcher::shoot_projectile(Vector2f direction, float angle, float delta_t)
{
	if (shot_available_ && ammo != 0)
	{
		ammo--;
		last_shot_ = 0;
		shot_available_ = false;
		return new missile(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}
