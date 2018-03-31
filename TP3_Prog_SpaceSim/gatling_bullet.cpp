#include "gatling_bullet.h"

gatling_bullet::gatling_bullet(const Vector2f& position, Vector2f direction, float angle) : projectile(position, 11, direction, angle)
{
	projectile_damage_ = 5;
	max_force_ = 1000;
	velocity_ = direction * max_force_;
	max_time_ = 1.0f;

	set_shape_points(shape_projectile_, 5, 2);
	rotation_angle_ = angle;
	bullet_color_ = Color(245, 186, 99, 200);
	shape_projectile_.setFillColor(bullet_color_);
}

gatling_bullet::~gatling_bullet()
{
}

void gatling_bullet::update(float delta_t)
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
		bullet_color_.a = 200 * percentage_end_sequence;
	}
	time_since_created_ += delta_t;
	percentage_time_elapsed_ = time_since_created_ / max_time_;
	projectile::update(delta_t);
}
