#ifndef MISSILE_H
#define MISSILE_H
#include "aoe_projectile.h"

class missile : public aoe_projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	missile(const Vector2f& position, Vector2f direction, float angle);
	~missile();

	// MUTATORS
	void update(float delta_t);
	void explode(Vector2f explosion_position);

private:
	Color proj_color_;
	bool hasExploded = false;
};




#endif
