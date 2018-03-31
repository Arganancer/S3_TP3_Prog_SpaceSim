#include "collidable.h"
#include "tools.hpp"

collidable::collidable(): movable(Vector2f(0,0), 0){}

collidable::collidable(Vector2f position, float mass) : movable(position, mass){}

collidable::~collidable(){}

bool collidable::intersects(collidable& entity) const
{
	// intersects (this is a basic/preliminary verification, AABB)
	if(get_global_bounds().intersects(entity.get_global_bounds()))
	{
		return true;
	}
	return false;
}