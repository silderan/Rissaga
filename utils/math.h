#ifndef RIS_MATH_H
#define RIS_MATH_H

#pragma once
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

namespace Ris
{
	template<class T> inline T operator~ (T a) { return (T)~(int)a; }
	template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
	template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
	template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
	template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
	template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
	template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }

	class Math
	{
	public:
		template <typename T>
		inline static T max(T a, T b) { return (a > b) ? a : b; }
		template <typename T>
		inline static T min(T a, T b) { return (a < b) ? a : b; }
		template <typename T>
		inline static T limit(T mi, T ma, T t) { return min(ma, max(mi, t)); }

		template <typename T>
		inline static T pow2(T v) { return v*v; }

		// Limits angle to be between 0 to 360
		// Just 'float' version as numbers are low.
		inline static float limitDegrees_360(float x)
		{
			x = fmod(x, 360.0f);
			if (x < 0.0f)
				x += 360.0f;
			return x;
		}

		// Limits angle to be between -180 to 180
		// Just 'float' version as numbers are low.
		inline static float limitDegrees_180(float x)
		{
			x = fmod(x + 180.0f, 360.0f);
			if (x < 0.0f)
				x += 360.0f;
			return x - 180.0f;
		}

		template <typename T>
		inline static T radians(T x, T y) { return atan2(x, y); }
		inline static float radians(int x, int y) { return (float)atan2((float)x, (float)y); }

		inline static float toDegrees(float radians) { return radians*(180.0f / (float)M_PI); }
		inline static long double toDegrees(long double radians) { return radians*(180.0l / M_PI); }

		inline static float toRadians(float degrees) { return degrees * (float)M_PI / 180.0f; }
		inline static long double toRadians(long double degrees) { return degrees * M_PI / 180.0l; }

		template <typename T>
		inline static T degrees(T x, T y) { return Math::toDegrees(radians(x, y)); }
		template <typename T>
		inline static T degrees180(T x, T y) { return Math::limitDegrees_180(degrees(x, y)); }
		template <typename T>
		inline static T degrees360(T x, T y) { return Math::limitDegrees_360(degrees(x, y)); }
	};
};
#endif
