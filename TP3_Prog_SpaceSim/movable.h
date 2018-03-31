#ifndef MOVABLE_H
#define MOVABLE_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "stdlib.h"

using namespace sf;
using namespace std;

class movable
{
public:
	enum faction
	{
		player,
		npc,
	};
	// Constructors/Destructors
	explicit movable(Vector2f position, float mass);
	virtual ~movable();

	// Accessors
	Vector2f get_velocity() const;
	float get_mass() const;
	Vector2f get_position() const;
	bool get_is_alive() const;
	virtual void draw(RenderWindow& main_win) = 0;

	// Mutators
	void set_velocity(Vector2f velocity);
	void kill_angular_velocity();
	void set_position(Vector2f position);
	void adjust_position(Vector2f position);

	void kill_entity();

protected:
	bool is_alive_;

	/* POSITION: the center of the object. It is used for the following:
	1) If collidable is a movable, its position is also its "center of mass".
	Although unrealistic, this simplifies a lot of calculations.
	2) The collidable's shapes will be drawn according to this position relative
	To their origin.*/
	Vector2f position_;

	void calculate_velocity(float delta_t);
	void set_velocity_and_move(Vector2f velocity, float delta_t);
	void rotate(float delta_t);


// PHYSICS VARIABLES :
	// TRANSLATION (F = ma)
		// Translation (movement) in this project uses a simplified version of the Verlet Integration:
		// https://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
		// Inspired by: http://buildnewgames.com/gamephysics/

		// MASS
		float mass_;

		// FORCE:
		Vector2f force_;
		float max_force_;

		// LAST_ACCELERATION
		// Last_acceleration = avg_acceleration_.
		Vector2f last_acceleration_;

		// Position (declared in collidable.h):
		// Position += velocity * delta_t + (0.5 * last_acceleration * delta_t^2)

		// NEW_ACCELERATION
		// new_acceleration_ = Force / Mass
		Vector2f new_acceleration_;

		// AVG_ACCELERATION
		// avg_acceleration = (last_acceleration + new_acceleration) /2
		Vector2f avg_acceleration_;

		// VELOCITY
		// Rate of change over time.
		// Velocity += avg_acceleration * delta_t
		Vector2f velocity_;

		// MAX_VELOCITY
		// Velocity in both x and y cannot be greater than this value.
		float max_velocity_;
		float default_max_velocity_;
		void set_current_max_velocity(float percentage);

	// ROTATION (T = Ja)
		// ANGULAR_MASS
		// Quality of the movable that resists angular acceleration.
		float angular_mass_;

		// ROTATION ANGLE
		// theta (θ)
		// Measured in degrees
		float rotation_angle_; 

		// ANGULAR_VELOCITY
		// omega (ω)
		// Measured in degrees/second
		float angular_velocity_;

		// ANGULAR_ACCELERATION
		// alpha (α)
		// Measured in degrees/second²
		float angular_acceleration_; 

		// TORQUE
		// Torque can be calculated by figuring out how far a force is applied 
		// from the center of rotation of an object–but we also have to only look at 
		// the component of the force that pushes at a 90 degree angle to the center point of our object.
		float torque_;
		float max_torque_;

		// MAX_ANGULAR_VELOCITY
		float max_angular_velocity_;
		float default_max_angular_velocity_;
		void set_current_max_angular_velocity(float percentage);
};

#endif