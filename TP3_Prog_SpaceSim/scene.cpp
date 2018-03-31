#include "scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "input_manager.h"

scene::scene(RenderWindow& main_win)
{
	view_ = main_win.getDefaultView();
}

void scene::get_inputs(RenderWindow& main_win)
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (main_win.pollEvent(event_))
	{
		input_manager::get_input_manager()->update(main_win, event_);
	}
}
