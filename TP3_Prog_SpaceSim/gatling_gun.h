#ifndef GATLING_GUN_H
#define GATLING_GUN_H
#include "weapon.h"

class gatling_gun : public weapon
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	explicit gatling_gun(Vector2f position, float weapon_size);
	~gatling_gun();

	// MUTATORS
	projectile* shoot_projectile(Vector2f direction, float angle, float delta_t) override;
	void update(float delta_t, Vector2f target) override;
	static bool init();


};
#endif
