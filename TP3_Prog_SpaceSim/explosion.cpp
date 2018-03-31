#include "explosion.h"

using namespace sf;

explosion::explosion(sf::Vector2f position) : projectile(position, 50, Vector2f(0,0), 0)
{
	time_since_created_ = 0;

	projectile_damage_ = 5000;
	max_force_ = 0;
	velocity_ = Vector2f(0,0);
	max_time_ = 10.0f;

	set_shape_points(shape_projectile_, 5, 5);
	rotation_angle_ = 45;
	explo_color = Color(204, 102, 0, 200);
	shape_projectile_.setFillColor(explo_color);
}

explosion::~explosion()
{
}

void explosion::update(float delta_t)
{
	if (time_since_created_ >= max_time_)
	{
		kill_entity();
	}
	time_since_created_ += delta_t;
}

void explosion::draw(RenderWindow& main_win)
{
	projectile::draw(main_win);
}

FloatRect explosion::get_global_bounds() const
{
	return projectile::get_global_bounds();
}

vector<Vector2f> explosion::get_axes()
{
	return projectile::get_axes();
}

vector<ConvexShape> explosion::get_shapes()
{
	return projectile::get_shapes();
}

