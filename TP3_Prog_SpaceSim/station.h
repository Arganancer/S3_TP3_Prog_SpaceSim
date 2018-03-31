#ifndef STATION_H
#define STATION_H
#include "npc.h"
#include "ship_hangar.h"

class station : public npc
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	explicit station(const Vector2f& position);
	~station() override;

	// ACCESSORS
	container_t::list_t<npc*>& get_npcs();
	container_t::list_t<fighter*>* get_launched_fighters() const;
	pair<int, int> get_fighter_points_money() const;

	// MUTATORS
	void update(float delta_t) override;

private:
	container_t::list_t<npc*> npcs_to_spawn_;
};

#endif