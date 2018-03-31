#include "input_manager.h"
#include "iostream"
#include "g_vars.hpp"

using namespace std;

input_manager* input_manager::input_manager_ = nullptr;

void input_manager::update(RenderWindow& main_win, Event& event)
{
	switch (event.type)
	{
	case Event::JoystickMoved:
		// TODO: Prevent unnecessary changes/verifications (Limit number of Joystick Events created by the controller).
		// Often, even just pressing a button on a controller can provoke 4 to 5 JoystickMoved events.
		// Swiveling the joysticks constantly will currently generate about 500 events per second.
		for (size_t i = 0; i < 4; i++)
		{
			if (event.joystickMove.joystickId == i)
			{
				switch (event.joystickMove.axis)
				{
				case Joystick::X: // Left Joystick X axis.
					left_joystick_player_specific_[i].x = event.joystickMove.position;
					left_joystick_.x = left_joystick_player_specific_[i].x;
					break;
				case Joystick::Y: // Left Joystick Y axis.
					left_joystick_player_specific_[i].y = event.joystickMove.position;
					left_joystick_.y = left_joystick_player_specific_[i].y;
					break;
				case Joystick::Z: // Both triggers.
					if(event.joystickMove.position >= 0)
						right_trigger_[i] = event.joystickMove.position;
					else
						left_trigger_[i] = event.joystickMove.position;
					break;
				case Joystick::R: // Right Joystick X axis.
					right_joystick_player_specific_[i].y = event.joystickMove.position;
					right_joystick_.y = right_joystick_player_specific_[i].y;
					break;
				case Joystick::U: // Right Joystick Y axis.
					right_joystick_player_specific_[i].x = event.joystickMove.position;
					right_joystick_.x = right_joystick_player_specific_[i].x;
					break;
				default: break;
				}
			}
		}
		break;
	case Event::JoystickButtonPressed:
		for (size_t i = 0; i < 4; i++)
		{
			if (event.joystickButton.joystickId == i)
			{
				buttons_are_pressed_player_specific_[i][event.joystickButton.button] = true;
				buttons_are_pressed_[event.joystickButton.button] = true;
				break;
			}
		}
		break;
	case Event::JoystickButtonReleased:
		for (size_t i = 0; i < 4; i++)
		{
			if (event.joystickButton.joystickId == i)
			{
				buttons_are_pressed_player_specific_[i][event.joystickButton.button] = false;
				buttons_are_pressed_[event.joystickButton.button] = false;
				buttons_locked_[event.joystickButton.button] = false;
				break;
			}
		}
		break;
	case Event::JoystickDisconnected:
		for (size_t i = 0; i < 4; i++)
		{
			if (player_controller_ids_[i] == event.joystickConnect.joystickId)
			{
				--nb_of_controllers_;
				player_controller_ids_[i] = -1;
			}
		}
		break;
	case Event::JoystickConnected:
		for (size_t i = 0; i < 4; i++)
		{
			if (player_controller_ids_[i] == -1)
			{
				++nb_of_controllers_;
				player_controller_ids_[i] = event.joystickConnect.joystickId;
				break;
			}
		}
		break;
	case Event::Closed:
		main_win.close();
		break;
	case Event::MouseButtonPressed:
		switch (event.mouseButton.button)
		{
		case Mouse::Left:
			buttons_are_pressed_[rb] = true;
			break;
		default: break;
		}
		break;
	case Event::MouseButtonReleased:
		switch (event.mouseButton.button)
		{
		case Mouse::Left:
			buttons_are_pressed_[rb] = false;
			buttons_locked_[rb] = false;
			break;
		default: break;
		}
		break;
	case Event::KeyPressed:
		switch (event.key.code)
		{
		case Keyboard::Key::Up:
			left_joystick_.y = -100;
			break;
		case Keyboard::Key::W:
			left_joystick_.y = -100;
			break;
		case Keyboard::Key::Down:
			left_joystick_.y = 100;
			break;
		case Keyboard::Key::S:
			left_joystick_.y = 100;
			break;
		case Keyboard::Key::Left:
			left_joystick_.x = -100;
			break;
		case Keyboard::Key::A:
			left_joystick_.x = -100;
			break;
		case Keyboard::Key::Right:
			left_joystick_.x = 100;
			break;
		case Keyboard::Key::D:
			left_joystick_.x = 100;
			break;
		case Keyboard::Key::Return:
			buttons_are_pressed_[a] = true;
			break;
		case Keyboard::Key::Escape:
			buttons_are_pressed_[start] = true;
			break;
		default:break;
		}
		break;
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::Key::Up:
			left_joystick_.y = 0;
			break;
		case Keyboard::Key::W:
			left_joystick_.y = 0;
			break;
		case Keyboard::Key::Down:
			left_joystick_.y = 0;
			break;
		case Keyboard::Key::S:
			left_joystick_.y = 0;
			break;
		case Keyboard::Key::Left:
			left_joystick_.x = 0;
			break;
		case Keyboard::Key::A:
			left_joystick_.x = 0;
			break;
		case Keyboard::Key::Right:
			left_joystick_.x = 0;
			break;
		case Keyboard::Key::D:
			left_joystick_.x = 0;
			break;
		case Keyboard::Key::Return:
			buttons_are_pressed_[a] = false;
			buttons_locked_[a] = false;
			break;
		case Keyboard::Key::Escape:
			buttons_are_pressed_[start] = false;
			buttons_locked_[start] = false;
			break;
		default:break;
		}
		break;
	case Event::MouseMoved:
		angle_to_screen_center_ = atan2(
			g_vars::view_width / 2 - main_win.mapCoordsToPixel(Vector2f(Mouse::getPosition())).x,
			g_vars::view_height / 2 - main_win.mapCoordsToPixel(Vector2f(Mouse::getPosition())).y);
		angle_to_screen_center_ += 1.5708f;
		right_joystick_ = Vector2f(
			cos(angle_to_screen_center_) * 100,
			-sin(angle_to_screen_center_) * 100
		);
		break;
	default: break;
	}
}

bool input_manager::get_button_is_pressed(button button, int player)
{
	if(nb_of_controllers_ < 1)
	{
		return buttons_are_pressed_[static_cast<int>(button)];
	}
	return buttons_are_pressed_player_specific_[player_controller_ids_[player]][static_cast<int>(button)];
}

bool input_manager::get_button_is_pressed(button button)
{
	return buttons_are_pressed_[static_cast<int>(button)];
}

bool input_manager::get_button_locked(button button)
{
	return buttons_locked_[static_cast<int>(button)];
}

void input_manager::set_button_locked(button button)
{
	buttons_locked_[static_cast<int>(button)] = true;
}


Vector2f input_manager::get_joystick_after_tolerance(Vector2f joystick) const
{
	// test if the axis is within the 
	// absolute range of the magnitude tolerance and out of bounds values.
	const auto temp = Vector2f(fabs(joystick.x), fabs(joystick.y));
	if (temp.x >= joystick_magnitude_tolerance_ &&
		temp.x <= joystick_out_of_bounds_ || 
		temp.y >= joystick_magnitude_tolerance_ &&
		temp.y <= joystick_out_of_bounds_
		)
	{
		return joystick;
	}
	return Vector2f(0, 0);
}

Vector2f input_manager::get_left_joystick_pos(int player)
{
	if (nb_of_controllers_ < 1)
	{
		return get_left_joystick_pos();
	}
	return get_joystick_after_tolerance(left_joystick_player_specific_[player_controller_ids_[player]]);
}

Vector2f input_manager::get_left_joystick_pos() const
{
	return get_joystick_after_tolerance(left_joystick_);
}

Vector2f input_manager::get_right_joystick_pos(int player)
{
	if (nb_of_controllers_ < 1)
	{
		return get_right_joystick_pos();
	}
	return get_joystick_after_tolerance(right_joystick_player_specific_[player_controller_ids_[player]]);
}

Vector2f input_manager::get_right_joystick_pos() const
{
	return get_joystick_after_tolerance(right_joystick_);
}

float input_manager::get_left_trigger_pos(int player)
{
	return left_trigger_[player_controller_ids_[player]];
}

float input_manager::get_right_trigger_pos(int player)
{
	return right_trigger_[player_controller_ids_[player]];
}

#pragma region Singleton + Constructor Methods
input_manager::input_manager() :
	joystick_magnitude_tolerance_(25), 
	joystick_out_of_bounds_(100),
	angle_to_screen_center_(0),
	nb_of_controllers_(0)
{
	// When the input manager is first initialized, check to see if 
	// joysticks are already connected (since no events will be generated for them).
	for (size_t i = 0; i < 4; i++)
	{
		if (Joystick::isConnected(i))
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (player_controller_ids_[j] == -1)
				{
					++nb_of_controllers_;
					player_controller_ids_[j] = i;
					break;
				}
			}
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		buttons_are_pressed_[i] = false;
		buttons_locked_[i] = false;
	}
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			buttons_are_pressed_player_specific_[i][j] = false;
		}
	}
}

input_manager* input_manager::get_input_manager()
{
	if (!input_manager_)
	{
		input_manager_ = new input_manager;
	}
	return input_manager_;
}

void input_manager::release()
{
	delete input_manager_;
	input_manager_ = nullptr;
}
#pragma endregion
