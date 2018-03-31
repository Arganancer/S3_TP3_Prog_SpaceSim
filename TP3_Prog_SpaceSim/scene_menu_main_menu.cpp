#include "scene_menu_main_menu.h"
#include "g_vars.hpp"
#include <complex.h>
#include "input_manager.h"

scene_menu_main_menu::scene_menu_main_menu(RenderWindow& main_win): scene_menu(main_win), nb_buttons_(4), current_active_button_(0)
{
	view_.setCenter(g_vars::view_width / 2, g_vars::view_height / 2);
	main_win.setView(view_);
	buttons_ = new button[nb_buttons_];

	title_ = text(
		"Main Menu", 
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 - 60), 
		text::title, 
		text::center);

	buttons_[0] = button(
		"Play", 
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2), 
		text::normal, 
		text::center);

	buttons_[1] = button(
		"Options", 
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 + 30),
		text::normal, 
		text::center);

	buttons_[2] = button(
		"Scores", 
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 + 60), 
		text::normal, 
		text::center);

	buttons_[3] = button(
		"Exit", 
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 + 90), 
		text::normal, 
		text::center);

	buttons_[current_active_button_].set_is_highlighted();
}

scene_menu_main_menu::~scene_menu_main_menu()
{
	delete[] buttons_;
	buttons_ = nullptr;
}

void scene_menu_main_menu::draw(RenderWindow& main_win)
{
	title_.draw(main_win);
	for (size_t i = 0; i < nb_buttons_; i++)
	{
		buttons_[i].draw(main_win);
	}
}

scene_factory::type_scene scene_menu_main_menu::update(float delta_t)
{
	// Transtion from one menu item to another.
	static auto joystick_still_held = false;
	const auto joystick_threshold = 30;
	auto left_joy_y = input_manager::get_input_manager()->get_left_joystick_pos().y;
	if (abs(left_joy_y) < joystick_threshold)
	{
		left_joy_y = 0;
	}
	if(!joystick_still_held && left_joy_y > joystick_threshold)
	{
		joystick_still_held = true;
		if (current_active_button_ < nb_buttons_ - 1)
		{
			buttons_[current_active_button_].set_is_not_highlighted();
			buttons_[++current_active_button_].set_is_highlighted();
		}
	}
	else if (!joystick_still_held && left_joy_y < -joystick_threshold)
	{
		joystick_still_held = true;
		if (current_active_button_ > 0)
		{
			buttons_[current_active_button_].set_is_not_highlighted();
			buttons_[--current_active_button_].set_is_highlighted();
		}
	}
	else
	{
		if(left_joy_y == 0 && joystick_still_held)
		{
			joystick_still_held = false;
		}
	}

	// Return result from interaction with current active button.
	if(input_manager::get_input_manager()->get_button_is_pressed(input_manager::a) && !input_manager::get_input_manager()->get_button_locked(input_manager::a))
	{
		input_manager::get_input_manager()->set_button_locked(input_manager::a);
		switch (current_active_button_)
		{
		case 0: 
			return scene_factory::play_e;
		case 1: 
			break;
		case 2: 
			break;
		case 3: 
			return scene_factory::exit_e;
		default: break;
		}
	}
	return scene_factory::type_scene::main_menu_e;
}
