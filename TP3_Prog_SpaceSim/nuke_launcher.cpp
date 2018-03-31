#include "nuke_launcher.h"
#include "nuke.h"

nuke_launcher::nuke_launcher(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 10.0f;
	modified_rof_ = default_rof_;
	last_shot_ = 0.0f;
	ammo = 2;
}

nuke_launcher::~nuke_launcher()
{
}

projectile* nuke_launcher::shoot_projectile(Vector2f direction, float angle, float rate_of_fire)
{
	if (shot_available_ && ammo != 0)
	{
		ammo--;
		last_shot_ = 0;
		shot_available_ = false;
		return new nuke(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}

void nuke_launcher::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}
