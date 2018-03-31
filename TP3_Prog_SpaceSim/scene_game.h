#ifndef SCENE_GAME_H
#define SCENE_GAME_H
#include "scene.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "text.h"
#include "player_ship.h"
#include "star.h"
#include "overlay.h"
#include "station.h"
#include "projectile.h"
#include "pickupable.h"
#include "user_interface.h"

class scene_game : public scene
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	explicit scene_game(RenderWindow& main_win);
	~scene_game();

	// MUTATORS
	scene_factory::type_scene update(float delta_t) override;
	void hero_leaving_game_area(player_ship& player_ship);
	static bool broad_phase_detection(collidable* entity1, collidable* entity2);
	tuple<bool, Vector2f, float> sat_movables_colliding(collidable* movable1, collidable* movable2) const;
	static Vector2f get_shape_projection_on_axis(ConvexShape shape, Vector2f axis);
	void collision_resolution(collidable* movable1, collidable* movable2, Vector2f, float, float);

	// ACCESSORS
	void draw(RenderWindow& main_win) override;
	int get_points() const;

	// OBSERVERS
	void register_observer(user_interface* ui_observer);
	void unregister_observer(user_interface* ui_observer);
	void notify_observers();

private:
	// Entities
	player_ship p_ship_;
	container_t::list_t<station*> stations_;
	container_t::list_t<npc*> npcs_;
	vector<star> stars_;
	container_t::list_t<projectile*> active_projectiles_;
	container_t::list_t<pickupable*> active_pickupables_;

	// Overlays
	user_interface* ui_;
	overlay* active_overlay_;
	View view_hud_;

	// Paused variables
	bool game_is_paused_;
	RectangleShape paused_overlay_;
	text paused_text_;
	text paused_return_mm_prompt_;

	// Observer
	container_t::list_t<user_interface*> ui_observers_;
	int current_points_;
	int points_last_frame_;
	int current_money_;
	int money_last_frame_;

	// Respawn variables:
	int current_respawn_price_;
	const float respawn_delay_;
	float current_respawn_time_;
	Vector2f respawn_position_;
	bool respawning_;
};
#endif