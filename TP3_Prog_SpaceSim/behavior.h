#ifndef BEHAVIOR_H
#define BEHAVIOR_H

namespace ai
{
	// BEHAVIOR BASE CLASS
	/*
	 * Behavior needs to evaluate the following to determine its state:
	 *	- Enemy is present in vue diameter.
	 *		- Distance between enemy and host ship.
	 *		- Enemy has attacked the host ship.
	 *	- Hull endurance remaining.
	 *	- whether or not an ally is in proximity
	 *		- State of the nearest ally.
	 */
	class behavior
	{
	public:
		enum type_state
		{
			idle_e,
			roaming_e,
			engaging_e,
			attacking_e,
			retreating_e,
		};

		behavior();
		virtual ~behavior() = default;

		virtual type_state update(bool enemy_in_view, bool enemy_in_attack_range,
			bool enemy_has_attacked, float hull_percentage_remaining, 
			bool ally_in_proximity, type_state state_of_nearest_ally,
			type_state current_state, float delta_t) = 0;

	protected:
		// One of the following methods will be called in the 
		// update depending on what the current state is.
		virtual type_state evaluate_idle(bool enemy_in_view, 
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) = 0;
		virtual type_state evaluate_roaming(bool enemy_in_vue, 
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) = 0;
		virtual type_state evaluate_engaging(bool enemy_in_vue, 
			bool enemy_in_attack_range, float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally) = 0;
		virtual type_state evaluate_attacking(bool enemy_in_attack_range, 
			bool ally_in_proximity, type_state state_of_nearest_ally, float hull_percentage_remaining) = 0;
		virtual type_state evaluate_retreating(float hull_percentage_remaining, 
			bool enemy_in_vue, bool ally_in_proximity, type_state state_of_nearest_ally) = 0;

		float hull_tolerance_;
		float time_elapsed_in_current_state_;
		float time_until_state_switch_;
	};

	// SUICIDAL
	class suicidal : public behavior
	{
	public:
		suicidal();
		~suicidal();
		type_state update(bool enemy_in_vue, bool enemy_in_attack_range,
			bool enemy_has_attacked, float hull_percentage_remaining,
			bool ally_in_proximity, type_state state_of_nearest_ally,
			type_state current_state, float delta_t) override;
	private:
		type_state evaluate_idle(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_roaming(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_engaging(bool enemy_in_vue,
			bool enemy_in_attack_range, float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally) override;
		type_state evaluate_attacking(bool enemy_in_attack_range,
			bool ally_in_proximity, type_state state_of_nearest_ally, float hull_percentage_remaining) override;
		type_state evaluate_retreating(float hull_percentage_remaining,
			bool enemy_in_vue, bool ally_in_proximity, type_state state_of_nearest_ally) override;
	};

	// AGGRESSIVE
	class aggressive : public behavior
	{
	public:
		aggressive();
		~aggressive();
		type_state update(bool enemy_in_vue, bool enemy_in_attack_range,
			bool enemy_has_attacked, float hull_percentage_remaining,
			bool ally_in_proximity, type_state state_of_nearest_ally,
			type_state current_state, float delta_t) override;
	private:
		type_state evaluate_idle(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_roaming(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_engaging(bool enemy_in_vue,
			bool enemy_in_attack_range, float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally) override;
		type_state evaluate_attacking(bool enemy_in_attack_range,
			bool ally_in_proximity, type_state state_of_nearest_ally, float hull_percentage_remaining) override;
		type_state evaluate_retreating(float hull_percentage_remaining,
			bool enemy_in_vue, bool ally_in_proximity, type_state state_of_nearest_ally) override;
	};

	// BALANCED
	class balanced : public behavior
	{
	public:
		balanced();
		~balanced();
		type_state update(bool enemy_in_vue, bool enemy_in_attack_range,
			bool enemy_has_attacked, float hull_percentage_remaining,
			bool ally_in_proximity, type_state state_of_nearest_ally,
			type_state current_state, float delta_t) override;
	private:
		type_state evaluate_idle(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_roaming(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_engaging(bool enemy_in_vue,
			bool enemy_in_attack_range, float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally) override;
		type_state evaluate_attacking(bool enemy_in_attack_range,
			bool ally_in_proximity, type_state state_of_nearest_ally, float hull_percentage_remaining) override;
		type_state evaluate_retreating(float hull_percentage_remaining,
			bool enemy_in_vue, bool ally_in_proximity, type_state state_of_nearest_ally) override;
	};

	// COWARD
	class coward : public behavior
	{
	public:
		coward();
		~coward();
		type_state update(bool enemy_in_vue, bool enemy_in_attack_range,
			bool enemy_has_attacked, float hull_percentage_remaining,
			bool ally_in_proximity, type_state state_of_nearest_ally,
			type_state current_state, float delta_t) override;
	private:
		type_state evaluate_idle(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_roaming(bool enemy_in_vue,
			bool enemy_in_attack_range, bool enemy_has_attacked, float delta_t) override;
		type_state evaluate_engaging(bool enemy_in_vue,
			bool enemy_in_attack_range, float hull_percentage_remaining, bool ally_in_proximity, type_state state_of_nearest_ally) override;
		type_state evaluate_attacking(bool enemy_in_attack_range,
			bool ally_in_proximity, type_state state_of_nearest_ally, float hull_percentage_remaining) override;
		type_state evaluate_retreating(float hull_percentage_remaining,
			bool enemy_in_vue, bool ally_in_proximity, type_state state_of_nearest_ally) override;
	};

	// BEHAVIOR FACTORY
	class behavior_factory
	{
	public:
		enum type_behavior
		{
			suicidal_e,
			aggressive_e,
			balanced_e,
			coward_e
		};

		static behavior* create_behavior(type_behavior type_behavior);

	private:
		behavior_factory() = delete;
	};

	inline behavior* behavior_factory::create_behavior(type_behavior type_behavior)
	{
		switch (type_behavior)
		{
		case suicidal_e: return new suicidal();
		case aggressive_e: return new aggressive();
		case balanced_e: return new balanced();
		case coward_e: return new coward();
		}
		return nullptr;
	}
}
#endif
