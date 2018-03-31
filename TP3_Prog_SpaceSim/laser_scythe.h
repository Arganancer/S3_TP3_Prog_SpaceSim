#ifndef LASER_SCYTHE_H
#define LASER_SCYTHE_H
#include "projectile.h"


class laser_scythe : public projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	laser_scythe(const Vector2f& position, Vector2f direction, float angle);
	~laser_scythe();

	void update(float delta_t);
private:
	sf::Color scythe_color_;
};

#endif