#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H
#include <SFML/Graphics/RenderWindow.hpp>

class scene;

class scene_factory
{
public:
	enum type_scene
	{
		exit_e,
		main_menu_e,
		play_e,
		end_screen_e,
	};

	static scene* create_scene(type_scene type, sf::RenderWindow& main_win);
private:
	scene_factory() = delete;
};
#endif
