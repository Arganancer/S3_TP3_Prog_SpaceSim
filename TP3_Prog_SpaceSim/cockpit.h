#ifndef COCKPIT_H
#define COCKPIT_H
#include "component.h"

class cockpit : public component
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	cockpit(Vector2f default_position, float default_angle, float component_size);
	~cockpit();

	// MUTATORS
	void update(float rotation_angle, Transform transform) override;
	static bool init();

protected:
	static Texture cockpit_texture_;
};

#endif