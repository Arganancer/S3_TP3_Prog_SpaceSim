#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "npc.h"
#include "type_weapon.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "text.h"

class user_interface
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	user_interface();
	~user_interface();

	// MUTATORS
	void update_hero_ship(Vector2f position, float health_percentage, float shield_percentage);
	void update_points_money(int points, int money, int respawn_price);
	void update_incoming_enemies(container_t::list_t<type_weapon> incoming_enemies);

	// ACCESSORS
	void draw(RenderWindow& main_win) const;

private:
	RectangleShape health_total_;
	RectangleShape health_remaining_;
	RectangleShape shield_total_;
	RectangleShape shield_remaining_;
	const float default_bar_width_;
	const float default_bar_height_;
	Color health_color_;
	Color shield_color_;
	Color neutral_color_;

	text ship_pos_text_;
	text points_text_;
	text money_text_;
	text next_respawn_text_;

	Vector2f hero_ship_position_;
	float ship_health_percentage_;
	float ship_shield_percentage_;
	int points_;
	int money_;
	int respawn_price_;
	//container_t::list_t<> incoming_enemies_; <-- To be implemented once an NPC factory exists.
	container_t::list_t<type_weapon> incoming_enemies_;
};

#endif
