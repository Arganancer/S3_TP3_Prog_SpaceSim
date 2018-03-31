#include "fighter.h"
#include "ship_hangar.h"
#include "tools.hpp"
#include "hull.h"

const float fighter::launch_speed_ = 150;

fighter::fighter(ship_hangar* home_hangar) : 
	npc(Vector2f(0, 0), 15),
	home_hangar_(home_hangar),
	current_secondary_state_(docked),                              
	max_flying_time_(7.0f), 
	flying_time_left_(0)
{
	hull_ = new hull(Vector2f(0, 0), 0, 16);
	hull_->set_is_fighter();
	hull_max_endurance_ = 50;
	hull_current_endurance_ = hull_max_endurance_;

	max_force_ = 3000;
	max_torque_ = 4000;
	delete behavior_;
	behavior_ = ai::behavior_factory::create_behavior(ai::behavior_factory::suicidal_e);

	view_radius_length_ = 700;
	attack_radius_length_ = 200;

	points_value_ *= 10;
	money_value_ = rand() % 10 + 5;
}

fighter::~fighter()
{
}

void fighter::update(float delta_t)
{
	switch(current_secondary_state_)
	{
	case flying:
		npc::update(delta_t);
		flying_time_left_ -= delta_t;
		if (flying_time_left_ <= 0)
		{
			flying_time_left_ = max_flying_time_;
			current_secondary_state_ = docking;
		}
		break;
	case docking:
	{
		is_throttling_ = true;
		// Find direction towards home hangar:
		desired_direction_ = tools::vec_util::direction(position_, home_hangar_->get_position());
		throttling_direction_ = get_throttling_direction(desired_direction_, velocity_);
		force_ = throttling_direction_ * max_force_;
		ship::update(delta_t);
		if (tools::vec_util::magnitude(position_, home_hangar_->get_position()) < 10)
			current_secondary_state_ = docked;
		break;
	}
	case docked:
		is_throttling_ = false;
		break;
	}
}

bool fighter::get_is_docked() const
{
	if (current_secondary_state_ == docked)
		return true;
	return false;
}

void fighter::launch_fighter(Vector2f direction, Vector2f position)
{
	is_throttling_ = true;
	velocity_ = direction * launch_speed_;
	position_ = position;
	flying_time_left_ = max_flying_time_;
	current_secondary_state_ = flying;
}