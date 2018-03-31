#include "warning_leaving_game_area.h"
#include "g_vars.hpp"

warning_leaving_game_area::warning_leaving_game_area()
{
	warning_message_ = text(
		"WARNING: LEAVING NAVIGABLE SPACE", 
		sf::Vector2f(g_vars::view_width / 2, 
			g_vars::view_height / 2 - 200), 
		text::warning_title, text::center);

	distance_until_termination_ = text(
		"PLACEHOLDER: distance until termination", 
		sf::Vector2f(g_vars::view_width / 2, 
			g_vars::view_height / 2 - 160), 
		text::warning, text::center);

	time_until_termination_ = text(
		"PLACEHOLDER: time until termination", 
		sf::Vector2f(g_vars::view_width / 2, 
			g_vars::view_height / 2 - 130), 
		text::warning, text::center);

	alpha_channel_increasing_ = true;
	overlay_color_ = sf::Color(214, 4, 4, 0);
	overlay_.setFillColor(overlay_color_);
}

warning_leaving_game_area::~warning_leaving_game_area()
{
}

void warning_leaving_game_area::update(float delta_t)
{
	if(alpha_channel_increasing_)
	{
		++overlay_color_.a;
		if(overlay_color_.a >= 60)
		{
			alpha_channel_increasing_ = false;
		}
	}
	else
	{
		--overlay_color_.a;
		if (overlay_color_.a <= 15)
		{
			alpha_channel_increasing_ = true;
		}
	}
	overlay_.setFillColor(overlay_color_);
	overlay::update(delta_t);
}

void warning_leaving_game_area::draw(sf::RenderWindow& main_win)
{
	overlay::draw(main_win);
	warning_message_.draw(main_win);
	distance_until_termination_.draw(main_win);
	time_until_termination_.draw(main_win);
}
