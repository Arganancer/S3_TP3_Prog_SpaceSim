#include "scene_game.h"
#include "g_vars.hpp"
#include "input_manager.h"
#include "warning_leaving_game_area.h"
#include "fighter.h"
#include "tools.hpp"

scene_game::scene_game(RenderWindow& main_win) : 
	scene(main_win),
	p_ship_(Vector2f(g_vars::game_width / 2, g_vars::game_height / 2)),
	active_overlay_(nullptr),
	game_is_paused_(false),
	current_points_(0),
	points_last_frame_(0),
	current_money_(0),
	money_last_frame_(0),
	respawn_delay_(3.0f), 
	current_respawn_time_(0),
	respawn_position_(Vector2f(g_vars::game_width / 2, g_vars::game_height / 2))
{
	active_pickupables_.push_back(new pickupable(Vector2f(g_vars::game_width / 2, g_vars::game_height / 2)));
	current_respawn_price_ = 100;
	respawning_ = false;

	stations_.push_back(new station(Vector2f(g_vars::game_width / 2 + 100, g_vars::game_height / 2)));
	srand(time(nullptr));
	view_.setCenter(g_vars::game_width / 2, g_vars::game_height / 2);
	view_hud_.setSize(g_vars::view_width, g_vars::view_height);
	view_hud_.setCenter(g_vars::view_width / 2, g_vars::view_height / 2);
	main_win.setView(view_);

	ui_ = new user_interface();
	p_ship_.register_observer(ui_);
	this->register_observer(ui_);

	// Star Initialisation;
	Vector2f star_position;
	for (size_t i = 0; i < 1500; i++)
	{
		star_position.x = rand() % (g_vars::view_width + 400) - 200 - g_vars::view_width / 2 + g_vars::game_width / 2;
		star_position.y = rand() % (g_vars::view_height + 400) - 200 - g_vars::view_height / 2 + g_vars::game_width / 2;
		stars_.push_back(star(star_position, 1));
	}
}

scene_game::~scene_game()
{
	for (auto proj_it = active_projectiles_.begin(); proj_it != active_projectiles_.end(); ++proj_it)
	{
		delete *proj_it;
	}
	active_projectiles_.clear();
	for (auto stations_it = stations_.begin(); stations_it != stations_.end(); ++stations_it)
	{
		delete *stations_it;
	}
	stations_.clear();
	for (auto npcs_it = npcs_.begin(); npcs_it != npcs_.end(); ++npcs_it)
	{
		delete *npcs_it;
	}
	npcs_.clear();
	if (active_overlay_)
	{
		delete active_overlay_;
		active_overlay_ = nullptr;
	}
	for (auto pickup_it = active_pickupables_.begin(); pickup_it != active_pickupables_.end(); ++pickup_it)
	{
		delete *pickup_it;
	}
	delete ui_;}

scene_factory::type_scene scene_game::update(float delta_t)
{
	// TODO: Replace with pause menu overlay:
	if (input_manager::get_input_manager()->get_button_is_pressed(input_manager::start))
	{
		return scene_factory::main_menu_e;
	}
	// Spawn new stations:
	if (stations_.size() < 100 && rand() % 400 == 1)
	{
		stations_.push_back(new station(Vector2f(rand() % g_vars::game_width, rand() % g_vars::game_height)));
	}

	// Update entities:
	for (auto proj_it = active_projectiles_.begin(); proj_it != active_projectiles_.end();)
	{
		proj_it->update(delta_t);
		if (!proj_it->get_is_alive())
		{
			auto temp_proj_it = proj_it++;
			delete *temp_proj_it;
			active_projectiles_.erase(temp_proj_it);
		}
		else
		{
			++proj_it;
		}
	}
	p_ship_.update(delta_t);
	if(!p_ship_.get_is_alive() && !respawning_)
	{
		if(current_respawn_price_ > current_money_)
		{
			return scene_factory::end_screen_e;
		}
		respawning_ = true;
		current_money_ -= current_respawn_price_;
		current_respawn_price_ *= 1.5f;
	}
	else if(respawning_)
	{
		current_respawn_time_ += delta_t;
		if(current_respawn_time_ >= respawn_delay_)
		{
			current_respawn_time_ = 0;
			respawning_ = false;
			p_ship_.revive(respawn_position_);
		}
	}

	// Calculate post player respawn assignments logic:
	for (auto npcs_it = npcs_.begin(); npcs_it != npcs_.end(); ++npcs_it)
	{
		npcs_it->set_nearest_enemy_and_ally(&p_ship_, nullptr);
	}
	for (auto stations_it = stations_.begin(); stations_it != stations_.end(); ++stations_it)
	{
		stations_it->set_nearest_enemy_and_ally(&p_ship_, nullptr);
	}

	for (auto stations_it = stations_.begin(); stations_it != stations_.end();)
	{
		stations_it->update(delta_t);
		const pair<int, int> fighters_p_m = stations_it->get_fighter_points_money();
		current_points_ += fighters_p_m.first;
		current_money_ += fighters_p_m.second;
		if (!stations_it->get_is_alive())
		{
			active_pickupables_.push_back(new pickupable(stations_it->get_position()));
			current_points_ += stations_it->get_point_value();
			current_money_ += stations_it->get_money_value();
			auto temp_stations_it = stations_it++;
			delete *temp_stations_it;
			stations_.erase(temp_stations_it);
		}
		else
		{
			++stations_it;
		}
	}
	for (auto npcs_it = npcs_.begin(); npcs_it != npcs_.end(); ++npcs_it)
	{
		npcs_it->update(delta_t);
	}

	hero_leaving_game_area(p_ship_);
	if (active_overlay_)
	{
		active_overlay_->update(delta_t);
	}

	for (auto pick_it = active_pickupables_.begin(); pick_it != active_pickupables_.end();)
	{
		if (!pick_it->get_is_alive())
		{
			auto temp_pick_it = pick_it++;
			delete *temp_pick_it;
			active_pickupables_.erase(temp_pick_it);
		}
		else
		{
			++pick_it;
		}
	}

	// Update stars:
	star::update_star_relative_info(p_ship_.get_velocity(), view_.getCenter());
	for (size_t i = 0; i < stars_.size(); i++)
	{
		stars_[i].update(delta_t);
	}

	// Add projectiles to game, and remove them from the collidable's list:
	active_projectiles_.splice(p_ship_.get_projectiles());
	for (auto stations_it = stations_.begin(); stations_it != stations_.end(); ++stations_it)
	{
		active_projectiles_.splice(stations_it->get_projectiles());
	}

	// Update Collisions between ships:
	for (auto npcs_it = npcs_.begin(); npcs_it != npcs_.end(); ++npcs_it)
	{
		if (broad_phase_detection(*npcs_it, &p_ship_))
		{
			std::tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(*npcs_it, &p_ship_);
			if (std::get<0>(sat_results))
			{
				collision_resolution(*npcs_it, &p_ship_, std::get<1>(sat_results), std::get<2>(sat_results), delta_t);
			}
		}
	}
	for (auto stations_it1 = stations_.begin(); stations_it1 != stations_.end(); ++stations_it1)
	{
		for (auto stations_it2 = stations_it1; stations_it2 != stations_.end(); ++stations_it2)
		{
			if (stations_it2 != stations_it1)
			{
				if (broad_phase_detection(*stations_it1, *stations_it2))
				{
					std::tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(*stations_it1, *stations_it2);
					if (std::get<0>(sat_results))
					{
						collision_resolution(*stations_it1, *stations_it2, std::get<1>(sat_results), std::get<2>(sat_results), delta_t);
					}
				}
			}
		}
		if (broad_phase_detection(*stations_it1, &p_ship_))
		{
			std::tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(*stations_it1, &p_ship_);
			if (std::get<0>(sat_results))
			{
				collision_resolution(*stations_it1, &p_ship_, std::get<1>(sat_results), std::get<2>(sat_results), delta_t);
			}
		}
	}
	//Update pickupables collisions
	for (auto pickup_it = active_pickupables_.begin(); pickup_it != active_pickupables_.end(); ++pickup_it)
	{
		if (broad_phase_detection(*pickup_it, &p_ship_))
		{
			p_ship_.add_bonus_weapon(pickup_it->get_this_bonus_weapon());
			pickup_it->kill_entity();
		}
	}

	// Update projectile collisions:
	for (auto proj_it = active_projectiles_.begin(); active_projectiles_.size() != 0 && proj_it != active_projectiles_.end(); ++proj_it)
	{
		// Check player projectiles
		if (proj_it->get_owner() == projectile::faction::player)
		{
			// Check collision with stations and their fighters
			for (auto stations_it = stations_.begin(); stations_it != stations_.end(); ++stations_it)
			{
				auto launched_fighters = stations_it->get_launched_fighters();
				for (auto launched_it = launched_fighters->begin(); launched_it != launched_fighters->end(); ++launched_it)
				{
					if (broad_phase_detection(*launched_it, *proj_it))
					{
						std::tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(*launched_it, *proj_it);
						if (std::get<0>(sat_results))
						{
							proj_it->kill_entity();
							launched_it->inflict_damage(proj_it->get_damage());
						}
					}
				}
				if (broad_phase_detection(*stations_it, *proj_it))
				{
					std::tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(*stations_it, *proj_it);
					if (std::get<0>(sat_results))
					{
						proj_it->kill_entity();
						stations_it->inflict_damage(proj_it->get_damage());
					}
				}
				launched_fighters->clear();
				delete launched_fighters;
			}
		}
		// Check NPC projectiles
		else
		{
			if (broad_phase_detection(&p_ship_, *proj_it))
			{
				tuple<bool, Vector2f, float> sat_results = sat_movables_colliding(&p_ship_, *proj_it);
				if (std::get<0>(sat_results))
				{
					proj_it->kill_entity();
					p_ship_.inflict_damage(proj_it->get_damage());
				}
			}
		}
	}

	// Update view:
	view_.setCenter(p_ship_.get_position());

	// Update Observers
	if(current_points_ != points_last_frame_ ||
		current_money_ != money_last_frame_)
	{
		points_last_frame_ = current_points_;
		money_last_frame_ = current_money_;
		notify_observers();
	}

	// TODO: Fix return when menu transitions are a thing.
	return scene_factory::play_e;
}

void scene_game::draw(RenderWindow& main_win)
{
	main_win.setView(view_);
	for (size_t i = 0; i < stars_.size(); i++)
	{
		stars_[i].draw(main_win);
	}
	for (auto stations_it = stations_.begin(); stations_it != stations_.end(); ++stations_it)
	{
		stations_it->draw(main_win);
	}
	for (auto npcs_it = npcs_.begin(); npcs_it != npcs_.end(); ++npcs_it)
	{
		npcs_it->draw(main_win);
	}
	p_ship_.draw(main_win);
	for (auto proj_it = active_projectiles_.begin(); proj_it != active_projectiles_.end(); ++proj_it)
	{
		proj_it->draw(main_win);
	}
	for (auto pickup_it = active_pickupables_.begin(); pickup_it != active_pickupables_.end(); ++pickup_it) //Added pickupables
	{
		pickup_it->draw(main_win);
	}
	main_win.setView(view_hud_);
	if (active_overlay_)
	{
		active_overlay_->draw(main_win);
	}
	ui_->draw(main_win);
}

void scene_game::hero_leaving_game_area(player_ship& player_ship)
{
	if (player_ship.get_position().x < 0 || player_ship.get_position().x > g_vars::game_width ||
		player_ship.get_position().y < 0 || player_ship.get_position().y > g_vars::game_height)
	{
		if (!active_overlay_)
		{
			active_overlay_ = new warning_leaving_game_area();
		}
	}
	else if (active_overlay_)
	{
		delete active_overlay_;
		active_overlay_ = nullptr;
	}
}

#pragma region COLLISION DETECTION AND RESOLUTION

bool scene_game::broad_phase_detection(collidable* entity1, collidable* entity2)
{
	// QUAD TREE FOR BROAD PHASE (check it out).
	if (entity1->intersects(*entity2))
	{
		return true;
	}
	return false;
}

std::tuple<bool, Vector2f, float> scene_game::sat_movables_colliding(collidable* collidable1, collidable* collidable2) const
{
	// SAT = Separating Axis Theorem.
	// This algorithm was heavily inspired by this article: http://www.dyn4j.org/2010/01/sat/

	auto overlap = FLT_MAX; // Maximum float value.
	Vector2f minimum_translation_vector(0, 0);
	auto movables_are_colliding = false;
	auto shapes_are_colliding = true;

	// Get the axes of each shape.
	auto axes = collidable1->get_axes();
	auto axes_temp = collidable2->get_axes();
	axes.insert(axes.end(), axes_temp.begin(), axes_temp.end());

	// Get the shapes of each collidable
	const auto shapes_collidable1 = collidable1->get_shapes();
	const auto shapes_collidable2 = collidable2->get_shapes();

	// Loop over the axes
	for (auto it1 = shapes_collidable1.begin(); it1 != shapes_collidable1.end(); ++it1)
	{
		for (auto it2 = shapes_collidable2.begin(); it2 != shapes_collidable2.end(); ++it2)
		{
			for (size_t i = 0; i < axes.size(); i++)
			{
				shapes_are_colliding = true;
				// Project each shape onto the current axis.
				const auto proj1 = get_shape_projection_on_axis(*it1, axes[i]);
				const auto proj2 = get_shape_projection_on_axis(*it2, axes[i]);

				/* If even once the projections don't overlap,
				the shapes are not colliding, and the verification exits.*/
				if (!(proj1.y >= proj2.x && proj2.y >= proj1.x))
				{
					shapes_are_colliding = false;
					break;
				}
				const auto overlap_temp = min(proj1.y, proj2.y) - max(proj1.x, proj2.x);
				if (overlap_temp < overlap)
				{
					overlap = overlap_temp;
					minimum_translation_vector = axes[i];
				}
			}
			if (shapes_are_colliding)
			{
				movables_are_colliding = true;
			}
		}
	}
	return make_tuple(movables_are_colliding, minimum_translation_vector, overlap);
}


Vector2f scene_game::get_shape_projection_on_axis(ConvexShape shape, Vector2f axis)
{
	Transform shape_transform = shape.getTransform();
	auto minimum = tools::vec_util::dot(
		axis, shape_transform.transformPoint(
			shape.getPoint(0)));
	auto maximum = minimum;
	for (size_t i = 1; i < shape.getPointCount(); i++)
	{
		const auto projection = tools::vec_util::dot(
			axis, shape_transform.transformPoint(shape.getPoint(i)));
		if (projection < minimum)
			minimum = projection;
		else if (projection > maximum)
			maximum = projection;
	}
	const Vector2f projection(minimum, maximum);
	return projection;
}

void scene_game::collision_resolution(collidable* movable1, collidable* movable2, Vector2f minimum_translation_vector, float overlap, float delta_t)
{
	if (ship* temp = dynamic_cast<ship*>(movable1))
	{
		temp->set_is_colliding();
	}
	if (ship* temp = dynamic_cast<ship*>(movable2))
	{
		temp->set_is_colliding();
	}
	if (true)
	{
		// Impulse resolution heavily inspired by this article: https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331
		const auto relative_velocity = movable1->get_velocity() - movable2->get_velocity();
		const auto velocity_along_normal = relative_velocity.x * minimum_translation_vector.x +
			relative_velocity.y * minimum_translation_vector.y;

		// Coefficient of restitution (bounciness) - A.K.A. Newton's Law of Restitution
		// Velocity after impact = Velocity * CoR (CoR is a percentage).
		const auto e = 0.0f;

		// Calculate impulse scalar:
		auto j = -(2.0f + e) * velocity_along_normal;
		j /= 1 / movable1->get_mass() + 1 / movable2->get_mass();
		const auto impulse = (j * minimum_translation_vector);
		//const auto impulse = (minimum_translation_vector * overlap);

		// Calculate mass distribution
		const auto sum_of_masses = movable1->get_mass() + movable2->get_mass();
		const auto movable1_ratio = movable1->get_mass() / sum_of_masses * 2;
		const auto movable2_ratio = movable2->get_mass() / sum_of_masses * 2;

		// Apply impulse:
		movable1->adjust_position(-minimum_translation_vector * velocity_along_normal / 2.0f * delta_t);
		movable2->adjust_position(minimum_translation_vector * velocity_along_normal / 2.0f * delta_t);

		// Apply Momentum transfer:
		movable1->set_velocity(movable1->get_velocity() + 1 / (movable1->get_mass()) * impulse * movable1_ratio);
		movable1->kill_angular_velocity();
		movable2->set_velocity(movable2->get_velocity() - 1 / (movable2->get_mass()) * impulse * movable2_ratio);
		movable2->kill_angular_velocity();
	}
}
#pragma endregion

#pragma region OBSERVER METHODS
void scene_game::register_observer(user_interface* ui_observer)
{
	ui_observers_.push_back(ui_observer);
}

void scene_game::unregister_observer(user_interface* ui_observer)
{
	for (auto it = ui_observers_.begin(); it != ui_observers_.end(); ++it)
	{
		if (*it == ui_observer)
		{
			ui_observers_.erase(it);
			break;
		}
	}
}

void scene_game::notify_observers()
{
	for (auto it = ui_observers_.begin(); it != ui_observers_.end(); ++it)
	{
		it->update_points_money(current_points_, current_money_, current_respawn_price_);
	}
}

int scene_game::get_points() const
{
	return current_points_;
}
#pragma endregion 
