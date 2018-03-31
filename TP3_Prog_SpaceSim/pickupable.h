#ifndef PICKUPABLE_H
#define PICKUPABLE_H
#include "collidable.h"
#include "type_weapon.h"
#include <SFML/Graphics/RectangleShape.hpp>

class pickupable : public collidable
{
public:
	pickupable(Vector2f position);
	~pickupable();
	type_weapon get_this_bonus_weapon() const;
	
	void draw(RenderWindow& main_win) override;
	FloatRect get_global_bounds() const override;
	vector<Vector2f> get_axes() override;
	vector<ConvexShape> get_shapes() override;
private:
	static bool init();
	type_weapon bonus_weapon;
	ConvexShape shape_;
	float width;
	float height;
};

#endif
