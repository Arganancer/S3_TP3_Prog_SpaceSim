#ifndef LASER_WEAPON_H
#define LASER_WEAPON_H
#include "weapon.h"

class laser_weapon : public weapon
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	explicit laser_weapon(Vector2f position, float weapon_size);
	~laser_weapon();

	// MUTATORS
	projectile* shoot_projectile(Vector2f direction, float angle, float delta_t) override;
	void update(float delta_t, Vector2f target) override;
	static bool init();

	// ACCESSORS
};
#endif
