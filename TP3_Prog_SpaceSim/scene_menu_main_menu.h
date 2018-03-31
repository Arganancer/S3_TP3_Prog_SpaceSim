#ifndef SCENE_MENU_MAIN_MENU_H
#define SCENE_MENU_MAIN_MENU_H
#include "scene_menu.h"
#include "button.h"

class scene_menu_main_menu : public scene_menu
{
public:
	explicit scene_menu_main_menu(RenderWindow& main_win);
	~scene_menu_main_menu();
	void draw(RenderWindow& main_win) override;
	scene_factory::type_scene update(float delta_t) override;

private:
	text title_;
	button* buttons_;
	const int nb_buttons_;
	int current_active_button_;
};
#endif