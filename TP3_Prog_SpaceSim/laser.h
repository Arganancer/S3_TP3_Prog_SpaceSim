#ifndef LASER_H
#define LASER_H
#include "projectile.h"

class laser : public projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	laser(const Vector2f& position, Vector2f direction, float angle);
	~laser();

	void update(float delta_t) override;
private:
	Color laser_color_;
};

#endif