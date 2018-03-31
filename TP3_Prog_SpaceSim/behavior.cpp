#include "behavior.h"
#include <cstdlib>
#include <iostream>

#pragma region BEHAVIOR BASE CLASS
ai::behavior::behavior(): hull_tolerance_(0), time_elapsed_in_current_state_(0), time_until_state_switch_(0)
{
}
#pragma endregion 

#pragma region SUICIDAL BEHAVIOR
ai::suicidal::suicidal()
{
	hull_tolerance_ = 0;
}

ai::suicidal::~suicidal()
{
}

ai::behavior::type_state ai::suicidal::update(bool enemy_in_vue, bool enemy_in_attack_range, bool enemy_has_attacked,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally, type_state current_state, 
	float delta_t)
{
	if(current_state != idle_e && current_state != roaming_e)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = 0;
	}
	switch (current_state)
	{
	case idle_e: return evaluate_idle(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case roaming_e: return evaluate_roaming(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case engaging_e: return evaluate_engaging(enemy_in_vue, enemy_in_attack_range, hull_percentage_remaining, ally_in_proximity, state_of_nearest_ally );
	case attacking_e: return evaluate_attacking(enemy_in_attack_range, ally_in_proximity, state_of_nearest_ally, hull_percentage_remaining);
	case retreating_e: return evaluate_retreating(hull_percentage_remaining, enemy_in_vue, ally_in_proximity, state_of_nearest_ally);
	}
	return {};
}

ai::behavior::type_state ai::suicidal::evaluate_idle(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	//std::cout << time_elapsed_in_current_state_ << " : " << time_until_state_switch_ << std::endl;
	time_elapsed_in_current_state_ += delta_t;
	if(enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if(time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 5 + 2);
		return roaming_e;
	}
	return idle_e;
}

ai::behavior::type_state ai::suicidal::evaluate_roaming(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	//std::cout << time_elapsed_in_current_state_ << " : " << time_until_state_switch_ << std::endl;
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 2 + 1);
		return idle_e;
	}
	return roaming_e;
}

ai::behavior::type_state ai::suicidal::evaluate_engaging(bool enemy_in_vue, bool enemy_in_attack_range,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally)
{
	// Suicidal AI will never retreat.
	if(!enemy_in_vue)
	{
		return idle_e;
	}
	if(enemy_in_attack_range)
	{
		return attacking_e;
	}
	return engaging_e;
}

ai::behavior::type_state ai::suicidal::evaluate_attacking(bool enemy_in_attack_range, bool ally_in_proximity,
	type_state state_of_nearest_ally, float hull_percentage_remaining)
{
	// Suicidal AI will never retreat.
	if(!enemy_in_attack_range)
	{
		return engaging_e;
	}
	return attacking_e;
}

ai::behavior::type_state ai::suicidal::evaluate_retreating(float hull_percentage_remaining, bool enemy_in_vue,
	bool ally_in_proximity, type_state state_of_nearest_ally)
{
	// A suicidal AI should never end up in this state.
	return attacking_e;
}
#pragma endregion 

#pragma region AGGRESSIVE BEHAVIOR
ai::aggressive::aggressive()
{
	hull_tolerance_ = 0.2f;
}

ai::aggressive::~aggressive()
{
}

ai::behavior::type_state ai::aggressive::update(bool enemy_in_vue, bool enemy_in_attack_range, bool enemy_has_attacked,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally, type_state current_state, float delta_t)
{
	if (current_state != idle_e && current_state != roaming_e)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = 0;
	}
	switch (current_state)
	{
	case idle_e: return evaluate_idle(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case roaming_e: return evaluate_roaming(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case engaging_e: return evaluate_engaging(enemy_in_vue, enemy_in_attack_range, hull_percentage_remaining, ally_in_proximity, state_of_nearest_ally);
	case attacking_e: return evaluate_attacking(enemy_in_attack_range, ally_in_proximity, state_of_nearest_ally, hull_percentage_remaining);
	case retreating_e: return evaluate_retreating(hull_percentage_remaining, enemy_in_vue, ally_in_proximity, state_of_nearest_ally);
	}
	return {};
}

ai::behavior::type_state ai::aggressive::evaluate_idle(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 5 + 4);
		return roaming_e;
	}
	return idle_e;
}

ai::behavior::type_state ai::aggressive::evaluate_roaming(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 3 + 3);
		return idle_e;
	}
	return roaming_e;
}

ai::behavior::type_state ai::aggressive::evaluate_engaging(bool enemy_in_vue, bool enemy_in_attack_range,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally)
{
	if (!enemy_in_vue)
	{
		return idle_e;
	}
	if(hull_percentage_remaining < hull_tolerance_ && !ally_in_proximity)
	{
		return retreating_e;
	}
	if (enemy_in_attack_range)
	{
		return attacking_e;
	}
	return engaging_e;
}

ai::behavior::type_state ai::aggressive::evaluate_attacking(bool enemy_in_attack_range, bool ally_in_proximity,
	type_state state_of_nearest_ally, float hull_percentage_remaining)
{
	if (!enemy_in_attack_range)
	{
		return engaging_e;
	}
	if (hull_percentage_remaining < hull_tolerance_ && !ally_in_proximity)
	{
		return retreating_e;
	}
	return attacking_e;
}

ai::behavior::type_state ai::aggressive::evaluate_retreating(float hull_percentage_remaining, bool enemy_in_vue,
	bool ally_in_proximity, type_state state_of_nearest_ally)
{
	if(ally_in_proximity || hull_percentage_remaining > hull_tolerance_)
	{
		return engaging_e;
	}
	if(!enemy_in_vue)
	{
		return idle_e;
	}
	return retreating_e;
}
#pragma endregion 

#pragma region BALANCED BEHAVIOR
ai::balanced::balanced()
{
	hull_tolerance_ = 0.5f;
}

ai::balanced::~balanced()
{
}

ai::behavior::type_state ai::balanced::update(bool enemy_in_vue, bool enemy_in_attack_range, bool enemy_has_attacked,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally, type_state current_state, float delta_t)
{
	if (current_state != idle_e && current_state != roaming_e)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = 0;
	}
	switch (current_state)
	{
	case idle_e: return evaluate_idle(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case roaming_e: return evaluate_roaming(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case engaging_e: return evaluate_engaging(enemy_in_vue, enemy_in_attack_range, hull_percentage_remaining, ally_in_proximity, state_of_nearest_ally);
	case attacking_e: return evaluate_attacking(enemy_in_attack_range, ally_in_proximity, state_of_nearest_ally, hull_percentage_remaining);
	case retreating_e: return evaluate_retreating(hull_percentage_remaining, enemy_in_vue, ally_in_proximity, state_of_nearest_ally);
	}
	return {};
}

ai::behavior::type_state ai::balanced::evaluate_idle(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 8 + 2);
		return roaming_e;
	}
	return idle_e;
}

ai::behavior::type_state ai::balanced::evaluate_roaming(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_vue || enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 6 + 4);
		return idle_e;
	}
	return roaming_e;
}

ai::behavior::type_state ai::balanced::evaluate_engaging(bool enemy_in_vue, bool enemy_in_attack_range,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally)
{
	if (!enemy_in_vue)
	{
		return idle_e;
	}
	if (hull_percentage_remaining < hull_tolerance_ && !ally_in_proximity && state_of_nearest_ally == retreating_e)
	{
		return retreating_e;
	}
	if (enemy_in_attack_range)
	{
		return attacking_e;
	}
	return engaging_e;
}

ai::behavior::type_state ai::balanced::evaluate_attacking(bool enemy_in_attack_range, bool ally_in_proximity,
	type_state state_of_nearest_ally, float hull_percentage_remaining)
{
	if (!enemy_in_attack_range)
	{
		return engaging_e;
	}
	if (hull_percentage_remaining < hull_tolerance_ && !ally_in_proximity && state_of_nearest_ally == retreating_e)
	{
		return retreating_e;
	}
	return attacking_e;
}

ai::behavior::type_state ai::balanced::evaluate_retreating(float hull_percentage_remaining, bool enemy_in_vue,
	bool ally_in_proximity, type_state state_of_nearest_ally)
{
	if ((ally_in_proximity && state_of_nearest_ally != retreating_e) || (hull_percentage_remaining > hull_tolerance_))
	{
		return engaging_e;
	}
	if (!enemy_in_vue)
	{
		return idle_e;
	}
	return retreating_e;
}
#pragma endregion 

#pragma region COWARD BEHAVIOR
ai::coward::coward()
{
	hull_tolerance_ = 0.8f;
}

ai::coward::~coward()
{
}

ai::behavior::type_state ai::coward::update(bool enemy_in_vue, bool enemy_in_attack_range, bool enemy_has_attacked,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally, type_state current_state, float delta_t)
{
	if (current_state != idle_e && current_state != roaming_e)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = 0;
	}
	switch (current_state)
	{
	case idle_e: return evaluate_idle(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case roaming_e: return evaluate_roaming(enemy_in_vue, enemy_in_attack_range, enemy_has_attacked, delta_t);
	case engaging_e: return evaluate_engaging(enemy_in_vue, enemy_in_attack_range, hull_percentage_remaining, ally_in_proximity, state_of_nearest_ally);
	case attacking_e: return evaluate_attacking(enemy_in_attack_range, ally_in_proximity, state_of_nearest_ally, hull_percentage_remaining);
	case retreating_e: return evaluate_retreating(hull_percentage_remaining, enemy_in_vue, ally_in_proximity, state_of_nearest_ally);
	}
	return {};
}

ai::behavior::type_state ai::coward::evaluate_idle(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 4 + 2);
		return roaming_e;
	}
	return idle_e;
}

ai::behavior::type_state ai::coward::evaluate_roaming(bool enemy_in_vue, bool enemy_in_attack_range,
	bool enemy_has_attacked, float delta_t)
{
	time_elapsed_in_current_state_ += delta_t;
	if (enemy_in_attack_range || enemy_has_attacked)
	{
		return engaging_e;
	}
	if (time_elapsed_in_current_state_ >= time_until_state_switch_)
	{
		time_elapsed_in_current_state_ = 0;
		time_until_state_switch_ = (rand() % 10 + 3);
		return idle_e;
	}
	return roaming_e;
}

ai::behavior::type_state ai::coward::evaluate_engaging(bool enemy_in_vue, bool enemy_in_attack_range,
	float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally)
{
	if (!enemy_in_vue)
	{
		return idle_e;
	}
	if (hull_percentage_remaining < hull_tolerance_ && !ally_in_proximity && state_of_nearest_ally == retreating_e)
	{
		return retreating_e;
	}
	if (enemy_in_attack_range)
	{
		return attacking_e;
	}
	return engaging_e;
}

ai::behavior::type_state ai::coward::evaluate_attacking(bool enemy_in_attack_range, bool ally_in_proximity,
	type_state state_of_nearest_ally, float hull_percentage_remaining)
{
	if (!enemy_in_attack_range)
	{
		return engaging_e;
	}
	// Coward AI will retreat irregardless of other conditions if his hull strength falls too low.
	if (hull_percentage_remaining < 0.4f)
	{
		return retreating_e;
	}
	if (hull_percentage_remaining < hull_tolerance_ && (!ally_in_proximity && state_of_nearest_ally == retreating_e))
	{
		return retreating_e;
	}
	return attacking_e;
}

ai::behavior::type_state ai::coward::evaluate_retreating(float hull_percentage_remaining, bool enemy_in_vue,
	bool ally_in_proximity, type_state state_of_nearest_ally)
{
	// Coward AI will retreat irregardless of other conditions if his hull strength falls too low.
	if (hull_percentage_remaining < 0.4f)
	{
		return retreating_e;
	}
	if ((ally_in_proximity && state_of_nearest_ally != retreating_e) || (hull_percentage_remaining > hull_tolerance_))
	{
		return engaging_e;
	}
	if (!enemy_in_vue)
	{
		return idle_e;
	}
	return retreating_e;
}
#pragma endregion 