#include "shield_generator.h"

Texture shield_generator::texture_shield_generator_;

shield_generator::shield_generator(
	Vector2f default_position, 
	float default_angle, 
	float component_size): 
	component(
		default_position,
		default_angle,
		component_size)
{
	layer_ = two;
	component_shape_.setTexture(&texture_shield_generator_);
}

shield_generator::~shield_generator()
{
}

void shield_generator::update(float rotation_angle, Transform transform)
{
	component::update(rotation_angle, transform);
}

bool shield_generator::init()
{
	if (!texture_shield_generator_.loadFromFile("Sprites\\battery_texture_16x16.png"))
		return false;
	return true;
}
