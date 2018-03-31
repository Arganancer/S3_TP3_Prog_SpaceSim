#ifndef SHIP_HANGAR_H
#define SHIP_HANGAR_H
#include "collidable.h"
#include "list_t.hpp"
#include "component.h"

class ship;
class fighter;

class ship_hangar : public component
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	ship_hangar(Vector2f default_position, float default_angle, float component_size);
	~ship_hangar();

	// ACCESSORS
	void draw(RenderWindow& main_win) override;

	// MUTATORS
	void update(float delta_t, ship* nearest_enemy);
	void launch_fighter();
	static bool init();
	container_t::list_t<fighter*>* get_launched_fighters();
	int get_current_dead_fighter_points() const;
	int get_current_dead_fighter_money() const;
	void reset_points_money();

protected:
	static Texture hangar_texture_;

	ship* nearest_enemy_;
	container_t::list_t<fighter*> docked_fighters_;
	container_t::list_t<fighter*> launched_fighters_;
	const int max_fighters_;

	const float time_between_spawns_;
	float time_since_last_spawn_;

	const float time_between_launches_;
	float time_since_last_launch_;

	int points_value_;
	int money_value_;
};

#endif