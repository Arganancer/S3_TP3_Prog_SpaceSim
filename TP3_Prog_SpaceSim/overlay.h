#ifndef OVERLAY_H
#define OVERLAY_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class overlay
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	overlay();
	virtual ~overlay();

	// MUTATORS
	virtual void update(float delta_t);

	// ACCESSORS
	virtual void draw(sf::RenderWindow& main_win);

protected:
	sf::RectangleShape overlay_;
	sf::Color overlay_color_;
};

#endif