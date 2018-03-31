#ifndef MISSILE_LAUNCHER_H
#define MISSILE_LAUNCHER_H
#include "weapon.h"

class missile_launcher : public weapon
{
public:
	explicit missile_launcher(Vector2f position, float weapon_size);
	~missile_launcher();
	projectile* shoot_projectile(Vector2f direction, float angle, float rate_of_fire) override;
	void update(float delta_t, Vector2f target) override;
};

#endif