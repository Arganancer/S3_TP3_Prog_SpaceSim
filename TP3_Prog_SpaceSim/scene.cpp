#include "scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "input_manager.h"

scene::scene(RenderWindow& main_win)
{
	view_ = main_win.getDefaultView();
}

void scene::get_inputs(RenderWindow& main_win)
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (main_win.pollEvent(event_))
	{
		input_manager::get_input_manager()->update(main_win, event_);
	}
}
