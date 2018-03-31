#include "weapon_factory.h"
#include "laser_weapon.h"
#include "plasma_weapon.h"
#include "gatling_gun.h"
#include "mine_launcher_weapon.h"
#include "nuke_launcher.h"
#include "missile_launcher.h"

weapon* weapon_factory::create_weapon(type_weapon weapontype, Vector2f position)
{
	switch (weapontype)
	{
		/*case type_weapon::railgun_e
		case type_weapon::harpoon_launcher_e
		case type_weapon::laser_scythe_e*/

		case type_weapon::nuke_launcher_e: return new nuke_launcher(position, 64);
		case type_weapon::missile_launcher_e: return new missile_launcher(position, 32);
		case type_weapon::suicide_drone_launcher_e: return new mine_launcher_weapon(position, 16);
		case type_weapon::laser_weapon_e: return new laser_weapon(position, 16);
		case type_weapon::plasma_weapon_e: return new plasma_weapon(position, 16);
		case type_weapon::gatling_gun_e: return new gatling_gun(position, 16);
		default:;
	}
	return nullptr;
}
 