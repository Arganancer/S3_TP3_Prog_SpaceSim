#include "star.h"
#include "g_vars.hpp"

const int star::out_of_range_distance_(200);
Vector2f star::trajectory_vector_(0, 0);
Vector2f star::view_pos_(0, 0);

star::star(Vector2f position, float mass):
	movable(position, mass)
{
	star_factor_ = 1;
	const auto chance = rand() % 100;
	if (chance < 2)
		star_factor_ = 3;
	else if (chance < 12)
		star_factor_ = 2;

	star_shape_.setRadius(star_factor_ * 0.7f);
	star_shape_.setOrigin(star_factor_ * 0.5f, star_factor_ * 0.5f);

	// Star colors
	default_alpha_ = 100 + star_factor_ * (rand() % 38);
	current_alpha_ = default_alpha_;
	flicker_is_increasing_ = true;
	flicker_variance_ = 5 + rand() % 16;
	flicker_rate_ = 3 + rand() % 6;

	const auto rg = 140 + rand() % 70;
	const auto b = 210 + rand() % 40;
	star_color_ = Color(rg, rg, b, default_alpha_);
	star_shape_.setFillColor(star_color_);

	star_shape_.setPosition(position);
	/* Star masses are negative to make it cost less operations to
	update them (they move in the opposite direction that the player is moving).*/
	max_velocity_ = -(star_factor_ * (rand() % 100)) * 0.0005f; 
}

void star::update_star_relative_info(Vector2f trajectory, Vector2f view_pos)
{
	trajectory_vector_ = trajectory;
	view_pos_ = view_pos;
}

star::~star()
{
}

void star::update(float delta_t)
{
	if(flicker_is_increasing_){
		current_alpha_ += flicker_rate_;
		if (current_alpha_ > default_alpha_ + flicker_variance_)
			flicker_is_increasing_ = false;
	}
	else{
		current_alpha_ -= flicker_rate_;
		if (current_alpha_ < default_alpha_ - flicker_variance_)
			flicker_is_increasing_ = true;
	}

	// Update alpha color after applying flicker.
	star_color_.a = current_alpha_;
	star_shape_.setFillColor(star_color_);

	set_velocity_and_move(trajectory_vector_ * max_velocity_, delta_t);

	respawn();

	star_shape_.setPosition(position_);
}

void star::draw(RenderWindow& main_win)
{
	main_win.draw(star_shape_);
}

void star::respawn()
{
	if (position_.x < view_pos_.x - g_vars::view_width * 0.5f - out_of_range_distance_)
	{
		const auto relative_left_outer_edge = view_pos_.x - g_vars::view_width * 0.5f - out_of_range_distance_;
		const auto adjustment = position_.x - relative_left_outer_edge;
		position_.x = view_pos_.x + g_vars::view_width * 0.5f + out_of_range_distance_ + adjustment;
	}
	else if (position_.x > view_pos_.x + g_vars::view_width * 0.5f + out_of_range_distance_)
	{
		const auto relative_right_outer_edge = view_pos_.x + g_vars::view_width * 0.5f + out_of_range_distance_;
		const auto adjustment = position_.x - relative_right_outer_edge;
		position_.x = view_pos_.x - g_vars::view_width * 0.5f - out_of_range_distance_ + adjustment;
	}

	if (position_.y < view_pos_.y - g_vars::view_height * 0.5f - out_of_range_distance_)
	{
		const auto relative_top_outer_edge = view_pos_.y - g_vars::view_height * 0.5f - out_of_range_distance_;
		const auto adjustment = position_.y - relative_top_outer_edge;
		position_.y = view_pos_.y + g_vars::view_height * 0.5f + out_of_range_distance_ + adjustment;
	}
	else if (position_.y > view_pos_.y + g_vars::view_height * 0.5f + out_of_range_distance_)
	{
		const auto relative_bottom_outer_edge = view_pos_.y + g_vars::view_height * 0.5f + out_of_range_distance_;
		const auto adjustment = position_.y - relative_bottom_outer_edge;
		position_.y = view_pos_.y - g_vars::view_height * 0.5f - out_of_range_distance_ + adjustment;
	}
}