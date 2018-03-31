#ifndef PARTICLE_H
#define PARTICLE_H
#include "movable.h"

/*
 * TYPES OF PARTICLES:
 *	- Fire (Diminishing flame effect).
 *	- Smoke  (Expanding/Random Direction).
 *	- Engine Flame (Expanding/Contracting directed flame).
 *	- Spark (Like in geometry wars).
 *	- Explosion (Expanding Circle).
 *	- Shockwave (Expanding Circle).
 *	- Electrical discharge (Random electrical effects/brief duration).
 *		
 * EVENTS THAT TRIGGER PARTICLE GENERATION:
 *	- Ship Hull Damaged:
 *		- Fire (Diminishing flame effect).
 *		- Smoke  (Expanding/Random Direction).
 *	- Movement:
 *		- Engine Flame (Expanding/Contracting directed flame).
 *		- Smoke  (Expanding/Random Direction).
 *	- Explosion:
 *		- Spark (Like in geometry wars).
 *		- Smoke (Expanding/Random direction).
 *		- Explosion (Expanding Circle).
 *		- Shockwave (Expanding circle).
 *	- Shield hit:
 *		- Electrical discharge (Random electrical effects/brief duration).
 *	- Regular projectile collides:
 *		- Spark (Like in geometry wars).
 *	- Exploding projectile collides:
 *		- Spark (Like in geometry wars).
 *		- Explosion (Expanding Circle).
 */

class particle : public movable
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	particle(const Vector2f& position, float mass);
	virtual ~particle();

	// ACCESSORS

	// MUTATORS
	void update(float delta_t);

protected:
	float percentage_time_elapsed_;
	float percentage_modifier_;
	float size_;
	float time_since_created_;
	float max_time_;
};

#endif