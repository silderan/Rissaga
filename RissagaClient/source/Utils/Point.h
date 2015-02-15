/**
* Define the Point class.
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once

#include "Math.h"
#include "SDL_rect.h"

namespace Ris
{
	/**
	 * A class for a 2D point.
	 */
	class Point2D
	{
	public:
		float x;
		float y;
		bool updateSDLPoint;
		SDL_Point m_point;

		inline Point2D(float X, float Y) : x(X), y(Y), updateSDLPoint(true)
		{ }
		inline Point2D(int X, int Y) : x((float)X), y((float)Y), updateSDLPoint(false)
		{
			m_point.x = X;
			m_point.y = Y;
		}
		inline Point2D() : x(0), y(0), updateSDLPoint(true)
		{ }
		inline Point2D(const Point2D &p) : x(p.x), y(p.y), updateSDLPoint(true)
		{ }
		inline Point2D(const SDL_Rect &r) : x((float)r.x), y((float)r.y), updateSDLPoint(false)
		{
			m_point.x = r.x;
			m_point.y = r.y;
		}
		inline Point2D(const SDL_Point &p) : x((float)p.x), y((float)p.y), updateSDLPoint(false)
		{
			m_point.x = p.x;
			m_point.y = p.y;
		}

		inline float getX() const { return x; }
		inline float getY() const { return y; }
		inline Point2D &set(float X, float Y)
		{
			updateSDLPoint = true;
			x = X;
			y = Y;
			return *this;
		}
		inline Point2D &set(int X, int Y)
		{
			updateSDLPoint = false;
			x = (float)(m_point.x = X);
			y = (float)(m_point.y = Y);
			return *this;
		}
		inline Point2D &set(const SDL_Point &p) { return set(p.x, p.y); }
		inline Point2D &set(const SDL_Rect &r) { return set(r.x, r.y); }
		template <typename T>
		inline float setX(const T &v) { updateSDLPoint = true; return x = (float)v; }
		template <typename T>
		inline float setY(const T &v) { updateSDLPoint = true; return y = (float)v; }
		template <typename T>
		inline float adjustX(const T &v) { updateSDLPoint = true; return x += (float)v; }
		template <typename T>
		inline float adjustY(const T &v) { updateSDLPoint = true; return y += (float)v; }

		// operators with a point
		inline Point2D &operator+=(const Point2D &p) { updateSDLPoint = true; x += p.x; y += p.y; return *this; }
		inline Point2D &operator-=(const Point2D &p) { updateSDLPoint = true; x -= p.x; y -= p.y; return *this; }
		inline Point2D &operator*=(const Point2D &p) { updateSDLPoint = true; x *= p.x; y *= p.y; return *this; }
		inline Point2D &operator/=(const Point2D &p) { updateSDLPoint = true; x /= p.x; y /= p.y; return *this; }
		inline Point2D &operator%=(const Point2D &p) { updateSDLPoint = true; x = (float)((int)x % (int)p.x); y = (float)((int)y % (int)p.y); return *this; }
		inline Point2D operator*(const Point2D &p) const { return Point2D(x * p.x, y * p.y); }
		inline Point2D operator/(const Point2D &p) const { return Point2D(x / p.x, y / p.y); }
		inline Point2D operator+(const Point2D &p) const { return Point2D(x + p.x, y + p.y); }
		inline Point2D operator-(const Point2D &p) const { return Point2D(x - p.x, y - p.y); }
		inline Point2D operator%(const Point2D &p) const { return Point2D((float)((int)x % (int)p.x), (float)((int)y % (int)p.y)); }

		// operators with scalars
		inline Point2D operator-() const { return Point2D(-x, -y); }

		template <typename T>
		inline Point2D &operator+=(const T& scalar) { updateSDLPoint = true; x += scalar; y += scalar; return *this; }
		template <typename T>
		inline Point2D &operator-=(const T& scalar) { updateSDLPoint = true; x -= scalar; y -= scalar; return *this; }
		template <typename T>
		inline Point2D &operator*=(const T& scalar) { updateSDLPoint = true; x *= scalar; y *= scalar; return *this; }
		template <typename T>
		inline Point2D &operator/=(const T& scalar) { updateSDLPoint = true; x /= scalar; y /= scalar; return *this; }
		template <typename T>
		inline Point2D &operator%=(const T& scalar) { updateSDLPoint = true; x = (T)((int)x % (int)scalar); y = (T)((int)y % (int)scalar); return *this; }
		template <typename T>
		inline Point2D operator*(const T& scalar) const { return _2DPoint<T(x * scalar, y * scalar); }
		template <typename T>
		inline Point2D operator/(const T& scalar) const { return Point2D(x / scalar, y / scalar); }
		template <typename T>
		inline Point2D operator+(const T& scalar) const { return Point2D(x + scalar, y + scalar); }
		template <typename T>
		inline Point2D operator-(const T& scalar) const { return Point2D(x - scalar, y - scalar); }
		template <typename T>
		inline Point2D operator%(const T& scalar) const { return Point2D((T)((int)x % (int)scalar), (T)((int)y % (int)scalar)); }

		inline bool operator==(const Point2D& p) const { return (x == p.x && y == p.y); }
		inline bool operator!=(const Point2D &p) const { return !(*this == p); }

		inline float getRadians() const { return (float)Math::radians(x, y); }
		inline float getDegrees() const { return (float)Math::degrees(x, y); }
		inline float getDegrees180() const { return (float)Math::degrees180(x, y); }
		inline float getDegrees360() const { return (float)Math::degrees360(x, y); }

		template <typename T>
		inline Point2D& limitX(T min, T max)
		{
			updateSDLPoint = true;
			x = Math::limit(min, max, x);
			return (*this);
		}
		template <typename T>
		inline Point2D& limitY(T min, T max)
		{
			updateSDLPoint = true;
			y = Math::limit(min, max, y);
			return (*this);
		}
		template <typename T>
		inline Point2D& limit(T min, T max)
		{
			limitX(min, max);
			limitY(min, max);
			return (*this);
		}
		template <typename T>
		inline Point2D& limit(T min, T max) const
		{
			Point2D ret = *this;
			return ret.limit(min, max);
		}
		inline Point2D& limit(const Point2D& min, const Point2D& max)
		{
			updateSDLPoint = true;
			limitX(min.x, max.x);
			limitY(min.y, max.y);
			return (*this);
		}
		inline Point2D& limit(const Point2D& min, const Point2D& max) const
		{
			Point2D ret = *this;
			return ret.limit(min, max);
		}
		// return distance from p point
		inline float getDistance(const Point2D& p) const
		{
			return sqrt((float)(Math::pow2(x - p.x) + Math::pow2(y - p.y)));
		}
		inline Point2D &fromRadians(float radians, float length = 1.0)
		{
			updateSDLPoint = true;
			x = (float)(cos(radians) * length);
			y = (float)(sin(radians) * length);
			return *this;
		}
		inline Point2D &fromDegrees(float angle, float length = 1.0)
		{
			return fromRadians(Math::toRadians(angle), length);
		}
		inline float getLength() const
		{
			return sqrt(Math::pow2(x) + Math::pow2(y));
		}
		inline Point2D& rotateDegrees(float degrees)
		{
			return fromDegrees(getDegrees() + degrees, getLength());
		}
		inline Point2D& rotateRadians(float radians)
		{
			return fromDegrees(getRadians() + radians, getLength());
		}
		/*
		// return normalized point
		inline Point2D get_normalized() const
		{
			T div = std::abs(x) + std::abs(y);
			if (div == 0) return Point2D::ZERO;
			return Point2D(x / div, y / div);
		}

		// return absolute values
		inline Point2D get_abs() const
		{
			return Point2D(std::abs(x), std::abs(y));
		}

		// turn to absolute value
		inline Point2D& abs()
		{
			x = std::abs(x);
			y = std::abs(y);
			return (*this);
		}

		// normalize this point
		inline Point2D& normalize()
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
		inline Point2D get_rotated(float angle) const
		{
			return Point2D::from_angle(this->get_angle() + angle, this->get_length());
		}

		// rotate this vector
		inline Point2D& rotate(float angle)
		{
			(*this) = Point2D::from_angle(this->get_angle() + angle, this->get_length());
			return (*this);
		}


		// floor the values of this point
		inline Point2D& floor()
		{
			this->x = (T)std::floor((float)this->x);
			this->y = (T)std::floor((float)this->y);
			return (*this);
		}
		inline Point2D get_floor() const
		{
			return Point2D((*this)).floor();
		}

		// ceil the values of this point
		inline Point2D& ceil()
		{
			this->x = (T)std::ceil((float)this->x);
			this->y = (T)std::ceil((float)this->y);
			return (*this);
		}
		inline Point2D get_ceil() const
		{
			return Point2D((*this)).ceil();
		}

		// limit the number of digits after the decimal point
		// for example, if the point is (x=2.5232, y=0.2511244) and you call .get_round_by(2),
		// the return value will be this point: (x=2.52, y=0.25).
		// Note: obviously useable only for Ts with floating point (float, double...)
		inline Point2D get_round_by(int num_of_zeroes_after_dot = 2) const
		{
			int factor = (int)pow((double)10.0, num_of_zeroes_after_dot);
			return ((Point2D((*this) * (T)factor).floor()) / (T)factor);
		}
		inline Point2D& round_by(int num_of_zeroes_after_dot = 2)
		{
			*this = this->get_round_by(num_of_zeroes_after_dot);
			return (*this);
		}

		// const useful points
		static Point2D ZERO;
		static Point2D ONE;
		static Point2D HALF;

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

		*/
		const SDL_Point &getSDLRect()
		{
			if (updateSDLPoint)
			{
				m_point.x = (int)round(x);
				m_point.y = (int)round(y);
				updateSDLPoint = false;
			}
			return m_point;
		}
	};
};
