#include "laser.h"

laser::laser(const Vector2f& position, Vector2f direction, float angle): 
	projectile(position, 4, direction, angle)
{
	projectile_damage_ = 25;
	max_force_ = 1000;
	velocity_ = direction * max_force_;
	max_time_ = 1.0f;

	set_shape_points(shape_projectile_, 5, 2);
	rotation_angle_ = angle;
	laser_color_ = Color(219, 19, 19, 200);
	shape_projectile_.setFillColor(laser_color_);
}

laser::~laser()
{
}

void laser::update(float delta_t)
{
	static const auto percentage_start_end_sequence = 0.80f;
	if(time_since_created_ >= max_time_)
	{
		kill_entity();
	}
	else if (percentage_time_elapsed_ >= percentage_start_end_sequence)
	{
		float percentage_end_sequence = 0.0f;
		if (percentage_start_end_sequence != 0)
		{
			percentage_end_sequence = (1.0f - percentage_time_elapsed_) / (1.0f - percentage_start_end_sequence);
		}
		velocity_ *= 0.99f;
		projectile_scale_ *= percentage_end_sequence;
		laser_color_.a = 200 * percentage_end_sequence;
		shape_projectile_.setFillColor(laser_color_);
	}
	time_since_created_ += delta_t;
	percentage_time_elapsed_ = time_since_created_ / max_time_;
	projectile::update(delta_t);
}
