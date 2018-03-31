#ifndef HULL_H
#define HULL_H
#include "component.h"
#include "list_t.hpp"
#include "behavior.h"
#include "movable.h"
#include "type_weapon.h"
class ship;
class thruster;
class shield_generator;
class fighter;
class projectile;
class weapon;

class hull : public component
{
public:
	enum type_component
	{
		thruster_e,
		hull_e,
		shield_generator_e,
		cockpit_e,
		hangar_e,
	};
	// CONSTRUCTORS/DESTRUCTORS
	hull(Vector2f default_position, float default_angle, float hull_size);
	~hull();

	// MUTATORS
	void update(Vector2f position, float rotation_angle);
	void update_hangars(
		float delta_t, 
		ship* nearest_enemy, 
		ai::behavior::type_state current_state);
	void update_weapons(
		float delta_t, 
		Vector2f target);
	void add_component(
		Vector2f default_position,
		float default_angle,
		type_component component_type,
		float component_size);
	void add_weapon(
		Vector2f default_position,
		type_weapon weapon_type);
	static bool init();
	vector<ConvexShape> get_shapes();
	vector<Vector2f> get_axes();
	void set_is_fighter();
	std::pair<int, int> get_hangar_values();
	void set_is_colliding();

	// ACCESSORS
	void draw(RenderWindow& main_win) override;
	FloatRect get_global_bounds();
	container_t::list_t<projectile*>& get_projectiles();
	container_t::list_t<fighter*>* get_launched_fighters();
	void fire_weapons(float delta_t, movable::faction owner, Vector2f target);

protected:
	container_t::list_t<projectile*> projectiles_to_add_to_queue_;
	container_t::list_t<component*> components_;
	static Texture hull_textures_[4];
	static Texture fighter_texture_;
	int nb_of_weapons_;
};

#pragma region COMPONENT FACTORY
class component_factory
{
public:
	static component* create_component(
		Vector2f default_position,
		float default_angle,
		hull::type_component component_type, 
		float component_size);
private:
	component_factory() = delete;
};
#pragma endregion

#endif