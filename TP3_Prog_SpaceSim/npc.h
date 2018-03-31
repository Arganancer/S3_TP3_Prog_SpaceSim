#ifndef NPC_H
#define NPC_H
#include "ship.h"
#include "behavior.h"
#include "experience.h"

class npc : public ship
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	npc(Vector2f position, float mass);
	~npc();

	// ACCESSORS
	ai::behavior::type_state get_current_state() const;
	int get_point_value() const;
	int get_money_value() const;

	// MUTATORS
	void set_nearest_enemy_and_ally(ship* enemy_ship, npc* ally_ship);
	void update(float delta_t) override;
	Vector2f get_throttling_direction(Vector2f desired_direction, Vector2f current_direction) const;

protected:
	void attack(float delta_t);
	void update_ai(float delta_t);

	ai::behavior* behavior_;
	ai::experience* experience_;

	float view_radius_length_;
	float attack_radius_length_;
	ship* nearest_enemy_;
	npc* nearest_ally_;
	Vector2f roaming_direction_;
	Vector2f desired_direction_;
	ai::behavior::type_state current_state_;
	int points_value_;
	int money_value_;
};

#endif