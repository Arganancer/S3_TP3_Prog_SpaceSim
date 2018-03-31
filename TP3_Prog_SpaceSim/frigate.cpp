#include "frigate.h"

frigate::frigate(const Vector2f& position): npc(position, 50)
{
	max_force_ = 8000.0f;
	// TODO: Replace shape with sprite once it is implemented.
	const float ship_scale = 25;

	view_radius_length_ = 500;
	attack_radius_length_ = 200;
}

frigate::~frigate()
{
}

void frigate::update(float delta_t)
{
	npc::update(delta_t);
}
