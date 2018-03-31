#include "movable.h"
#include "tools.hpp"

movable::movable(Vector2f position, float mass) : 
	is_alive_(true),
	position_(position),
	mass_(mass),
	force_(Vector2f(0, 0)),
	max_force_(0),
	last_acceleration_(Vector2f(0, 0)),
	new_acceleration_(Vector2f(0, 0)),
	avg_acceleration_(Vector2f(0, 0)),
	velocity_(Vector2f(0, 0)),
	rotation_angle_(0),
	angular_velocity_(0),
	angular_acceleration_(0),
	torque_(0),
	max_torque_(0)
{
	angular_mass_ = mass_ * 0.5f;
	default_max_velocity_ = 7000 / mass_;
	default_max_angular_velocity_ = 5000 / angular_mass_;
	max_velocity_ = default_max_velocity_;
	max_angular_velocity_ = default_max_angular_velocity_;
}

movable::~movable()
{
}

Vector2f movable::get_velocity() const
{
	return velocity_;
}

void movable::calculate_velocity(float delta_t)
{
	// TRANLATION:
		// Velocity Verlet: https://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
		// 1) last_acceleration = new_acceleration
		// 2) position += velocity * time_step + (0.5 * last_acceleration * time_step ^ 2)
		// 3) new_acceleration = force / mass
		// 4) avg_acceleration = (last_acceleration + new_acceleration) / 2
		// 5) velocity += avg_acceleration * time_step

	// Calculate maximum velocity and perform adjustments if necessary:
	if (tools::vec_util::magnitude(velocity_) > max_velocity_)
	{
		const Vector2f direction = tools::vec_util::direction(velocity_);
		velocity_ = direction * max_velocity_;
	}
	last_acceleration_ = new_acceleration_;	
	position_ += velocity_ * delta_t + 0.5f * last_acceleration_ * delta_t * delta_t; // powf(delta_t, 2)
	if (mass_ != 0)
		new_acceleration_ = force_ / mass_;
	avg_acceleration_ = (last_acceleration_ + new_acceleration_) * 0.5f; // divided by 2.0f
	velocity_ += avg_acceleration_ * delta_t;
}

void movable::set_velocity_and_move(Vector2f velocity, float delta_t)
{
	velocity_ = velocity;
	position_ += velocity_ * delta_t;
}

void movable::set_current_max_velocity(float percentage)
{
	max_velocity_ = default_max_velocity_ * percentage;
}

void movable::set_current_max_angular_velocity(float percentage)
{
	max_angular_velocity_ = default_max_angular_velocity_ * percentage;
}


void movable::kill_angular_velocity()
{
	angular_velocity_ = 0;
}

void movable::rotate(float delta_t)
{
	// ROTATION:
		// Euler's Method: https://en.wikipedia.org/wiki/Euler_method

	if (angular_mass_ != 0)
		angular_acceleration_ = (torque_ / angular_mass_);

	angular_velocity_ += angular_acceleration_;
	if (angular_velocity_ > max_angular_velocity_)
		angular_velocity_ = max_angular_velocity_;
	else if (angular_velocity_ < -max_angular_velocity_)
		angular_velocity_ = -max_angular_velocity_;

	rotation_angle_ += angular_velocity_ * delta_t;
	rotation_angle_ = (int(rotation_angle_ * 10) % 3600) / 10;
}

float movable::get_mass() const
{
	return mass_;
}

void movable::set_velocity(Vector2f velocity)
{
	velocity_ = velocity;
}

Vector2f movable::get_position() const
{
	return position_;
}

bool movable::get_is_alive() const
{
	return is_alive_;
}

void movable::set_position(Vector2f position)
{
	position_ = position;
}

void movable::kill_entity()
{
	is_alive_ = false;
}

void movable::adjust_position(Vector2f position)
{
	position_ += position;
}
