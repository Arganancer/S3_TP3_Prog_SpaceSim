#include "pickupable.h"
#include <SFML/Graphics.hpp>
#include "tools.hpp"

pickupable::pickupable(Vector2f position) : collidable(position, 0)
{
	width = 50;
	height = 50;
	max_force_ = 0;
	velocity_ = Vector2f(0, 0);
	shape_.setPosition(position);
	shape_.setPointCount(4);
	shape_.setPoint(0, Vector2f(0, 0));
	shape_.setPoint(1, Vector2f(width, 0));
	shape_.setPoint(2, Vector2f(width, height));
	shape_.setPoint(3, Vector2f(0, height));
	shape_.setOrigin(width * 0.5f, height * 0.5f);
	rotation_angle_ = 0;
	shape_.setFillColor(Color::Cyan);

	int temp = rand() % 5 + 1;

	if (temp == 1)
		bonus_weapon = plasma_weapon_e;
	if (temp == 2)
		bonus_weapon = suicide_drone_launcher_e;
	if (temp == 3)
		bonus_weapon = nuke_launcher_e;
	if (temp == 4)
		bonus_weapon = missile_launcher_e;
	if (temp == 5)
		bonus_weapon = gatling_gun_e;
}

pickupable::~pickupable()
{
}

type_weapon pickupable::get_this_bonus_weapon() const
{
	return bonus_weapon;
}

void pickupable::draw(RenderWindow& main_win)
{
	main_win.draw(shape_);
}

FloatRect pickupable::get_global_bounds() const
{
	return shape_.getGlobalBounds();
}

vector<Vector2f> pickupable::get_axes()
{
	vector<Vector2f> axes;
	for (size_t i = 0; i < shape_.getPointCount(); i++)
	{
		Transform shape_transform = shape_.getTransform();
		const auto point1 = shape_transform.transformPoint(
			shape_.getPoint(i));
		const auto point2 = shape_transform.transformPoint(
			shape_.getPoint(i + 1 == shape_.getPointCount() ? 0 : i + 1));
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

vector<ConvexShape> pickupable::get_shapes()
{
	vector<ConvexShape> shape;
	shape.push_back(shape_);
	return shape;
}

bool pickupable::init()
{
	return true;
}
