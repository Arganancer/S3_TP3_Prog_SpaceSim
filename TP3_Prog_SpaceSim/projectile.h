#ifndef PROJECTILE_H
#define PROJECTILE_H 
#include "collidable.h"

class projectile : public collidable
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	projectile(Vector2f position, float mass, Vector2f direction, float angle);
	~projectile();

	// MUTATORS
	static void set_shape_points(ConvexShape& shape, float size);
	static void set_shape_points(ConvexShape& shape, float width, float height);
	virtual void update(float delta_t);
	void set_owner(faction owner);

	// ACCESSORS
	faction get_owner() const;
	int get_damage() const;
	void draw(RenderWindow& main_win) override;

	FloatRect get_global_bounds() const override;
	vector<Vector2f> get_axes() override;
	vector<ConvexShape> get_shapes() override;
	bool is_emp() const;
protected:
	ConvexShape shape_projectile_;
	faction owner_;
	Vector2f direction_;
	float percentage_time_elapsed_;
	float time_since_created_;
	float max_time_;
	float projectile_scale_;
	int projectile_damage_;
	bool emp = false;
};

#endif 