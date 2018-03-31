#include "missile.h"



missile::missile(const Vector2f& position, Vector2f direction, float angle) : aoe_projectile(position, 4, direction, angle)
{
	projectile_damage_ = 20;
	max_force_ = 1000;
	velocity_ = direction * max_force_;
	max_time_ = 1.0f;

	set_shape_points(shape_projectile_, 9, 4);
	rotation_angle_ = angle;
	proj_color_ = Color(160, 160, 160, 255);
	proj_color_.a = 200;
	shape_projectile_.setFillColor(proj_color_);
}

missile::~missile()
{
}

void missile::update(float delta_t)
{
	if (hasExploded || !is_alive_)
	{
		static const auto percentage_start_end_sequence = 0.80f;
		if (time_since_created_ >= max_time_)
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
			proj_color_.a = 200 * percentage_end_sequence;
		}
		else if (!hasExploded)
		{
			is_alive_ = true;
			explode(position_);
		}
		time_since_created_ += delta_t;
		percentage_time_elapsed_ = time_since_created_ / max_time_;
		projectile::update(delta_t);
	}
	else if (!hasExploded)
	{
		static const auto percentage_start_end_sequence = 0.80f;
		if (time_since_created_ >= max_time_)
		{
			explode(position_);
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
			proj_color_.a = 200 * percentage_end_sequence;
		}
		time_since_created_ += delta_t;
		percentage_time_elapsed_ = time_since_created_ / max_time_;
		projectile::update(delta_t);
	}
}

void missile::explode(Vector2f explosion_area)
{
	hasExploded = true;
	time_since_created_ = 0;
	projectile_damage_ = 5000;
	max_force_ = 1000;
	velocity_ = Vector2f(0, 0);
	max_time_ = 0.1f;

	set_shape_points(shape_projectile_, 50, 50);
	rotation_angle_ = 45;
	proj_color_ = Color::Red;
	proj_color_.a = 200;
	shape_projectile_.setFillColor(proj_color_);
}
