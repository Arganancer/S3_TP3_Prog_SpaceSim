#pragma once
#ifndef HARPOON_H
#define HARPOON_H
#include "projectile.h"


class harpoon: public projectile
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	harpoon(const Vector2f& position, Vector2f direction, float angle);
	~harpoon();

	void update(float delta_t) override;
private:
	sf::Color harpoon_color_;
};

#endif