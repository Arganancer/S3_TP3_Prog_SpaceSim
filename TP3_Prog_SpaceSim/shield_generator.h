#ifndef SHIELD_GENERATOR_H
#define SHIELD_GENERATOR_H
#include "component.h"

class shield_generator : public component
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	shield_generator(Vector2f default_position, float default_angle, float component_size);
	~shield_generator();

	// MUTATORS
	void update(float rotation_angle, Transform transform) override;
	static bool init();

protected:
	static Texture texture_shield_generator_;
};

#endif