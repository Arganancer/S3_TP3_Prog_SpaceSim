#include "button.h"

button::button()
{
}

button::button(std::string text, sf::Vector2f position, style_text style, alignment alignment) : text(text, position, style, alignment)
{
}

void button::set_is_highlighted()
{
	text_.setFillColor(color_highlight_);
}

void button::set_is_not_highlighted()
{
	text_.setFillColor(color_);
}
