
#ifndef PLASMA_WEAPON_H
#define PLASMA_WEAPON_H
#include "weapon.h"

class plasma_weapon : public weapon
{
public:
	explicit plasma_weapon(Vector2f position, float weapon_size);
	~plasma_weapon();
	projectile* shoot_projectile(Vector2f direction, float angle, float rate_of_fire) override;
	void update(float delta_t, Vector2f target) override;
};
#endif
