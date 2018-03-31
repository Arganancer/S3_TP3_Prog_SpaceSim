#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <SFML/System/Vector2.hpp>
#include <math.h>

using namespace sf;

namespace tools
{
	static const float pi = 3.14159265359f;
	class vec_util
	{
	public:
		// Returns the angle, in rads, from a vector's origin to its end.
		static float angle_r(Vector2f vector);

		// Returns the angle, in rads, from the first vector to the other.
		static float angle_r(Vector2f origin, Vector2f end);

		// Returns given angle in degrees converted as its equivalent radiant form.
		static float angle_r(float angle_d);

		// Returns the angle, in degrees, from a vector's origin to its end.
		static float angle_d(Vector2f vector);

		// Returns the angle, in degrees, from the first vector to the other.
		static float angle_d(Vector2f origin, Vector2f end);

		// Returns given angle in radians converted as its equivalent degree form.
		static float angle_d(float angle_r);

		// Returns the direction of the given vector as a unit vector.
		static Vector2f direction(Vector2f vector);

		// Returns the direction from the first vector to the other as a unit vector.
		static Vector2f direction(Vector2f origin, Vector2f end);

		// Returns the direction of the given radian angle as a unit vector.
		static Vector2f direction(float angle);

		// Returns the normal of the given vector as a unit vector.
		static Vector2f direction_normal(Vector2f vector);

		// Returns the normal of the given vectors as a unit vector.
		static Vector2f direction_normal(Vector2f vector1, Vector2f vector2);

		// Returns the normal of the given vector.
		static Vector2f normal(Vector2f vector);

		// Returns the normal of the given vectors.
		static Vector2f normal(Vector2f vector1, Vector2f vector2);

		// Returns the dot product of the given vectors.
		static float dot(Vector2f vector1, Vector2f vector2);

		// Returns the magnitude (length) of the given vector.
		static float magnitude(Vector2f vector);

		// Returns the magnitude (length) between the given vectors.
		static float magnitude(Vector2f vector1, Vector2f vector2);

	private:
		vec_util() = delete;
	};

	inline float vec_util::angle_r(Vector2f vector)
	{
		return atan2f(vector.y, vector.x);
	}

	inline float vec_util::angle_r(Vector2f origin, Vector2f end)
	{
		return atan2f(end.y - origin.y, end.x - origin.x);
	}

	inline float vec_util::angle_r(float angle_d)
	{
		return angle_d * pi * 0.0055555555556f; // This product corresponds to the same operation as dividing by 180.
	}

	inline float vec_util::angle_d(Vector2f vector)
	{
		return angle_d(angle_r(vector));
	}

	inline float vec_util::angle_d(Vector2f origin, Vector2f end)
	{
		return angle_d(angle_r(origin, end));
	}

	inline float vec_util::angle_d(float angle_r)
	{
		return angle_r * 180 / pi;
	}

	inline Vector2f vec_util::direction(Vector2f vector)
	{
		return direction(angle_r(vector));
	}

	inline Vector2f vec_util::direction(Vector2f origin, Vector2f end)
	{
		return direction(angle_r(origin, end));
	}

	inline Vector2f vec_util::direction(float angle)
	{
		return Vector2f(cosf(angle), sinf(angle));
	}

	inline Vector2f vec_util::direction_normal(Vector2f vector)
	{
		return direction(normal(vector));
	}

	inline Vector2f vec_util::direction_normal(Vector2f vector1, Vector2f vector2)
	{
		return direction(normal(vector1, vector2));
	}

	inline Vector2f vec_util::normal(Vector2f vector)
	{
		return Vector2f(vector.y, -vector.x);
	}

	inline Vector2f vec_util::normal(Vector2f vector1, Vector2f vector2)
	{
		const auto temp_vec = Vector2f(vector1.x - vector2.x, vector1.y - vector2.y);
		return normal(temp_vec);
	}

	inline float vec_util::dot(Vector2f vector1, Vector2f vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y;
	}

	inline float vec_util::magnitude(Vector2f vector)
	{
		return sqrtf(vector.x * vector.x + vector.y * vector.y);
	}

	inline float vec_util::magnitude(Vector2f vector1, Vector2f vector2)
	{
		const auto temp_vec = Vector2f(vector1.x - vector2.x, vector1.y - vector2.y);
		return magnitude(temp_vec);
	}
}
#endif