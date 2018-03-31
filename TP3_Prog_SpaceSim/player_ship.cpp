#include "player_ship.h"
#include "input_manager.h"
//#include "weapon_factory.h"
#include "tools.hpp"
#include "hull.h"
#include "user_interface.h"

using namespace std;

player_ship::player_ship(Vector2f position) :
	ship(position, 12),
	position_last_update_(position),
	health_percentage_last_update_(1),
	shield_percentage_last_update_(0)
{
	const auto size = 32;
	hull_ = new hull(Vector2f(0, 0), 0, size);
	hull_->add_component(Vector2f(size, size * 0.5f), 0, hull::cockpit_e, 24);
	hull_->add_component(Vector2f(0, size * 0.5f), 0, hull::thruster_e, 24);
	hull_->add_component(Vector2f(size * 0.5f, 0), 0, hull::shield_generator_e, 16);
	hull_->add_weapon(Vector2f(0, 0), laser_weapon_e);	// suicide_drone_launcher_e plasma_weapon_e nuke_launcher_e missile_launcher_e laser_weapon_e
	hull_->add_weapon(Vector2f(size, 0), laser_weapon_e);
	hull_->add_weapon(Vector2f(size, size), laser_weapon_e);
	hull_->add_weapon(Vector2f(0, size), laser_weapon_e);
	owner_ = player;
	hull_max_endurance_ = 3000;
	hull_current_endurance_ = hull_max_endurance_;
	max_force_ = 10000;
	max_torque_ = 8000;
	player_id_ = 0;
}

player_ship::~player_ship()
{
}

void player_ship::update(float delta_t)
{
	if (!is_alive_)
	{
		delete hull_;
		hull_ = new hull(Vector2f(0, 0), 0, 32);
	}

	if (is_alive_)
	{
		// INPUTS
		// Only update velocity if left joystick is being pressed.
		const auto left_joystick_pos = input_manager::get_input_manager()->get_left_joystick_pos(player_id_);
		if (left_joystick_pos.x != 0 || left_joystick_pos.y != 0)
		{
			throttling_direction_ = tools::vec_util::direction(left_joystick_pos);
			force_ = throttling_direction_ * max_force_;
			is_throttling_ = true;
		}
		else
		{
			is_throttling_ = false;
		}
	}
	ship::update(delta_t);

	if (is_alive_)
	{
		// WEAPON UPDATES
		const auto right_joystick_pos = input_manager::get_input_manager()->get_right_joystick_pos(player_id_);
		if (right_joystick_pos.x != 0 || right_joystick_pos.y != 0)
		{
			// Calculate necessary variables for projectiles:
			desired_weapon_angle_ = tools::vec_util::angle_d(right_joystick_pos);
			aiming_target_ = tools::vec_util::direction(tools::vec_util::angle_r(desired_weapon_angle_));
			aiming_target_ *= 400.0f;
			aiming_target_ += position_;
		}
		hull_->update_weapons(delta_t, aiming_target_);
		if (input_manager::get_input_manager()->get_button_is_pressed(input_manager::rb, player_id_))
		{
			hull_->fire_weapons(delta_t, owner_, aiming_target_);
		}
	}
	
	// Update observer variables
	if(position_last_update_ != position_ ||
		health_percentage_last_update_ != hull_percentage_strength_ ||
		shield_percentage_last_update_ != current_shield_percentage_strength_)
	{
		notify_observers();
	}
	position_last_update_ = position_;
	health_percentage_last_update_ = hull_percentage_strength_;
	shield_percentage_last_update_ = current_shield_percentage_strength_;
}

void player_ship::register_observer(user_interface* ui_observer)
{
	ui_observers_.push_back(ui_observer);
}

void player_ship::unregister_observer(user_interface* ui_observer)
{
	for (auto it = ui_observers_.begin(); it != ui_observers_.end(); ++it)
	{
		if(*it == ui_observer)
		{
			ui_observers_.erase(it);
			break;
		}
	}
}

void player_ship::notify_observers()
{
	for (auto it = ui_observers_.begin(); it != ui_observers_.end(); ++it)
	{
		it->update_hero_ship(position_, hull_percentage_strength_, current_shield_percentage_strength_);
	}
}

void player_ship::add_bonus_weapon(type_weapon weapon) const
{
	hull_->add_weapon(Vector2f(32 / 2, 32 / 2), weapon);
}

void player_ship::revive(Vector2f position)
{
	position_ = position;
	rotation_angle_ = 0;
	velocity_ = Vector2f(0,0);
	const auto size = 32;
	hull_ = new hull(Vector2f(0, 0), 0, size);
	hull_->add_component(Vector2f(size, size * 0.5f), 0, hull::cockpit_e, 24);
	hull_->add_component(Vector2f(0, size * 0.5f), 0, hull::thruster_e, 24);
	hull_->add_component(Vector2f(size * 0.5f, 0), 0, hull::shield_generator_e, 16);
	hull_->add_weapon(Vector2f(0, 0), laser_weapon_e);
	hull_->add_weapon(Vector2f(size, 0), laser_weapon_e);
	hull_->add_weapon(Vector2f(size, size), laser_weapon_e);
	hull_->add_weapon(Vector2f(0, size), laser_weapon_e);
	owner_ = player;
	hull_max_endurance_ = 3000;
	hull_current_endurance_ = hull_max_endurance_;
	is_alive_ = true;
}
