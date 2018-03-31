#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class input_manager
{
public:
	enum button
	{
		a,
		// 0
		b,
		// 1
		x,
		// 2
		y,
		// 3
		lb,
		// 4
		rb,
		// 5
		select,
		// 6
		start,
		// 7
		ls_press,
		// 8
		rs_press,
		// 9
	};

#pragma region Constructor + Singleton methods
public:
	static input_manager* get_input_manager();
	static void release();
private:
	/// <summary>
	/// Initialise une nouvelle instance de la classe <see cref = "input_manager" />.
	/// </summary>
	input_manager();
	input_manager(const input_manager&); // Does not need to be defined, stops the singleton from being able to be copied.
	void operator=(const input_manager&); // Does not need to be defined, stops the singleton from being able to be copied.

	static input_manager* input_manager_;
#pragma endregion
public:
	/// <summary>
	/// Mets à jour toutes les valeurs de l'état du matériel de cette image(frame).
	/// </summary>
	/// <param name="main_win">L'écran principal.</param>
	void update(RenderWindow& main_win, Event& event);

#pragma region Joystick
	/// <summary>
	/// Gets the button.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	bool get_button_is_pressed(button button, int player);
	bool get_button_is_pressed(button button);
	bool get_button_locked(button button);
	void set_button_locked(button button);

	Vector2f get_left_joystick_pos() const;
	Vector2f get_left_joystick_pos(int player);
	Vector2f get_right_joystick_pos() const;
	Vector2f get_right_joystick_pos(int player);
	float get_left_trigger_pos(int player);
	float get_right_trigger_pos(int player);

private:
	Vector2f get_joystick_after_tolerance(Vector2f joystick) const;

	float joystick_magnitude_tolerance_;
	float joystick_out_of_bounds_;
	float angle_to_screen_center_;
	int nb_of_controllers_;
	int player_controller_ids_[4]{-1, -1, -1, -1};
	bool buttons_are_pressed_player_specific_[4][10];
	bool buttons_are_pressed_[10];
	bool buttons_locked_[10];
	Vector2f left_joystick_;
	Vector2f right_joystick_;
	Vector2f left_joystick_player_specific_[4];
	Vector2f right_joystick_player_specific_[4];
	float left_trigger_[4];
	float right_trigger_[4];
#pragma endregion
};
#endif
