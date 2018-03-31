#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include "scene_factory.h"

using namespace sf;

class scene
{
public:
	explicit scene(RenderWindow& main_win);
	virtual ~scene() = default;
	void get_inputs(RenderWindow& main_win);
	virtual scene_factory::type_scene update(float delta_t) = 0;
	virtual void draw(RenderWindow& main_win) = 0;

protected:
	View view_;
	Event event_;
};
#endif