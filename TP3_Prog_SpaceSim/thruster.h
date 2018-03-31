#ifndef THRUSTER_H
#define THRUSTER_H
#include "component.h"

class thruster : public component
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	thruster(Vector2f default_position, float default_angle, float component_size);
	~thruster();

	// MUTATORS
	void update(float rotation_angle, Transform transform) override;
	static bool init();

protected:
	static Texture engine_texture_;
};

#endif