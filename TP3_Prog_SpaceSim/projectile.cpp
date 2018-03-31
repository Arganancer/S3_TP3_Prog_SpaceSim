#include "projectile.h"
#include "tools.hpp"

projectile::projectile(Vector2f position, float mass, Vector2f direction, float angle):
	collidable(position, mass),
	owner_(npc),
	max_time_(0),
	projectile_scale_(0)
{
	direction_ = direction;
	projectile_damage_ = 0;
	percentage_time_elapsed_ = 0;
	time_since_created_ = 0;
}

projectile::~projectile()
{
}

void projectile::update(float delta_t)
{
	calculate_velocity(delta_t);
	shape_projectile_.setPosition(position_);
	shape_projectile_.setRotation(rotation_angle_);
}

int projectile::get_damage() const
{
	return projectile_damage_;
}

void projectile::set_owner(faction owner)
{
	owner_ = owner;
}

projectile::faction projectile::get_owner() const
{
	return owner_;
}

void projectile::draw(RenderWindow& main_win)
{
	main_win.draw(shape_projectile_);
}

FloatRect projectile::get_global_bounds() const
{
	return shape_projectile_.getGlobalBounds();
}

vector<Vector2f> projectile::get_axes()
{
	vector<Vector2f> axes;
		for (size_t i = 0; i < shape_projectile_.getPointCount(); i++)
		{
			Transform shape_transform = shape_projectile_.getTransform();
			const auto point1 = shape_transform.transformPoint(
				shape_projectile_.getPoint(i));
			const auto point2 = shape_transform.transformPoint(
				shape_projectile_.getPoint(i + 1 == shape_projectile_.getPointCount() ? 0 : i + 1));
			const auto edge = point1 - point2;
			/* The normal of an edge can obtained by
			flipping the coordinates and negating one. */
			const auto unit_normal = tools::vec_util::direction_normal(edge);

			/* When evaluating collisions using the SAT method,
			* there is no need to verify axes that are parallel. */
			auto parallel_axis_exists = false;
			for (auto axes_it = axes.begin(); axes_it != axes.end(); ++axes_it)
			{
				if (tools::vec_util::dot(*axes_it, unit_normal))
				{
					parallel_axis_exists = true;
					break;
				}
			}
			if (!parallel_axis_exists)
			{
				axes.push_back(unit_normal);
			}
		}
	return axes;
}

vector<ConvexShape> projectile::get_shapes()
{
	vector<ConvexShape> shape;
	shape.push_back(shape_projectile_);
	return shape;
}

void projectile::set_shape_points(ConvexShape& shape, float size)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(0, 0));
	shape.setPoint(1, Vector2f(size, 0));
	shape.setPoint(2, Vector2f(size, size));
	shape.setPoint(3, Vector2f(0, size));
	shape.setOrigin(size * 0.5f, size * 0.5f);
}

void projectile::set_shape_points(ConvexShape& shape, float width, float height)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(0, 0));
	shape.setPoint(1, Vector2f(width, 0));
	shape.setPoint(2, Vector2f(width, height));
	shape.setPoint(3, Vector2f(0, height));
	shape.setOrigin(width * 0.5f, height * 0.5f);
}

bool projectile::is_emp() const
{
	return emp;
}
