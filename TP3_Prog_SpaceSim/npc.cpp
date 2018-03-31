#include "npc.h"
#include "g_vars.hpp"
#include "tools.hpp"
#include "hull.h"

npc::npc(Vector2f position, float mass ) :
	ship(position, mass),
	view_radius_length_(0),
	attack_radius_length_(0),
	nearest_enemy_(nullptr),
	nearest_ally_(nullptr),
	current_state_(ai::behavior::idle_e), 
	points_value_(0), 
	money_value_(0)
{
	const auto ai = rand() % 100;
	if (ai > 90)
	{
		behavior_ = ai::behavior_factory::create_behavior(ai::behavior_factory::suicidal_e);
		points_value_ = 4;
	}
	else if (ai > 75)
	{
		behavior_ = ai::behavior_factory::create_behavior(ai::behavior_factory::aggressive_e);
		points_value_ = 3;
	}
	else if (ai > 15)
	{
		behavior_ = ai::behavior_factory::create_behavior(ai::behavior_factory::balanced_e);
		points_value_ = 3;
	}
	else
	{
		behavior_ = ai::behavior_factory::create_behavior(ai::behavior_factory::coward_e);
		points_value_ = 2;
	}

	experience_ = ai::experience_factory::create_experience(ai::experience_factory::soldier_e, 4, false);
}

npc::~npc()
{
	delete behavior_;
	delete experience_;
	nearest_enemy_ = nullptr;
}

void npc::update(float delta_t)
{
	update_ai(delta_t);
	ship::update(delta_t);
}

void npc::update_ai(float delta_t)
{
	// Get information necessary for behavior update.
	auto distance_to_nearest_enemy = float();
	auto enemy_in_attack_range = false;
	auto enemy_in_view = false;
	auto ally_in_proximity = false;
	auto state_of_nearest_ally = ai::behavior::type_state::retreating_e;
	const auto enemy_has_attacked = false; // TODO: Implement.

	if (nearest_enemy_)
	{
		distance_to_nearest_enemy = tools::vec_util::magnitude(position_, nearest_enemy_->get_position());
		enemy_in_attack_range = distance_to_nearest_enemy < attack_radius_length_;
		enemy_in_view = distance_to_nearest_enemy < view_radius_length_;
	}
	if (nearest_ally_)
	{
		ally_in_proximity = true; 
		state_of_nearest_ally = nearest_ally_->get_current_state();
	}

	// Update behavior.
	const auto new_state = behavior_->update(
		enemy_in_view, 
		enemy_in_attack_range, 
		enemy_has_attacked, 
		hull_percentage_strength_,
		ally_in_proximity, 
		state_of_nearest_ally, 
		current_state_, 
		delta_t);

	// Manage new direction if switched to roaming.
	if(new_state == ai::behavior::roaming_e != current_state_)
	{
		const auto random_angle = atan2f(rand() % 1000 - 500, rand() % 1000 - 500);
		roaming_direction_ = tools::vec_util::direction(random_angle);
		desired_direction_ = roaming_direction_;
	}

	// Turn ship around if it leaves the playable area while in roaming mode
	if (ai::behavior::roaming_e == current_state_)
	{
		if (position_.x < 0)
			roaming_direction_ = Vector2f(1, 0);
		else if (position_.x > g_vars::game_width)
			roaming_direction_ = Vector2f(-1, 0);
		if (position_.y < 0)
			roaming_direction_ = Vector2f(0, 1);
		else if (position_.y > g_vars::game_height)
			roaming_direction_ = Vector2f(0, -1);
		desired_direction_ = roaming_direction_;
	}

	Vector2f nearest_enemy_pos = Vector2f();
	if(nearest_enemy_)
	{
		nearest_enemy_pos = nearest_enemy_->get_position();
	}
	experience_->update(new_state, position_, nearest_enemy_pos);
	if (new_state != current_state_)
	{
		//const auto rof_modifier = experience_->get_rate_of_fire_modifier();
		//for (auto weap_it = active_weapons_.begin(); weap_it != active_weapons_.end(); ++weap_it)
		//{
		//	weap_it->set_modified_rof(rof_modifier);
		//}
	}

	current_state_ = new_state;

	switch (current_state_)
	{
	case ai::behavior::idle_e:
		{
			// Manage ship translation and rotation:
			throttling_direction_ = tools::vec_util::direction(tools::vec_util::angle_r(rotation_angle_));
			is_throttling_ = false;
			break;
		}
	case ai::behavior::roaming_e: 
		{
			// Manage ship translation and rotation:
			throttling_direction_ = roaming_direction_;
			force_ = roaming_direction_ * max_force_;
			is_throttling_ = true;
			break;
		}
	case ai::behavior::engaging_e:
		{
			// Manage ship translation and rotation:
			desired_direction_ = tools::vec_util::direction(position_, nearest_enemy_->get_position());
			throttling_direction_ = get_throttling_direction(desired_direction_, velocity_);
			force_ = throttling_direction_ * max_force_;
			is_throttling_ = true;
			break;
		}
	case ai::behavior::attacking_e: 
		{
			// Manage ship translation and rotation:
			throttling_direction_ = tools::vec_util::direction(position_, nearest_enemy_->get_position());
			force_ = Vector2f(0, 0);
			is_throttling_ = false;
			break;
		}
	case ai::behavior::retreating_e:
		{
			// Manage ship translation and rotation:
			desired_direction_ = tools::vec_util::direction(nearest_enemy_->get_position(), position_);
			throttling_direction_ = get_throttling_direction(desired_direction_, velocity_);
			force_ = throttling_direction_ * max_force_;
			is_throttling_ = true;
			break;
		}
	}
	if(experience_->get_is_firing())
	{
		attack(delta_t);
	}
}

void npc::set_nearest_enemy_and_ally(ship* enemy_ship, npc* ally_ship)
{
	nearest_enemy_ = enemy_ship;
	nearest_ally_ = ally_ship;
}

ai::behavior::type_state npc::get_current_state() const
{
	return current_state_;
}


void npc::attack(float delta_t)
{
	aiming_target_ = experience_->get_modified_aim(nearest_enemy_->get_velocity(), nearest_enemy_->get_position());
	hull_->fire_weapons(delta_t, owner_, aiming_target_);
}

Vector2f npc::get_throttling_direction(Vector2f desired_direction, Vector2f current_direction) const
{
	auto angle_between_desired_and_current =
		tools::vec_util::angle_d(desired_direction) - 
		tools::vec_util::angle_d(current_direction);
	if (fabs(angle_between_desired_and_current) > 3 && fabs(angle_between_desired_and_current) < 90)
	{
		if (tools::vec_util::magnitude(velocity_) > 1)
		{
			auto adjusted_direction_angle = tools::vec_util::angle_d(desired_direction);
			angle_between_desired_and_current +=
				(angle_between_desired_and_current > 180) ? -360 :
				(angle_between_desired_and_current < -180) ? 360 : 0;

			if (angle_between_desired_and_current > 0)
				adjusted_direction_angle += 10 + fabs(angle_between_desired_and_current * 0.3f);
			else
				adjusted_direction_angle -= 10 + fabs(angle_between_desired_and_current * 0.3f);

			return tools::vec_util::direction(tools::vec_util::angle_r(adjusted_direction_angle));
		}
	}
	return desired_direction;
}

int npc::get_point_value() const
{
	return points_value_;
}

int npc::get_money_value() const
{
	return money_value_;
}
