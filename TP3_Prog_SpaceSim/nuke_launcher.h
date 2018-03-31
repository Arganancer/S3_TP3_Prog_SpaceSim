#ifndef NUKE_LAUNCHER_H
#define NUKE_LAUNCHER_H
#include "weapon.h"

class nuke_launcher : public weapon
{
public:
	explicit nuke_launcher(Vector2f position, float weapon_size);
	~nuke_launcher();
	projectile* shoot_projectile(Vector2f direction, float angle, float rate_of_fire) override;
	void update(float delta_t, Vector2f target) override;
};

#endif