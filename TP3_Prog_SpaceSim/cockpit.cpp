#include "cockpit.h"

Texture cockpit::cockpit_texture_;

cockpit::cockpit(
	Vector2f default_position,
	float default_angle,
	float component_size) :
	component(
		default_position,
		default_angle,
		component_size)
{
	layer_ = four;
	component_shape_.setTexture(&cockpit_texture_);
}

cockpit::~cockpit()
{
}

void cockpit::update(float rotation_angle, Transform transform)
{
	component::update(rotation_angle, transform);
}

bool cockpit::init()
{
	if (!cockpit_texture_.loadFromFile("Sprites\\cockpit_texture_25x25.png"))
		return false;
	return true;
}
