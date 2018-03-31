#include "user_interface.h"
#include "g_vars.hpp"

user_interface::user_interface(): 
	default_bar_width_(200),
	default_bar_height_(20),
	ship_health_percentage_(1), 
	ship_shield_percentage_(0), 
	points_(0), 
	money_(0),
	respawn_price_(0)
{
	// Health and Shield bar colors:
	shield_color_ = Color(48, 189, 255, 200);
	health_color_ = Color(64, 239, 33, 200);
	neutral_color_ = Color(136, 143, 147, 50);

	health_total_.setSize(Vector2f(default_bar_width_, default_bar_height_));
	health_total_.setPosition(g_vars::view_width / 2 - default_bar_width_ / 2, g_vars::view_height - default_bar_height_);
	health_total_.setFillColor(neutral_color_);
	health_remaining_.setSize(Vector2f(default_bar_width_ * ship_health_percentage_, default_bar_height_));
	health_remaining_.setPosition(g_vars::view_width / 2 - default_bar_width_ / 2, g_vars::view_height - default_bar_height_);
	health_remaining_.setFillColor(health_color_);

	shield_total_.setSize(Vector2f(default_bar_width_, default_bar_height_));
	shield_total_.setPosition(g_vars::view_width / 2 - default_bar_width_ / 2, g_vars::view_height - default_bar_height_ * 2);
	shield_total_.setFillColor(neutral_color_);
	shield_remaining_.setSize(Vector2f(default_bar_width_ * ship_shield_percentage_, default_bar_height_));
	shield_remaining_.setPosition(g_vars::view_width / 2 - default_bar_width_ / 2, g_vars::view_height - default_bar_height_ * 2);
	shield_remaining_.setFillColor(shield_color_);

	points_text_ = text(
		"Score :" + to_string(points_),
		Vector2f(20, 20),
		text::normal,
		text::left);

	money_text_ = text(
		to_string(money_) + "$",
		Vector2f(g_vars::view_width -20, 20),
		text::normal,
		text::right);

	next_respawn_text_ = text(
		"Respawn price: " + to_string(respawn_price_) + "$",
		Vector2f(g_vars::view_width - 20, 50),
		text::normal,
		text::right);

	ship_pos_text_ = text(
		"x: " + to_string(hero_ship_position_.x) + " y: " + to_string(hero_ship_position_.y),
		Vector2f(g_vars::view_width / 2, 20),
		text::normal,
		text::center);
}

user_interface::~user_interface()
{
}

void user_interface::update_hero_ship(Vector2f position, float health_percentage, float shield_percentage)
{
	if(position != hero_ship_position_)
	{
		hero_ship_position_ = position;
		ship_pos_text_.set_string("x: " + to_string(int(hero_ship_position_.x)) + " y: " + to_string(int(hero_ship_position_.y)));
	}
	if(health_percentage != ship_health_percentage_)
	{
		ship_health_percentage_ = std::max(health_percentage, 0.0f);
		health_remaining_.setSize(Vector2f(default_bar_width_ * ship_health_percentage_, default_bar_height_));
	}
	if (shield_percentage != ship_shield_percentage_)
	{
		ship_shield_percentage_ = std::max(shield_percentage, 0.0f);
		shield_remaining_.setSize(Vector2f(default_bar_width_ * ship_shield_percentage_, default_bar_height_));
	}
}

void user_interface::update_points_money(int points, int money, int respawn_price)
{
	if(points != points_)
	{
		points_ = points;
		points_text_.set_string("Score :" + to_string(points_));
	}
	if (money != money_)
	{
		money_ = money;
		money_text_.set_string(to_string(money_) + "$");
		money_text_.update();
	}
	if (respawn_price != respawn_price_)
	{
		respawn_price_ = respawn_price;
		next_respawn_text_.set_string("Respawn price: " + to_string(respawn_price_) + "$");
		next_respawn_text_.update();
	}
}

void user_interface::update_incoming_enemies(container_t::list_t<type_weapon> incoming_enemies)
{
	// Not implemented.
}

void user_interface::draw(RenderWindow& main_win) const
{
	points_text_.draw(main_win);
	money_text_.draw(main_win);
	next_respawn_text_.draw(main_win);
	ship_pos_text_.draw(main_win);
	main_win.draw(health_total_);
	main_win.draw(health_remaining_);
	main_win.draw(shield_total_);
	main_win.draw(shield_remaining_);
}
