#ifndef FIGHTER_H
#define FIGHTER_H
#include "npc.h"

class ship_hangar;

class fighter : public npc
{
	enum secondary_states
	{
		flying,
		docking,
		docked,
	};

public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	explicit fighter(ship_hangar* home_hangar);
	~fighter() override;

	// ACCESSORS
	bool get_is_docked() const;

	// MUTATORS
	void update(float delta_t) override;
	void launch_fighter(Vector2f direction, Vector2f position);

private:
	ship_hangar* home_hangar_;
	secondary_states current_secondary_state_;
	const float max_flying_time_;
	float flying_time_left_;

	const static float launch_speed_;
};

#endif