#include "thruster.h"

Texture thruster::engine_texture_;

thruster::thruster(
	Vector2f default_position, 
	float default_angle, 
	float component_size): 
	component(
		default_position,
		default_angle,
		component_size)
{
	layer_ = four;
	component_shape_.setTexture(&engine_texture_);
}

thruster::~thruster()
{
}

void thruster::update(float rotation_angle, Transform transform)
{
	component::update(rotation_angle, transform);
}

bool thruster::init()
{
	if (!engine_texture_.loadFromFile("Sprites\\thruster_texture_32x32.png"))
		return false;
	return true;
}