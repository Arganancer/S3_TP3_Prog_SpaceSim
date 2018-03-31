#include "station.h"
#include "hull.h"

station::station(const Vector2f& position): 
	npc(position, 50)
{
	hull_ = new hull(Vector2f(0, 0), 0, 128);
	hull_->add_component(Vector2f(24, 0), 270, hull::hangar_e, 32);
	hull_->add_component(Vector2f(64, 0), 270, hull::hangar_e, 32);
	hull_->add_weapon(Vector2f(32, 32), laser_weapon_e);
	hull_->add_weapon(Vector2f(96, 32), laser_weapon_e);
	hull_->add_weapon(Vector2f(96, 96), laser_weapon_e);
	hull_->add_weapon(Vector2f(32, 96), laser_weapon_e);

	hull_max_endurance_ = 5000;
	hull_current_endurance_ = hull_max_endurance_;

	max_force_ = 4000.0f;
	max_torque_ = 5000.0f;
	// TODO: Replace shape with sprite once it is implemented.
	const float ship_scale = 128;

	view_radius_length_ = 800;
	attack_radius_length_ = 500;
	points_value_ *= 400;
	money_value_ = rand() % 150 + 300;
}

station::~station()
{
	for (auto npcs_it = npcs_to_spawn_.begin(); npcs_it != npcs_to_spawn_.end(); ++npcs_it)
		delete *npcs_it;
	npcs_to_spawn_.clear();
}

container_t::list_t<npc*>& station::get_npcs()
{
	return npcs_to_spawn_;
}

void station::update(float delta_t)
{
	npc::update(delta_t);
	hull_->update_hangars(delta_t, nearest_enemy_, current_state_);
	hull_->update_weapons(delta_t, aiming_target_);
}

container_t::list_t<fighter*>* station::get_launched_fighters() const
{
	return hull_->get_launched_fighters();
}

pair<int, int> station::get_fighter_points_money() const
{
	return hull_->get_hangar_values();
}