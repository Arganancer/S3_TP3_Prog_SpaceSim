#include "particle.h"

particle::particle(const Vector2f& position, float mass): movable(position, mass)
{
	size_;

	time_since_created_ = 0;
	max_time_ = rand() % 5 + 1; // To be set in subclasses.

	percentage_modifier_;
	percentage_time_elapsed_;
}

particle::~particle()
{
}

void particle::update(float delta_t)
{

}
