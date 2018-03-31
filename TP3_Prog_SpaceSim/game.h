#ifndef GAME_H
#define GAME_H

#include "scene.h"

using namespace sf;

class game
{
public:
	game();
	~game();
	int run();

private:
	bool init();
	void change_scene();

	RenderWindow main_win_;
	Event event_;
	scene* active_scene_;
	scene_factory::type_scene returned_scene_;
	scene_factory::type_scene current_scene_;
};
#endif