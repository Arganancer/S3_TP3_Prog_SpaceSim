#include "overlay.h"
#include "g_vars.hpp"

overlay::overlay()
{
	overlay_.setSize(sf::Vector2f(g_vars::view_width, g_vars::view_height));
}

overlay::~overlay()
{
}

void overlay::update(float delta_t)
{
}

void overlay::draw(sf::RenderWindow& main_win)
{
	main_win.draw(overlay_);
}
