#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H
#include "type_weapon.h"
#include "weapon.h"

class weapon_factory
{
public:
	static weapon* create_weapon(type_weapon weapontype, Vector2f position);
private:
	weapon_factory() = delete;
};

#endif
