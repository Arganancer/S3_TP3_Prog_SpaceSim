#ifndef STAR_H
#define STAR_H
#include "movable.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class star: public movable
{
public:
	star(Vector2f position, float mass);
	~star();
	void update(float delta_t);
	static void update_star_relative_info(Vector2f trajectory, Vector2f view_pos);
	void draw(RenderWindow& main_win) override;

private:
	static const int out_of_range_distance_;
	static Vector2f view_pos_;
	static Vector2f trajectory_vector_;
	
	CircleShape star_shape_;
	Color star_color_;
	int default_alpha_;
	int current_alpha_;
	int flicker_variance_;
	bool flicker_is_increasing_;
	int flicker_rate_;

	int star_factor_;

	void respawn();
};

#endif