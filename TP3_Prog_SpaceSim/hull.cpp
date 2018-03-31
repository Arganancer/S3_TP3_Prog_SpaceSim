#include "hull.h"
#include "tools.hpp"
#include "ship_hangar.h"
#include "weapon.h"
#include "weapon_factory.h"
#include "cockpit.h"
#include "thruster.h"
#include "shield_generator.h"

Texture hull::hull_textures_[4]{};
Texture hull::fighter_texture_;

hull::hull(Vector2f default_position, float default_angle, float hull_size):
	component(default_position, default_angle, hull_size), 
	nb_of_weapons_(0)
{
	layer_ = three;
	if(hull_size < 24)
		component_shape_.setTexture(&hull_textures_[0]);
	else if(hull_size < 48)
		component_shape_.setTexture(&hull_textures_[1]);
	else if (hull_size < 96)
		component_shape_.setTexture(&hull_textures_[2]);
	else
		component_shape_.setTexture(&hull_textures_[3]);
}


void hull::set_is_fighter()
{
	component_shape_.setTexture(&fighter_texture_);
}

hull::~hull()
{
	for (auto proj_it = projectiles_to_add_to_queue_.begin(); proj_it != projectiles_to_add_to_queue_.end(); ++proj_it)
		delete *proj_it;
	projectiles_to_add_to_queue_.clear();
	for (auto comp_it = components_.begin(); comp_it != components_.end(); ++comp_it)
		delete *comp_it;
	components_.clear();
}

void hull::update(Vector2f position, float rotation_angle)
{
	component_shape_.setFillColor(Color::White);
	component_shape_.setPosition(position);
	component_shape_.setRotation(rotation_angle);
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		it->update(rotation_angle, component_shape_.getTransform());
	}
}

void hull::draw(RenderWindow& main_win)
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
		if (it->layer_ == four)
			it->draw(main_win);
	for (auto it = components_.begin(); it != components_.end(); ++it)
		if (it->layer_ == three)
			it->draw(main_win);
	component::draw(main_win);
	for (auto it = components_.begin(); it != components_.end(); ++it)
		if (it->layer_ == two)
			it->draw(main_win);
	for (auto it = components_.begin(); it != components_.end(); ++it)
		if (it->layer_ == one)
			it->draw(main_win);
}

void hull::add_component(
	Vector2f default_position, 
	float default_angle, 
	type_component component_type,
	float component_size)
{
	components_.push_back(
		component_factory::create_component(
			default_position, 
			default_angle, 
			component_type,
			component_size));
}

void hull::add_weapon(
	Vector2f default_position, 
	type_weapon weapon_type)
{
	components_.push_back(
		weapon_factory::create_weapon(
			weapon_type, 
			default_position));
}

bool hull::init()
{
	if(!hull_textures_[0].loadFromFile("Sprites\\hull_texture_16x16.png"))
		return false;
	if (!hull_textures_[1].loadFromFile("Sprites\\hull_texture_32x32.png"))
		return false;
	if (!hull_textures_[2].loadFromFile("Sprites\\hull_texture_64x64.png"))
		return false;
	if (!hull_textures_[3].loadFromFile("Sprites\\hull_texture_128x128.png"))
		return false;
	if (!fighter_texture_.loadFromFile("Sprites\\fighter_texture_16x16.png"))
		return false;
	return true;
}

FloatRect hull::get_global_bounds()
{
	auto temp_float_rect = component_shape_.getGlobalBounds();
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		temp_float_rect.top = min(
			temp_float_rect.top, 
			static_cast<float>(it->component_shape_.getGlobalBounds().top));
		temp_float_rect.left = min(
			temp_float_rect.left, 
			static_cast<float>(it->component_shape_.getGlobalBounds().left));
		temp_float_rect.width = max(
			temp_float_rect.width, 
			static_cast<float>(it->component_shape_.getGlobalBounds().width));
		temp_float_rect.height = max(
			temp_float_rect.height, 
			static_cast<float>(it->component_shape_.getGlobalBounds().height));
	}
	return temp_float_rect;
}

vector<ConvexShape> hull::get_shapes()
{
	std::vector<ConvexShape> shapes;
	shapes.push_back(component_shape_);
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (weapon* temp = dynamic_cast<weapon*>(*it)){}
		else
		{
			shapes.push_back(it->component_shape_);
		}
	}
	return shapes;
}

vector<Vector2f> hull::get_axes()
{
	vector<Vector2f> axes;
	// TODO: Find a better way to manage this
	for (size_t i = 0; i < component_shape_.getPointCount(); i++)
	{
		Transform shape_transform = component_shape_.getTransform();
		const auto point1 = shape_transform.transformPoint(
			component_shape_.getPoint(i));
		const auto point2 = shape_transform.transformPoint(
			component_shape_.getPoint(i + 1 == component_shape_.getPointCount() ? 0 : i + 1));
		const auto edge = point1 - point2;
		/* The normal of an edge can obtained by
		flipping the coordinates and negating one. */
		const auto unit_normal = tools::vec_util::direction_normal(edge);

		/* When evaluating collisions using the SAT method,
		* there is no need to verify axes that are parallel. */
		auto parallel_axis_exists = false;
		for (auto axes_it = axes.begin(); axes_it != axes.end(); ++axes_it)
		{
			if (tools::vec_util::dot(*axes_it, unit_normal))
			{
				parallel_axis_exists = true;
				break;
			}
		}
		// TODO: Fix parallel axis checks (clearly not working).
		//if (!parallel_axis_exists)
		{
			axes.push_back(unit_normal);
		}
	}

	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (weapon* temp = dynamic_cast<weapon*>(*it)) {}
		else
		{
			for (size_t i = 0; i < it->component_shape_.getPointCount(); i++)
			{
				Transform shape_transform = it->component_shape_.getTransform();
				const auto point1 = shape_transform.transformPoint(
					it->component_shape_.getPoint(i));
				const auto point2 = shape_transform.transformPoint(
					it->component_shape_.getPoint(i + 1 == it->component_shape_.getPointCount() ? 0 : i + 1));
				const auto edge = point1 - point2;
				/* The normal of an edge can obtained by
				flipping the coordinates and negating one. */
				const auto unit_normal = tools::vec_util::direction_normal(edge);

				/* When evaluating collisions using the SAT method,
				 * there is no need to verify axes that are parallel. */
				auto parallel_axis_exists = false;
				for (auto axes_it = axes.begin(); axes_it != axes.end(); ++axes_it)
				{
					if (tools::vec_util::dot(*axes_it, unit_normal))
					{
						parallel_axis_exists = true;
						break;
					}
				}
				// TODO: Fix parallel axis checks (clearly not working).
				//if (!parallel_axis_exists)
				{
					axes.push_back(unit_normal);
				}
			}
		}
	}
	return axes;
}


void hull::update_weapons(float delta_t, Vector2f target)
{
	for (auto it = components_.begin(); it != components_.end();)
	{
		if (weapon* temp = dynamic_cast<weapon*>(*it))
		{
			temp->update(delta_t, target);
			if (temp->get_ammo() == 0)
			{
				auto temp2 = it++;
				delete *temp2;
				components_.erase(temp2);
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}
}

void hull::fire_weapons(float delta_t, movable::faction owner, Vector2f target)
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (weapon* temp = dynamic_cast<weapon*>(*it))
		{
			const auto aiming_direction = tools::vec_util::direction(temp->get_position(), target);
			const auto aiming_angle = tools::vec_util::angle_d(aiming_direction);
			auto temp_proj = temp->shoot_projectile(aiming_direction, aiming_angle, delta_t);
			if (temp_proj)
			{
				temp_proj->set_owner(owner);
				projectiles_to_add_to_queue_.push_back(temp_proj);
			}
		}
	}
}

container_t::list_t<projectile*>& hull::get_projectiles()
{
	return projectiles_to_add_to_queue_;
}

container_t::list_t<fighter*>* hull::get_launched_fighters()
{
	const auto all_fighters = new container_t::list_t<fighter*>;
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (ship_hangar* temp = dynamic_cast<ship_hangar*>(*it))
		{
			*all_fighters += *temp->get_launched_fighters();
		}
	}
	return all_fighters;
}

void hull::update_hangars(float delta_t, ship* nearest_enemy, ai::behavior::type_state current_state)
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (ship_hangar* temp = dynamic_cast<ship_hangar*>(*it))
		{
			temp->update(delta_t, nearest_enemy);
			if (current_state == ai::behavior::attacking_e)
			{
				temp->launch_fighter();
			}
		}
	}
}

std::pair<int, int> hull::get_hangar_values()
{
	auto money = 0;
	auto points = 0;
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		if (ship_hangar* temp = dynamic_cast<ship_hangar*>(*it))
		{
			money += temp->get_current_dead_fighter_money();
			points += temp->get_current_dead_fighter_points();
			temp->reset_points_money();
		}
	}
	return make_pair(points, money);
}


void hull::set_is_colliding()
{
	component_shape_.setFillColor(Color::Red);
}

#pragma region COMPONENT FACTORY
component* component_factory::create_component(
	Vector2f default_position,
	float default_angle,
	hull::type_component component_type,
	float component_size)
{
	switch (component_type)
	{
	case hull::thruster_e: 
		return new thruster(default_position, default_angle, component_size);
	case hull::hull_e:
		return new hull(default_position, default_angle, component_size);
	case hull::shield_generator_e:
		return new shield_generator(default_position, default_angle, component_size);
	case hull::cockpit_e: 
		return new cockpit(default_position, default_angle, component_size);
	case hull::hangar_e:
		return new ship_hangar(default_position, default_angle, component_size);
	default:;
	}
	return new hull(default_position, default_angle, component_size);
}
#pragma endregion