#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include "text.h"

class button : public text
{
public:
	button();
	button(std::string text, sf::Vector2f position, style_text style, alignment alignment);
	void set_is_highlighted();
	void set_is_not_highlighted();
};

#endif