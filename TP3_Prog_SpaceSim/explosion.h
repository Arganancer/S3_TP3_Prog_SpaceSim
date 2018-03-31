#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <SFML/Graphics.hpp>
#include "projectile.h"

using namespace sf;

class explosion : public projectile
{
public:
	explosion(sf::Vector2f position);
	~explosion();

	void update(float delta_t) override;
	float time_since_created_;
	float max_time_;


	void draw(RenderWindow& main_win) override;
	FloatRect get_global_bounds() const override;
	vector<Vector2f> get_axes() override;
	vector<ConvexShape> get_shapes() override;
	Color explo_color;
};


#endif

