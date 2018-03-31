#include "scene_factory.h"
#include "scene_menu_main_menu.h"
#include "scene_game.h"
#include "scene_menu_end_screen.h"

scene* scene_factory::create_scene(type_scene type, RenderWindow& main_win)
{
	switch (type)
	{
	case main_menu_e: return new scene_menu_main_menu(main_win);
	case play_e: return new scene_game(main_win);
	case end_screen_e: return new scene_menu_end_screen(main_win);
	default:;
	}
	return nullptr;
}
