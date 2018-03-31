#ifndef GATLING_BULLET_H
#define GATLING_BULLET_H
#include "projectile.h"

class gatling_bullet : public projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	gatling_bullet(const Vector2f& position, Vector2f direction, float angle);
	~gatling_bullet();

	void update(float delta_t);
private:
	Color bullet_color_;		
};

#endif