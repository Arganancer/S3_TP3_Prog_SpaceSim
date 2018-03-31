#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Texture.hpp>
class hull;

using namespace sf;

class component 
{
	friend class hull;
public:
	enum layer
	{
		one,
		two,
		three,
		four,
	};
	// CONSTRUCTORS/DESTRUCTORS
	component(Vector2f default_position, float default_angle, float component_size);
	virtual ~component();

	// ACCESSORS
	virtual void draw(RenderWindow& main_win);
	Vector2f get_position() const;

protected:
	// MUTATORS
	virtual void update(float rotation_angle, Transform transform);
	static void set_shape_points(ConvexShape& shape, float size);
	static void set_shape_points(ConvexShape& shape, float width, float height);

	ConvexShape component_shape_;
	const Vector2f default_pos_;
	const float default_angle_;
	layer layer_;
};

#endif