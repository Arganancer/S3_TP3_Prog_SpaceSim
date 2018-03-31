#include "text.h"

sf::Font text::font_bungee_;
sf::Font text::font_consolas_bold_;
sf::Font text::font_consolas_;

bool text::init()
{
	if (!font_bungee_.loadFromFile("Fonts\\Bungee-Regular.ttf"))
	{
		return false;
	}
	if (!font_consolas_bold_.loadFromFile("Fonts\\consolab.ttf"))
	{
		return false;
	}
	if (!font_consolas_.loadFromFile("Fonts\\consola.ttf"))
	{
		return false;
	}
	return true;
}

text::text()
{
	
}

text::text(std::string text, sf::Vector2f position, style_text style, alignment alignment, int font_size)
{
	font_size_ = font_size;
	alignment_ = alignment;
	text_ = sf::Text();
	text_.setString(text);
	text_.setPosition(position);
	set_text_style(style);
	update_alignment(alignment_);
}

void text::update()
{
	update_alignment(alignment_);
}

void text::set_font_size(int size)
{
	text_.setCharacterSize(size);
}

void text::draw(sf::RenderWindow& main_win) const
{
	main_win.draw(text_);
}

void text::set_text_style(style_text style)
{
	switch (style)
	{
	case title:
		text_.setFont(font_bungee_);
		color_ = sf::Color(110, 178, 0);
		color_highlight_ = sf::Color(157, 255, 0);
		char_size_ = 26;
		break;
	case normal_plus:
		text_.setFont(font_bungee_);
		color_ = sf::Color(49, 155, 0);
		color_highlight_ = sf::Color(111, 239, 52);
		char_size_ = 22;
		break;
	case normal:
		text_.setFont(font_consolas_);
		color_ = sf::Color(49, 155, 0);
		color_highlight_ = sf::Color(111, 239, 52);
		char_size_ = 20;
		break;
	case placeholder:
		text_.setFont(font_consolas_);
		color_ = sf::Color(25, 90, 0);
		color_highlight_ = sf::Color(25, 90, 0);
		char_size_ = 20;
		break;
	case warning_title:
		text_.setFont(font_bungee_);
		color_ = sf::Color(214, 92, 0);
		color_highlight_ = sf::Color(255, 172, 109);
		char_size_ = 26;
		break;
	case warning:
		text_.setFont(font_consolas_bold_);
		color_ = sf::Color(214, 92, 0);
		color_highlight_ = sf::Color(255, 172, 109);
		char_size_ = 20;
		break;
	}
	if(font_size_ != 0)
	{
		char_size_ = font_size_;
	}
	text_.setCharacterSize(char_size_);
	text_.setFillColor(color_);
}


void text::update_alignment(enum alignment alignment)
{
	if(alignment != alignment_)
	{
		alignment_ = alignment;
	}
	switch (alignment)
	{
	case left:
		text_.setOrigin(0, 0);
		break;
	case center:
		text_.setOrigin(get_text_size() / 2, 0);
		break;
	case right:
		text_.setOrigin(get_text_size(), 0);
		break;
	default:;
	}
}

void text::set_string(std::string text)
{
	text_.setString(text);
}

sf::String text::get_text_string() const
{
	return text_.getString();
}


int text::get_text_size() const
{
	return text_.getGlobalBounds().width;
}

void text::set_position(sf::Vector2f new_position)
{
	text_.setPosition(new_position);
}