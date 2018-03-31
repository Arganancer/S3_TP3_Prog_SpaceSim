#include "aoe_projectile.h"
#include "explosion.h"

aoe_projectile::aoe_projectile(const Vector2f& position, float mass, Vector2f direction, float angle) : projectile(position, mass, direction, angle)
{
}

aoe_projectile::~aoe_projectile()
{
}

void aoe_projectile::update(float delta_t)
{
}

void aoe_projectile::explode(Vector2f explosion_position)
{
	//return new explosion(explosion_position);
}
