#include "experience.h"
#include "tools.hpp"
#include <cstdlib>

#pragma region EXPERIENCE_BASE_CLASS
ai::experience::experience(int nb_of_weapons, bool has_hangars) :
	chances_of_perfect_aim_(0),
	last_state_(behavior::idle_e),
	firing_angle_modifier_(0), 
	angle_to_enemy_(0),
	rate_of_fire_modifier_(0),
	nb_of_weapons_(nb_of_weapons),
	nb_of_currently_active_weapons_(0),
	has_hangars_(has_hangars),
	is_firing_(false)
{
}

void ai::experience::update(
	behavior::type_state current_state, 
	Vector2f position, 
	Vector2f enemy_position)
{
	if (enemy_position != Vector2f())
	{
		angle_to_enemy_ = tools::vec_util::angle_d(position, enemy_position);
	}
	switch (current_state)
	{
	case behavior::attacking_e:
		evaluate_attacking(position, enemy_position);
		break;
	case behavior::engaging_e:
		evaluate_engaging(position, enemy_position);
		break;
	case behavior::retreating_e: 
		evaluate_retreating(position, enemy_position);
		break;
	case behavior::idle_e:
		is_firing_ = false;
		break; // No instructions currently for this state.
	case behavior::roaming_e:
		is_firing_ = false;
		break; // No instructions currently for this state.
	}
}

float ai::experience::get_rate_of_fire_modifier() const
{
	return rate_of_fire_modifier_;
}

int ai::experience::get_nb_of_active_weapons() const
{
	return nb_of_currently_active_weapons_;
}

bool ai::experience::get_is_firing() const
{
	return is_firing_;
}
#pragma endregion 

#pragma region ELITE
ai::elite::elite(int nb_of_weapons, bool has_hangars) : experience(nb_of_weapons, has_hangars)
{
}

ai::elite::~elite()
{
}

void ai::elite::update(
	behavior::type_state current_state, 
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

ai::manoeuvre* ai::elite::get_new_manoeuvre(bool is_fighter)
{
	// TODO: Define this behavior.
	return new manoeuvre;
}

sf::Vector2f ai::elite::get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position)
{
	// TODO: Define this behavior.
	return sf::Vector2f();
}

void ai::elite::evaluate_engaging(
	sf::Vector2f position, 
	sf::Vector2f enemy_position)
{
}

void ai::elite::evaluate_attacking(
	sf::Vector2f position, 
	sf::Vector2f enemy_position)
{
}

void ai::elite::evaluate_retreating(
	sf::Vector2f position, 
	sf::Vector2f enemy_position)
{
}
#pragma endregion 

#pragma region VETERAN
ai::veteran::veteran(int nb_of_weapons, bool has_hangars) : experience(nb_of_weapons, has_hangars)
{
}

ai::veteran::~veteran()
{
}

void ai::veteran::update(
	behavior::type_state current_state,
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

ai::manoeuvre* ai::veteran::get_new_manoeuvre(bool is_fighter)
{
	// TODO: Define this behavior.
	return new manoeuvre;
}

sf::Vector2f ai::veteran::get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position)
{
	// TODO: Define this behavior.
	return sf::Vector2f();
}

void ai::veteran::evaluate_engaging(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::veteran::evaluate_attacking(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::veteran::evaluate_retreating(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}
#pragma endregion 

#pragma region SOLDIER
ai::soldier::soldier(int nb_of_weapons, bool has_hangars) : 
	experience(nb_of_weapons, has_hangars)
{
	chances_of_perfect_aim_ = 90;
	firing_angle_modifier_ = 5;
	rate_of_fire_modifier_ = 1;
	nb_of_currently_active_weapons_ = nb_of_weapons_;
}

ai::soldier::~soldier()
{
}

void ai::soldier::update(
	behavior::type_state current_state,
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
	switch (current_state)
	{
	case behavior::attacking_e:
		if(current_state != last_state_)
		{
			chances_of_perfect_aim_ = 90;
			firing_angle_modifier_ = 5;
			rate_of_fire_modifier_ = 1;
			nb_of_currently_active_weapons_ = nb_of_weapons_;
			is_firing_ = true;
		}
		break;
	case behavior::engaging_e:
		if (current_state != last_state_)
		{
			chances_of_perfect_aim_ = 80;
			firing_angle_modifier_ = 7;
			rate_of_fire_modifier_ = 1.2f;
			if(nb_of_weapons_ > 4)
			{
				nb_of_currently_active_weapons_ = nb_of_weapons_ - 1;
			}
			is_firing_ = true;
		}
		break;
	case behavior::retreating_e:
		if (current_state != last_state_)
		{
			chances_of_perfect_aim_ = 70;
			firing_angle_modifier_ = 10;
			rate_of_fire_modifier_ = 1.4f;
			if (nb_of_weapons_ > 4)
			{
				nb_of_currently_active_weapons_ = nb_of_weapons_ - 2;
			}
			is_firing_ = true;
		}
		break;
	case behavior::idle_e:
		break; // No instructions currently for this state.
	case behavior::roaming_e:
		break; // No instructions currently for this state.
	}
	experience::update(current_state, position, enemy_position);
	last_state_ = current_state;
}

ai::manoeuvre* ai::soldier::get_new_manoeuvre(bool is_fighter)
{
	// TODO: Define this behavior.
	return new manoeuvre;
}

sf::Vector2f ai::soldier::get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position)
{
	target_position.x += rand() % int(firing_angle_modifier_ * 2) - firing_angle_modifier_;
	target_position.y += rand() % int(firing_angle_modifier_ * 2) - firing_angle_modifier_;
	return target_position;
}

void ai::soldier::evaluate_engaging(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::soldier::evaluate_attacking(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::soldier::evaluate_retreating(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}
#pragma endregion 

#pragma region RECRUIT
ai::recruit::recruit(int nb_of_weapons, bool has_hangars) : experience(nb_of_weapons, has_hangars)
{
}

ai::recruit::~recruit()
{
}

void ai::recruit::update(
	behavior::type_state current_state,
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

ai::manoeuvre* ai::recruit::get_new_manoeuvre(bool is_fighter)
{
	// TODO: Define this behavior.
	return new manoeuvre;
}

sf::Vector2f ai::recruit::get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position)
{
	// TODO: Define this behavior.
	return sf::Vector2f();
}

void ai::recruit::evaluate_engaging(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::recruit::evaluate_attacking(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::recruit::evaluate_retreating(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}
#pragma endregion 

#pragma region RUFFIAN
ai::ruffian::ruffian(int nb_of_weapons, bool has_hangars) : experience(nb_of_weapons, has_hangars)
{
}

ai::ruffian::~ruffian()
{
}

void ai::ruffian::update(
	behavior::type_state current_state,
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

ai::manoeuvre* ai::ruffian::get_new_manoeuvre(bool is_fighter)
{
	// TODO: Define this behavior.
	return new manoeuvre;
}

sf::Vector2f ai::ruffian::get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position)
{
	// TODO: Define this behavior.
	return sf::Vector2f();
}

void ai::ruffian::evaluate_engaging(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::ruffian::evaluate_attacking(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}

void ai::ruffian::evaluate_retreating(
	sf::Vector2f position,
	sf::Vector2f enemy_position)
{
}
#pragma endregion 
