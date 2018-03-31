#ifndef SHIP_H
#define SHIP_H
#include "collidable.h"
#include "list_t.hpp"
#include "projectile.h"

class hull;

class ship: public collidable
{
public:
	ship(Vector2f position, float mass);
	~ship();

	// MUTATORS
	virtual void update(float delta_t);
	void inflict_damage(int damage_to_hull);
	void dampen_velocity();
	void dampen_angular_velocity();
	void set_is_colliding() const;

	// ACCESSORS
	void draw(RenderWindow& main_win) override;
	FloatRect get_global_bounds() const override;
	vector<Vector2f> get_axes() override;
	vector<ConvexShape> get_shapes() override;
	container_t::list_t<projectile*>& get_projectiles() const;
	
protected:
	Vector2f throttling_direction_;
	Vector2f aiming_target_;
	float desired_weapon_angle_;
	bool is_throttling_;

	faction owner_;

	hull* hull_;

	int hull_max_endurance_;
	int hull_current_endurance_;
	float hull_percentage_strength_;

	// Shield is not implemented.
	int current_shield_max_endurance_;
	int current_shield_actual_endurance_;
	float current_shield_percentage_strength_;
};

#endif
