#include "component.h"

component::component(Vector2f default_position, float default_angle, float component_size) :
	default_pos_(default_position),
	default_angle_(default_angle), 
	layer_(four)
{
	set_shape_points(component_shape_, component_size);
}

component::~component()
{
}

void component::draw(RenderWindow& main_win)
{
	main_win.draw(component_shape_);
}

void component::update(float rotation_angle, Transform transform)
{
	component_shape_.setPosition(transform.transformPoint(default_pos_));
	component_shape_.setRotation(rotation_angle + default_angle_);
}

void component::set_shape_points(ConvexShape& shape, float size)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(0, 0));
	shape.setPoint(1, Vector2f(size, 0));
	shape.setPoint(2, Vector2f(size, size));
	shape.setPoint(3, Vector2f(0, size));
	shape.setOrigin(size * 0.5f, size * 0.5f);
}

void component::set_shape_points(ConvexShape& shape, float width, float height)
{
	shape.setPointCount(4);
	shape.setPoint(0, Vector2f(0, 0));
	shape.setPoint(1, Vector2f(width, 0));
	shape.setPoint(2, Vector2f(width, height));
	shape.setPoint(3, Vector2f(0, height));
	shape.setOrigin(width * 0.5f, height * 0.5f);
}

Vector2f component::get_position() const
{
	return component_shape_.getPosition();
}
