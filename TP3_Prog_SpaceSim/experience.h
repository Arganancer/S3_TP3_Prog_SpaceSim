#ifndef EXPERIENCE_H
#define EXPERIENCE_H
#include <SFML/System/Vector2.hpp>
#include "behavior.h"
#include "manoeuvre.h"

namespace ai
{
#pragma region EXPERIENCE_BASE_CLASS
	class experience
	{
	public:
		experience(
			int nb_of_weapons,
			bool has_hangars);
		virtual ~experience() = default;

		virtual void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position );
		virtual manoeuvre* get_new_manoeuvre(bool is_fighter) = 0;
		virtual sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) = 0;
		float get_rate_of_fire_modifier() const;
		int get_nb_of_active_weapons() const;
		bool get_is_firing() const;

	protected:
		virtual void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position) = 0;
		virtual void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position) = 0;
		virtual void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position) = 0;

		// MEMBERS
		int chances_of_perfect_aim_; // This member is evaluated on a scale of 1 to 100.
		behavior::type_state last_state_;
		float firing_angle_modifier_;
		float angle_to_enemy_;
		float rate_of_fire_modifier_;
		int nb_of_weapons_;
		int nb_of_currently_active_weapons_;
		bool has_hangars_;
		bool is_firing_;
	};
#pragma endregion

#pragma region ELITE
	class elite : public experience
	{
	public:
		elite(
			int nb_of_weapons,
			bool has_hangars);
		~elite();

		void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;

		manoeuvre* get_new_manoeuvre(bool is_fighter) override;
		sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) override;

	private:
		void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
	};
#pragma endregion

#pragma region VETERAN
	class veteran : public experience
	{
	public:
		veteran(
			int nb_of_weapons,
			bool has_hangars);
		~veteran();

		void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;

		manoeuvre* get_new_manoeuvre(bool is_fighter) override;
		sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) override;

	private:
		void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
	};
#pragma endregion

#pragma region SOLDIER
	class soldier : public experience
	{
	public:
		soldier(
			int nb_of_weapons,
			bool has_hangars);
		~soldier();

		void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;

		manoeuvre* get_new_manoeuvre(bool is_fighter) override;
		sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) override;

	private:
		void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
	};
#pragma endregion

#pragma region RECRUIT
	class recruit : public experience
	{
	public:
		recruit(
			int nb_of_weapons,
			bool has_hangars);
		~recruit();

		void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;

		manoeuvre* get_new_manoeuvre(bool is_fighter) override;
		sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) override;

	private:
		void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
	};
#pragma endregion

#pragma region RUFFIAN
	class ruffian : public experience
	{
	public:
		ruffian(
			int nb_of_weapons,
			bool has_hangars);
		~ruffian();

		void update(
			behavior::type_state current_state,
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;

		manoeuvre* get_new_manoeuvre(bool is_fighter) override;
		sf::Vector2f get_modified_aim(sf::Vector2f enemy_velocity, sf::Vector2f target_position) override;

	private:
		void evaluate_engaging(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_attacking(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
		void evaluate_retreating(
			sf::Vector2f position,
			sf::Vector2f enemy_position
		) override;
	};
#pragma endregion

#pragma region EXPERIENCE_FACTORY
	class experience_factory
	{
	public:
		enum type_experience
		{
			elite_e,
			veteran_e,
			soldier_e,
			recruit_e,
			ruffian_e
		};

		static experience* create_experience(
			type_experience type_experience,
			int nb_of_weapons,
			bool has_hangars);

	private:
		experience_factory();
	};

	inline experience* experience_factory::create_experience(
		type_experience type_experience,
		int nb_of_weapons,
		bool has_hangars)
	{
		switch (type_experience)
		{
		case elite_e: return new elite(nb_of_weapons, has_hangars);
		case veteran_e: return new veteran(nb_of_weapons, has_hangars);
		case soldier_e: return new soldier(nb_of_weapons, has_hangars);
		case recruit_e: return new recruit(nb_of_weapons, has_hangars);
		case ruffian_e: return new ruffian(nb_of_weapons, has_hangars);
		}
		return nullptr;
	}
#pragma endregion
}


#endif
