#ifndef WARNING_LEAVING_GAME_AREA_H
#define WARNING_LEAVING_GAME_AREA_H
#include "overlay.h"
#include "text.h"

class warning_leaving_game_area : public overlay
{
public:
	// CONSTRUCTORS/DESTRUCTORS
	warning_leaving_game_area();
	~warning_leaving_game_area() override;

	// MUTATORS
	void update(float delta_t) override;

	// ACCESSORS
	void draw(sf::RenderWindow& main_win) override;

private:
	bool alpha_channel_increasing_;
	text warning_message_;
	text distance_until_termination_;
	text time_until_termination_;
};

#endif