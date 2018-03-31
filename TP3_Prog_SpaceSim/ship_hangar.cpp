#include "ship_hangar.h"
#include "fighter.h"
#include "text.h"
#include "tools.hpp"

Texture ship_hangar::hangar_texture_;

ship_hangar::ship_hangar(Vector2f default_position, float default_angle, float component_size) :
	component(default_position, default_angle, component_size),
	nearest_enemy_(nullptr),
	max_fighters_(8),
	time_between_spawns_(5.0f),
	time_between_launches_(0.2f),
	time_since_last_spawn_(0.0f),
	time_since_last_launch_(0.0f), 
	points_value_(0), 
	money_value_(0)
{
	layer_ = two;
	component_shape_.setTexture(&hangar_texture_);
}

ship_hangar::~ship_hangar()
{
	for (auto docked_it = docked_fighters_.begin(); docked_it != docked_fighters_.end(); ++docked_it)
		delete *docked_it;
	docked_fighters_.clear();

	for (auto launched_it = launched_fighters_.begin(); launched_it != launched_fighters_.end(); ++launched_it)
		delete *launched_it;
	launched_fighters_.clear();
}

bool ship_hangar::init()
{
	if (!hangar_texture_.loadFromFile("Sprites\\ship_hangar_32x32.png"))
		return false;
	return true;
}

void ship_hangar::update(float delta_t, ship* nearest_enemy)
{
	nearest_enemy_ = nearest_enemy;

	// Update launched fighters
	if (time_since_last_launch_ <= time_between_launches_)
		time_since_last_launch_ += delta_t;

	for (auto launched_it = launched_fighters_.begin(); launched_it != launched_fighters_.end();)
	{
		launched_it->update(delta_t);
		if(launched_it->get_is_docked())
		{
			auto temp_it = launched_it++;
			docked_fighters_.push_back(*temp_it);
			launched_fighters_.erase(temp_it);
		}
		else if (!launched_it->get_is_alive())
		{
			points_value_ += launched_it->get_point_value();
			money_value_ += launched_it->get_money_value();
			auto temp_it = launched_it++;
			delete *temp_it;
			launched_fighters_.erase(temp_it);
		}
		else
		{
			launched_it->set_nearest_enemy_and_ally(nearest_enemy_, nullptr);
			++launched_it;
		}
	}

	// Update time-based actions.
	if (docked_fighters_.size() + launched_fighters_.size() < max_fighters_)
	{
		time_since_last_spawn_ += delta_t;
		if (time_since_last_spawn_ >= time_between_spawns_)
		{
			time_since_last_spawn_ = 0;
			docked_fighters_.push_back(new fighter(this));
		}
	}
	// TODO: If ship hangar dies, visually explode all fighters.
}

void ship_hangar::draw(RenderWindow& main_win)
{
	for (auto fighters_it = launched_fighters_.begin(); fighters_it != launched_fighters_.end(); ++fighters_it)
		fighters_it->draw(main_win);
	component::draw(main_win);
}

void ship_hangar::launch_fighter()
{
	if (docked_fighters_.size() > 0)
	{
		if (time_since_last_launch_ >= time_between_launches_)
		{
			time_since_last_launch_ = 0;
			launched_fighters_.push_front(docked_fighters_.front());
			docked_fighters_.pop_front();
			launched_fighters_.front()->set_nearest_enemy_and_ally(nearest_enemy_, nullptr);

			const auto direction = tools::vec_util::direction(tools::vec_util::angle_r(component_shape_.getRotation()));
			auto it = launched_fighters_.begin();
			it->launch_fighter(direction, component_shape_.getPosition());
		}
	}
}

container_t::list_t<fighter*>* ship_hangar::get_launched_fighters()
{
	return &launched_fighters_;
}

int ship_hangar::get_current_dead_fighter_points() const
{
	return points_value_;
}

int ship_hangar::get_current_dead_fighter_money() const
{
	return money_value_;
}

void ship_hangar::reset_points_money()
{
	points_value_ = money_value_ = 0;
}
