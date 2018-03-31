#ifndef NUKE_H
#define NUKE_H
#include "aoe_projectile.h"

class nuke : public aoe_projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	nuke(const Vector2f& position, Vector2f direction, float angle);
	~nuke();

	// MUTATORS
	void update(float delta_t);
	void explode(Vector2f explosion_position);

private:
	Color proj_color_;
	bool hasExploded = false;
};




#endif
