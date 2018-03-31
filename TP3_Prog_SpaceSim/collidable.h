#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "movable.h"

class collidable : public movable
{
public:
	// Constructors/Destructors
	collidable();
	explicit collidable(Vector2f position, float mass);
	~collidable();

	// Accessors
	virtual FloatRect get_global_bounds() const = 0;
	virtual vector<Vector2f> get_axes() = 0;
	virtual vector<ConvexShape> get_shapes() = 0;

	// Mutators
	bool intersects(collidable& entity) const;
};

#endif