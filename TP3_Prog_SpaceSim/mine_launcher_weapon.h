#ifndef MINE_LAUNCHER_WEAPON_H
#define MINE_LAUNCHER_WEAPON_H
#include "weapon.h"

class mine_launcher_weapon : public weapon
{
public:
	explicit mine_launcher_weapon(Vector2f position, float weapon_size);
	~mine_launcher_weapon();
	projectile* shoot_projectile(Vector2f direction, float angle, float rate_of_fire) override;
	void update(float delta_t, Vector2f target) override;
};

#endif;