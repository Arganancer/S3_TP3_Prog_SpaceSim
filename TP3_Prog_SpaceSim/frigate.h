#ifndef FRIGATE_H
#define FRIGATE_H
#include "npc.h"

class frigate : public npc
{
public:
	// CONSTRUCTOR(S) / DESTRUCTOR
	explicit frigate(const Vector2f& position);
	~frigate() override;

	// ACCESSORS

	// MUTATORS
	void update(float delta_t) override;
};

#endif