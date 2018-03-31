#include "ship.h"
#include "tools.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "hull.h"

ship::ship(Vector2f position, float mass) :
	collidable(position, mass),
	desired_weapon_angle_(0),
	is_throttling_(false),
	owner_(npc),
	hull_max_endurance_(0),
	hull_current_endurance_(0),
	hull_percentage_strength_(1), 
	current_shield_max_endurance_(0), 
	current_shield_actual_endurance_(0),
	current_shield_percentage_strength_(0)
{
}


void ship::set_is_colliding() const
{
	hull_->set_is_colliding();
}

ship::~ship()
{
	delete hull_;
}

void ship::update(float delta_t)
{
	if(hull_current_endurance_ <= 0)
		kill_entity();

	// ROTATION
	// Ships have integrated smart rotational inertia dampeners that reduce torque as 
	// the ship's rotation approaches its target rotation.
	const auto desired_angle = tools::vec_util::angle_d(throttling_direction_);
	auto difference_between_both_angles = desired_angle - rotation_angle_;
	difference_between_both_angles +=
		(difference_between_both_angles > 180) ? -360 :
		(difference_between_both_angles < -180) ? 360 : 0;

	if (fabs(difference_between_both_angles) > 1)
	{
		const auto adjusted_torque = 0.038f + 0.0054f * fabs(difference_between_both_angles);

		if (difference_between_both_angles > 0)
			torque_ = max_torque_ * adjusted_torque;
		else
			torque_ = -max_torque_ * adjusted_torque;

		set_current_max_angular_velocity(adjusted_torque);
	}
	else { torque_ = 0; }

	if (!is_throttling_)
	{
		dampen_velocity();
	}

	calculate_velocity(delta_t);
	rotate(delta_t);

	hull_->update(position_, rotation_angle_);

	// TODO: Figure out where to include weapons.
	//for (auto weap_it = active_weapons_.begin(); weap_it != active_weapons_.end(); ++weap_it)
	//{
	//	weap_it->update(delta_t);
	//	weap_it->set_transform(entity_shapes_.front()->getTransform());
	//	weap_it->set_desired_direction(aiming_target_, desired_weapon_angle_);
	//}
}

void ship::dampen_velocity()
{
	// Dampen Force.
	if(fabs(tools::vec_util::magnitude(velocity_)) > 3)
	{
		const auto current_direction = tools::vec_util::direction(velocity_);
		force_ = -current_direction * max_force_;
	}
	else
	{
		force_ = Vector2f(0, 0);
		velocity_ = Vector2f(0, 0);
	}
}

void ship::dampen_angular_velocity()
{
	// Dampen torque.
	if (angular_velocity_ > max_torque_)
		torque_ = -max_torque_;
	else if (angular_velocity_ < -max_torque_)
		torque_ = max_torque_;
	else {
		torque_ = 0;
		angular_velocity_ = 0;
	}
}

void ship::inflict_damage(int damage_to_hull)
{
	hull_current_endurance_ -= damage_to_hull;
	hull_percentage_strength_ = float(hull_current_endurance_) / float(hull_max_endurance_);
}

void ship::draw(RenderWindow& main_win)
{
//#pragma region DEBUG CODE
//	auto health = RectangleShape(Vector2f(40, 5));
//	health.setFillColor(Color::Red);
//	health.setPosition(position_.x - 20, position_.y + 80);
//	main_win.draw(health);
//	health.setSize(Vector2f(40 * hull_percentage_strength_, 5));
//	health.setFillColor(Color::Green);
//	main_win.draw(health);
//#pragma endregion
	hull_->draw(main_win);
}

vector<Vector2f> ship::get_axes()
{
	// Get the normals (right angles) of each shape's edges:
	return hull_->get_axes();
}

vector<ConvexShape> ship::get_shapes()
{
	return hull_->get_shapes();
}

FloatRect ship::get_global_bounds() const
{
	return hull_->get_global_bounds();
}

container_t::list_t<projectile*>& ship::get_projectiles() const
{
	return hull_->get_projectiles();
}
