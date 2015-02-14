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
	class _2DPoint
	{
	public:
		T x;
		T y;

		// ctor
		inline _2DPoint<T>(T X, T Y) : x(X), y(Y)
		{}
		inline _2DPoint<T>() : x(0), y(0)
		{}

		// operators with another point
		inline _2DPoint<T>& operator+=(const _2DPoint<T>& other) { x += other.x; y += other.y; return *this; }
		inline _2DPoint<T>& operator-=(const _2DPoint<T>& other) { x -= other.x; y -= other.y; return *this; }
		inline _2DPoint<T>& operator*=(const _2DPoint<T>& other) { x *= other.x; y *= other.y; return *this; }
		inline _2DPoint<T>& operator/=(const _2DPoint<T>& other) { x /= other.x; y /= other.y; return *this; }
		inline _2DPoint<T>& operator%=(const _2DPoint<T>& other) { x = (T)((int)x % (int)other.x); y = (T)((int)y % (int)other.y); return *this; }
		inline _2DPoint<T> operator*(const _2DPoint<T>& other) const { return _2DPoint<T>(x * other.x, y * other.y); }
		inline _2DPoint<T> operator/(const _2DPoint<T>& other) const { return _2DPoint<T>(x / other.x, y / other.y); }
		inline _2DPoint<T> operator+(const _2DPoint<T>& other) const { return _2DPoint<T>(x + other.x, y + other.y); }
		inline _2DPoint<T> operator-(const _2DPoint<T>& other) const { return _2DPoint<T>(x - other.x, y - other.y); }
		inline _2DPoint<T> operator%(const _2DPoint<T>& other) const { return _2DPoint<T>((T)((int)x % (int)other.x), (T)((int)y % (int)other.y)); }

		// operators with scalars
		inline _2DPoint<T> operator-() const { return _2DPoint<T>(-x, -y); }
		inline _2DPoint<T>& operator+=(const T& scalar) { x += scalar; y += scalar; return *this; }
		inline _2DPoint<T>& operator-=(const T& scalar) { x -= scalar; y -= scalar; return *this; }
		inline _2DPoint<T>& operator*=(const T& scalar) { x *= scalar; y *= scalar; return *this; }
		inline _2DPoint<T>& operator/=(const T& scalar) { x /= scalar; y /= scalar; return *this; }
		inline _2DPoint<T>& operator%=(const T& scalar) { x = (T)((int)x % (int)scalar); y = (T)((int)y % (int)scalar); return *this; }
		inline _2DPoint<T> operator*(const T& scalar) const { return _2DPoint<T(x * scalar, y * scalar); }
		inline _2DPoint<T> operator/(const T& scalar) const { return _2DPoint<T>(x / scalar, y / scalar); }
		inline _2DPoint<T> operator+(const T& scalar) const { return _2DPoint<T>(x + scalar, y + scalar); }
		inline _2DPoint<T> operator-(const T& scalar) const { return _2DPoint<T>(x - scalar, y - scalar); }
		inline _2DPoint<T> operator%(const T& scalar) const { return _2DPoint<T>((T)((int)x % (int)scalar), (T)((int)y % (int)scalar)); }

		inline bool operator==(const _2DPoint<T>& other) const { return (x == other.x && y == other.y); }
		inline bool operator!=(const _2DPoint<T> &other) const { return !(*this == other); }

		// casting
		inline operator _2DPoint<float>() const	 { return _2DPoint<float>((float)x, (float)y); }
		inline operator _2DPoint<int>()	const	 { return _2DPoint<int>((int)x, (int)y); }

		inline void set(T X, T Y) { x = X; y = Y; }

		inline float getRadians() const { return (float)Math::radians(x, y); }
		inline float getDegrees() const { return (float)Math::degrees(x, y); }
		inline float getDegrees180() const { return (float)Math::degrees180(x, y); }
		inline float getDegrees360() const { return (float)Math::degrees360(x, y); }

		inline _2DPoint<T>& limitX(T min, T max)
		{
			x = Math::limit(min, max, x);
			return (*this);
		}
		inline _2DPoint<T>& limitY(T min, T max)
		{
			y = Math::limit(min, max, y);
			return (*this);
		}
		inline _2DPoint<T>& limit(T min, T max)
		{
			limitX(min, max);
			limitY(min, max);
			return (*this);
		}
		inline _2DPoint<T>& limit(T min, T max) const
		{
			_2DPoint<T> ret = *this;
			return ret.limit(min, max);
		}
		inline _2DPoint<T>& limit(const _2DPoint<T>& min, const _2DPoint<T>& max)
		{
			limitX(min.x, max.x);
			limitY(min.y, max.y);
			return (*this);
		}
		inline _2DPoint<T>& limit(const _2DPoint<T>& min, const _2DPoint<T>& max) const
		{
			_2DPoint<T> ret = *this;
			return ret.limit(min, max);
		}
		// return distance from other point
		inline float getDistance(const _2DPoint<T>& other) const
		{
			return sqrt((float)(Math::pow2(x - other.x) + Math::pow2(y - other.y)));
		}
		inline _2DPoint<T> &fromRadians(float radians, float length = 1.0)
		{
			x = (T)(cos(radians) * length);
			y = (T)(sin(radians) * length);
			return *this;
		}
		inline _2DPoint<T> &fromDegrees(float angle, float length = 1.0)
		{
			return fromRadians(Math::toRadians(angle), length);
		}
		inline T getLength()
		{
			return sqrt(Math::pow2(x) + Math::pow2(y));
		}
		inline _2DPoint<T>& rotateDegrees(float degrees)
		{
			return fromDegrees(getDegrees() + degrees, getLength());
		}
		inline _2DPoint<T>& rotateRadians(float radians)
		{
			return fromDegrees(getRadians() + radians, getLength());
		}
		/*
		// return normalized point
		inline _2DPoint<T> get_normalized() const
		{
			T div = std::abs(x) + std::abs(y);
			if (div == 0) return _2DPoint<T>::ZERO;
			return _2DPoint<T>(x / div, y / div);
		}

		// return absolute values
		inline _2DPoint<T> get_abs() const
		{
			return _2DPoint<T>(std::abs(x), std::abs(y));
		}

		// turn to absolute value
		inline _2DPoint<T>& abs()
		{
			x = std::abs(x);
			y = std::abs(y);
			return (*this);
		}

		// normalize this point
		inline _2DPoint<T>& normalize()
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
		inline _2DPoint<T> get_rotated(float angle) const
		{
			return _2DPoint<T>::from_angle(this->get_angle() + angle, this->get_length());
		}

		// rotate this vector
		inline _2DPoint<T>& rotate(float angle)
		{
			(*this) = _2DPoint<T>::from_angle(this->get_angle() + angle, this->get_length());
			return (*this);
		}


		// floor the values of this point
		inline _2DPoint<T>& floor()
		{
			this->x = (T)std::floor((float)this->x);
			this->y = (T)std::floor((float)this->y);
			return (*this);
		}
		inline _2DPoint<T> get_floor() const
		{
			return _2DPoint<T>((*this)).floor();
		}

		// ceil the values of this point
		inline _2DPoint<T>& ceil()
		{
			this->x = (T)std::ceil((float)this->x);
			this->y = (T)std::ceil((float)this->y);
			return (*this);
		}
		inline _2DPoint<T> get_ceil() const
		{
			return _2DPoint<T>((*this)).ceil();
		}

		// limit the number of digits after the decimal point
		// for example, if the point is (x=2.5232, y=0.2511244) and you call .get_round_by(2),
		// the return value will be this point: (x=2.52, y=0.25).
		// Note: obviously useable only for Ts with floating point (float, double...)
		inline _2DPoint<T> get_round_by(int num_of_zeroes_after_dot = 2) const
		{
			int factor = (int)pow((double)10.0, num_of_zeroes_after_dot);
			return ((_2DPoint<T>((*this) * (T)factor).floor()) / (T)factor);
		}
		inline _2DPoint<T>& round_by(int num_of_zeroes_after_dot = 2)
		{
			*this = this->get_round_by(num_of_zeroes_after_dot);
			return (*this);
		}

		// const useful points
		static _2DPoint<T> ZERO;
		static _2DPoint<T> ONE;
		static _2DPoint<T> HALF;

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
*/
	};
	typedef _2DPoint<float> Pointf2D;
	typedef _2DPoint<int> Pointi2D;
	typedef _2DPoint<unsigned char> Pointb2D;
};
