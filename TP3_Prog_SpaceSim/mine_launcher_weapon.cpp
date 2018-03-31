#include "mine_launcher_weapon.h"
#include "mine.h"
mine_launcher_weapon::mine_launcher_weapon(Vector2f position, float weapon_size) : weapon(position, 0, weapon_size)
{
	default_rof_ = 1.0f;
	modified_rof_ = default_rof_;
	last_shot_ = 0.0f;
	ammo = 5;
}

mine_launcher_weapon::~mine_launcher_weapon()
{
}

projectile* mine_launcher_weapon::shoot_projectile(Vector2f direction, float angle, float rate_of_fire)
{
	if (shot_available_ && ammo != 0)
	{
		ammo--;
		last_shot_ = 0;
		shot_available_ = false;
		return new mine(component_shape_.getPosition(), direction, angle);
	}
	return nullptr;
}

void mine_launcher_weapon::update(float delta_t, Vector2f target)
{
	weapon::update(delta_t, target);
}
