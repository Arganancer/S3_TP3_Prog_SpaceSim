#ifndef WEAPON_H
#define WEAPON_H
#include "projectile.h"
#include <SFML/Graphics.hpp>
#include "component.h"

class weapon : public component
{
public:
	// CONSTRUCTORS
	weapon(Vector2f default_position, float default_angle, float weapon_size);
	~weapon();

	// MUTATORS
	virtual projectile* shoot_projectile(Vector2f direction, float angle, float delta_t) = 0;
	void shoot_delay(float delta_t);
	virtual void update(float delta_t, Vector2f target);
	void set_modified_rof(float modifier);
	int get_ammo() const;
	// ACCESSORS

protected:
	float current_angle_;
	float desired_angle_;
	Vector2f current_direction_;
	Vector2f desired_direction_;
	static Texture weapon_texture_;

	bool shot_available_;
	float last_shot_;
	float default_rof_;
	float modified_rof_;
	int ammo;
};

#endif