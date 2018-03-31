#include "game.h"
#include "scene_factory.h"
#include "g_vars.hpp"
#include "text.h"
#include "input_manager.h"
#include "ship_hangar.h"
#include "hull.h"
#include "cockpit.h"
#include "thruster.h"
#include "shield_generator.h"
#include "laser_weapon.h"
#include "scene_game.h"
#include "scene_menu_end_screen.h"

game::game(): active_scene_(nullptr), returned_scene_(), current_scene_()
{
	main_win_.create(VideoMode(g_vars::view_width, g_vars::view_height, 32), "Space Simulation", Style::Fullscreen);
	main_win_.setVerticalSyncEnabled(true);
}

game::~game()
{
	if (active_scene_)
	{
		delete active_scene_;
	}
	input_manager::release();
}

int game::run()
{
	if (!init())
	{
		return EXIT_FAILURE;
	}

	Clock clock;
	float delta_t = 0;
	while (main_win_.isOpen())
	{
		delta_t = std::min(clock.restart().asSeconds(), 0.025f);
		active_scene_->get_inputs(main_win_);
		returned_scene_ = active_scene_->update(delta_t);

		main_win_.clear();
		active_scene_->draw(main_win_);
		main_win_.display();

		change_scene();
	}

	return EXIT_SUCCESS;
}

bool game::init()
{
	if(!text::init())
		return false;
	if (!hull::init())
		return false;
	if (!laser_weapon::init())
		return false;
	if (!ship_hangar::init())
		return false;
	if (!cockpit::init())
		return false;
	if (!thruster::init())
		return false;
	if (!shield_generator::init())
		return false;
	current_scene_ = scene_factory::main_menu_e;
	active_scene_ = scene_factory::create_scene(current_scene_, main_win_);
	return true;
}

void game::change_scene()
{
	if (returned_scene_ == scene_factory::exit_e)
	{
		main_win_.close();
	}
	else if (returned_scene_ != current_scene_ && returned_scene_ == scene_factory::end_screen_e)
	{
		int points = 0;
		if (scene_game* temp = dynamic_cast<scene_game*>(active_scene_))
		{
			points = temp->get_points();
		}
		delete active_scene_;
		current_scene_ = returned_scene_;
		active_scene_ = scene_factory::create_scene(current_scene_, main_win_);
		if (scene_menu_end_screen* temp = dynamic_cast<scene_menu_end_screen*>(active_scene_))
		{
			temp->set_points(points);
		}
	}
	else if(returned_scene_ != current_scene_)
	{
		delete active_scene_;
		current_scene_ = returned_scene_;
		active_scene_ = scene_factory::create_scene(current_scene_, main_win_);
	}
}