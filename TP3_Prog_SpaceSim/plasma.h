
#ifndef PLASMA_H
#define PLASMA_H

#include "aoe_projectile.h"



class plasma : public aoe_projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	plasma(const Vector2f& position, Vector2f direction, float angle);
	~plasma();

	// MUTATORS
	void update(float delta_t);
	void explode(Vector2f explosion_position);

private:
	Color proj_color_;
	bool hasExploded = false;
};

#endif