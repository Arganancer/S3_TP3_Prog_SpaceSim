#ifndef MINE_H
#define MINE_H

#include "aoe_projectile.h"
#include "explosion.h"


class mine : public aoe_projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	mine(const Vector2f& position, Vector2f direction, float angle);
	~mine();

	// MUTATORS
	void update(float delta_t);
	void explode(Vector2f explosion_position);

private:
	Color proj_color_;
	explosion* this_proj_explosion_;
	bool hasExploded = false;
};

#endif