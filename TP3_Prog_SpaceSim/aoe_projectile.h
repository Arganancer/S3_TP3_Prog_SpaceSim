#ifndef AOE_PROJECTILE_H
#define AOE_PROJECTILE_H

#include "projectile.h"

class aoe_projectile : public projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	aoe_projectile(const Vector2f& position, float mass, Vector2f direction, float angle);
	~aoe_projectile();

	void update(float delta_t);
	void explode(Vector2f explosion_position);
};

#endif