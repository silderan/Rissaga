/**
* Define the Point class.
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once

#include "Math.h"

namespace Ris
{
	/**
	 * A class that encapsulates a 2D point.
	 */
	template <typename T>
	class __Point
	{
	public:
		T x;
		T y;

		// ctor
		inline __Point<T>(T X, T Y) : x(X), y(Y)
		{}
		inline __Point<T>() : x(0), y(0)
		{}

		// operators with another point
		inline __Point<T>& operator+=(const __Point<T>& other) { x += other.x; y += other.y; return *this; }
		inline __Point<T>& operator-=(const __Point<T>& other) { x -= other.x; y -= other.y; return *this; }
		inline __Point<T>& operator*=(const __Point<T>& other) { x *= other.x; y *= other.y; return *this; }
		inline __Point<T>& operator/=(const __Point<T>& other) { x /= other.x; y /= other.y; return *this; }
		inline __Point<T>& operator%=(const __Point<T>& other) { x = (T)((int)x % (int)other.x); y = (T)((int)y % (int)other.y); return *this; }
		inline __Point<T> operator*(const __Point<T>& other) const { return __Point<T>(x * other.x, y * other.y); }
		inline __Point<T> operator/(const __Point<T>& other) const { return __Point<T>(x / other.x, y / other.y); }
		inline __Point<T> operator+(const __Point<T>& other) const { return __Point<T>(x + other.x, y + other.y); }
		inline __Point<T> operator-(const __Point<T>& other) const { return __Point<T>(x - other.x, y - other.y); }
		inline __Point<T> operator%(const __Point<T>& other) const { return __Point<T>((T)((int)x % (int)other.x), (T)((int)y % (int)other.y)); }

		// operators with scalars
		inline __Point<T> operator-() const { return __Point<T>(-x, -y); }
		inline __Point<T>& operator+=(const T& scalar) { x += scalar; y += scalar; return *this; }
		inline __Point<T>& operator-=(const T& scalar) { x -= scalar; y -= scalar; return *this; }
		inline __Point<T>& operator*=(const T& scalar) { x *= scalar; y *= scalar; return *this; }
		inline __Point<T>& operator/=(const T& scalar) { x /= scalar; y /= scalar; return *this; }
		inline __Point<T>& operator%=(const T& scalar) { x = (T)((int)x % (int)scalar); y = (T)((int)y % (int)scalar); return *this; }
		inline __Point<T> operator*(const T& scalar) const { return __Point<T(x * scalar, y * scalar); }
		inline __Point<T> operator/(const T& scalar) const { return __Point<T>(x / scalar, y / scalar); }
		inline __Point<T> operator+(const T& scalar) const { return __Point<T>(x + scalar, y + scalar); }
		inline __Point<T> operator-(const T& scalar) const { return __Point<T>(x - scalar, y - scalar); }
		inline __Point<T> operator%(const T& scalar) const { return __Point<T>((T)((int)x % (int)scalar), (T)((int)y % (int)scalar)); }

		inline bool operator==(const __Point<T>& other) const { return (x == other.x && y == other.y); }
		inline bool operator!=(const __Point<T> &other) const { return !(*this == other); }

		// casting
		inline operator __Point<float>() const	 { return __Point<float>((float)x, (float)y); }
		inline operator __Point<int>()	const	 { return __Point<int>((int)x, (int)y); }

		inline void set(T X, T Y) { x = X; y = Y; }

		inline float getRadian() const { return Math::radian(x, y); }
		inline float getAngle() const { return Math::angle(x, y); }
		inline float getAngle180() const { return Math::angle180(x, y); }
		inline float getAngle360() const { return Math::angle360(x, y); }

		inline __Point<T>& limitX(T min, T max)
		{
			x = Math::limit(min, max, x);
			return (*this);
		}
		inline __Point<T>& limitY(T min, T max)
		{
			y = Math::limit(min, max, y);
			return (*this);
		}
		inline __Point<T>& limit(T min, T max)
		{
			limitX(min, max);
			limitY(min, max);
			return (*this);
		}
		inline __Point<T>& limit(T min, T max) const
		{
			__Point<T> ret = *this;
			return ret.limit(min, max);
		}
		inline __Point<T>& limit(const __Point<T>& min, const __Point<T>& max)
		{
			limitX(min.x, max.x);
			limitY(min.y, max.y);
			return (*this);
		}
		inline __Point<T>& limit(const __Point<T>& min, const __Point<T>& max) const
		{
			__Point<T> ret = *this;
			return ret.limit(min, max);
		}
		// return distance from other point
		inline float distance(const __Point<T>& other) const
		{
			return sqrt((float)(Math::pow2(x - other.x) + Math::pow2(y - other.y)));
		}
		/*
		// return normalized point
		inline __Point<T> get_normalized() const
		{
			T div = std::abs(x) + std::abs(y);
			if (div == 0) return __Point<T>::ZERO;
			return __Point<T>(x / div, y / div);
		}

		// return absolute values
		inline __Point<T> get_abs() const
		{
			return __Point<T>(std::abs(x), std::abs(y));
		}

		// turn to absolute value
		inline __Point<T>& abs()
		{
			x = std::abs(x);
			y = std::abs(y);
			return (*this);
		}

		// normalize this point
		inline __Point<T>& normalize()
		{
			T div = std::abs(x) + std::abs(y);
			if (div == 0) return (*this);
			x /= div;
			y /= div;
			return (*this);
		}

		// return the length of this vector
		inline float get_length() const
		{
			return sqrt(pow((float)x, 2) + pow((float)y, 2));
		}

		// return a rotated version of this vector
		inline __Point<T> get_rotated(float angle) const
		{
			return __Point<T>::from_angle(this->get_angle() + angle, this->get_length());
		}

		// rotate this vector
		inline __Point<T>& rotate(float angle)
		{
			(*this) = __Point<T>::from_angle(this->get_angle() + angle, this->get_length());
			return (*this);
		}


		// floor the values of this point
		inline __Point<T>& floor()
		{
			this->x = (T)std::floor((float)this->x);
			this->y = (T)std::floor((float)this->y);
			return (*this);
		}
		inline __Point<T> get_floor() const
		{
			return __Point<T>((*this)).floor();
		}

		// ceil the values of this point
		inline __Point<T>& ceil()
		{
			this->x = (T)std::ceil((float)this->x);
			this->y = (T)std::ceil((float)this->y);
			return (*this);
		}
		inline __Point<T> get_ceil() const
		{
			return __Point<T>((*this)).ceil();
		}

		// limit the number of digits after the decimal point
		// for example, if the point is (x=2.5232, y=0.2511244) and you call .get_round_by(2),
		// the return value will be this point: (x=2.52, y=0.25).
		// Note: obviously useable only for Ts with floating point (float, double...)
		inline __Point<T> get_round_by(int num_of_zeroes_after_dot = 2) const
		{
			int factor = (int)pow((double)10.0, num_of_zeroes_after_dot);
			return ((__Point<T>((*this) * (T)factor).floor()) / (T)factor);
		}
		inline __Point<T>& round_by(int num_of_zeroes_after_dot = 2)
		{
			*this = this->get_round_by(num_of_zeroes_after_dot);
			return (*this);
		}

		// const useful points
		static __Point<T> ZERO;
		static __Point<T> ONE;
		static __Point<T> HALF;

		// serialize the point into representable string
		String serialize() const
		{
			return ness_float_to_string(x) + "," + ness_float_to_string(y);
		}

		// deserialize the point from a representable string
		void deserialize(const String& src)
		{
			size_t sep = src.find(',');
			if (sep == -1) throw WrongFormatError("Input string is not a valid point format! serialized point must contain a comma");
			std::string sx = src.substr(0, sep);
			std::string sy = src.substr(sep + 1);
			x = (T)(atof(sx.c_str()));
			y = (T)(atof(sy.c_str()));
		}

		// static function: create point from angle
		static __Point<T> from_angle(float angle, float velocity = 1.0f)
		{
			__Point<T> ret;
			ret.x = (T)(cos(DEGREE_TO_RADIAN(angle)) * velocity);
			ret.y = (T)(sin(DEGREE_TO_RADIAN(angle)) * velocity);
			return ret;
		}
*/
	};
	typedef __Point<float> Pointf;
	typedef __Point<int> Pointi;
	typedef __Point<unsigned char> Pointb;
};
