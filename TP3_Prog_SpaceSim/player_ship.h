#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H
#include "ship.h"
#include "type_weapon.h"

class user_interface;

class player_ship: public ship
{
public:
	explicit player_ship(Vector2f position);
	~player_ship();
	void update(float delta_t) override;
	void revive(Vector2f position);

	void register_observer(user_interface* ui_observer);
	void unregister_observer(user_interface* ui_observer);
	void notify_observers();

	void add_bonus_weapon(type_weapon weapon) const;
private:
	int player_id_;

	container_t::list_t<user_interface*> ui_observers_;

	Vector2f position_last_update_;
	float health_percentage_last_update_;
	float shield_percentage_last_update_;
};

#endif