#include "scene_menu_end_screen.h"
#include "g_vars.hpp"
#include "input_manager.h"

scene_menu_end_screen::scene_menu_end_screen(RenderWindow& main_win): scene_menu(main_win)
{
	score_total_ = 0;

	title_ = text(
		"GAME OVER",
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 - 60),
		text::title,
		text::center);

	score_ = text(
		"score: " + std::to_string(0),
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2),
		text::normal,
		text::center);

	button_ = button(
		"press enter to return to the main menu",
		Vector2f(g_vars::view_width / 2, g_vars::view_height / 2 + 40),
		text::normal,
		text::center);
	button_.set_is_highlighted();
}

void scene_menu_end_screen::draw(RenderWindow& main_win)
{
	title_.draw(main_win);
	score_.draw(main_win);
	button_.draw(main_win);
}

scene_factory::type_scene scene_menu_end_screen::update(float delta_t)
{
	if (input_manager::get_input_manager()->get_button_is_pressed(input_manager::a) && !input_manager::get_input_manager()->get_button_locked(input_manager::a))
	{
		input_manager::get_input_manager()->set_button_locked(input_manager::a);
		return scene_factory::main_menu_e;
	}
	return scene_factory::end_screen_e;
}

void scene_menu_end_screen::set_points(int points)
{
	score_total_ = points;
	score_.set_string("score: " + std::to_string(points));
}
