#include "weapon.h"
#include "tools.hpp"

Texture weapon::weapon_texture_;

weapon::weapon(Vector2f default_position, float default_angle, float weapon_size) :
	component(default_position, default_angle, weapon_size),
	current_angle_(0),
	desired_angle_(0), 
	shot_available_(true),
	last_shot_(0),
	default_rof_(0),
	modified_rof_(0)
{
	layer_ = one;
	set_shape_points(component_shape_, weapon_size);
	component_shape_.setTexture(&weapon_texture_);
}

void weapon::update(float delta_t, Vector2f target)
{
	shoot_delay(delta_t);
	desired_direction_ = tools::vec_util::direction(get_position(), target);
	desired_angle_ = tools::vec_util::angle_d(desired_direction_);
	component_shape_.setRotation(desired_angle_);
}

weapon::~weapon()
{
}

void weapon::set_modified_rof(float modifier)
{
	modified_rof_ = default_rof_ * modifier;
}

void weapon::shoot_delay(float delta_t)
{	
	if(last_shot_ < modified_rof_)
	{
		last_shot_ += delta_t;
	}
	else if (!shot_available_)
	{
		shot_available_ = true;
	}
}

int weapon::get_ammo() const
{
	return ammo;
}
