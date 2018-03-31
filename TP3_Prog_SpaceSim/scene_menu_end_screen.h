#ifndef SCENE_MENU_END_SCREEN_H
#define SCENE_MENU_END_SCREEN_H
#include "scene_menu.h"
#include "button.h"

class scene_menu_end_screen : public scene_menu
{
public:
	explicit scene_menu_end_screen(RenderWindow& main_win);
	void draw(RenderWindow& main_win) override;
	scene_factory::type_scene update(float delta_t) override;
	void set_points(int points);

private:
	text title_;
	text score_;
	button button_;

	int score_total_;
};
#endif