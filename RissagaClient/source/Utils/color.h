#pragma once

#include <SDL_pixels.h>
#include "Math.h"

namespace Ris
{
	class Color
	{
		float r;
		float g;
		float b;
		float a;
		bool updateSDLColor;
		SDL_Color m_color;

	public:
		Color() :r(0.0f), g(0.0f), b(0.0f), a(1.0f), updateSDLColor(true)
		{ }
		Color(float _r, float _g, float _b, float _a = 1.0f) : r(_r), g(_g), b(_b), a(_a), updateSDLColor(true)
		{ }
		Color(int _r, int _g, int _b, int _a = 255) :
			r((m_color.r = _r) / 255.0f),
			g((m_color.g = _g) / 255.0f),
			b((m_color.b = _b) / 255.0f),
			a((m_color.a = _a) / 255.0f),
			updateSDLColor(false)
		{ }
		Color(const Color &c) : r(c.r), g(c.g), b(c.b), a(c.a), updateSDLColor(c.updateSDLColor)
		{
			m_color = c.m_color;
		}
		Color(const SDL_Color &c)
		{
			set(c);
		}

		const SDL_Color &getSDLColor()
		{
			if (updateSDLColor)
			{
				m_color.r = (Uint8)round(r*255.0f);
				m_color.g = (Uint8)round(g*255.0f);
				m_color.b = (Uint8)round(b*255.0f);
				m_color.a = (Uint8)round(a*255.0f);
				updateSDLColor = false;
			}
			return m_color;
		}

		inline Color &operator+=(const Color &other) { updateSDLColor = true; r += other.r; g += other.g; b += other.b; a += other.a; return *this; }
		inline Color &operator-=(const Color &other) { updateSDLColor = true; r -= other.r; g -= other.g; b -= other.b; a -= other.a; return *this; }
		inline Color &operator*=(const Color &other) { updateSDLColor = true; r *= other.r; g *= other.g; b *= other.b; a *= other.a; return *this; }
		inline Color &operator/=(const Color &other) { updateSDLColor = true; r /= other.r; g /= other.g; b /= other.b; a /= other.a; return *this; }
		inline Color operator*(const Color &other) const { return Color(r * other.r, g * other.g, b * other.b, a * other.a); }
		inline Color operator/(const Color &other) const { return Color(r / other.r, g / other.g, b / other.b, a / other.a); }
		inline Color operator+(const Color &other) const { return Color(r + other.r, g + other.g, b + other.b, a + other.a); }
		inline Color operator-(const Color &other) const { return Color(r - other.r, g - other.g, b - other.b, a - other.a); }

		// operators with floats (0.0 a 1.0)
		inline Color &operator+=(const float f) { updateSDLColor = true; r += f; g += f; b += f; a += f; return *this; }
		inline Color &operator-=(const float f) { updateSDLColor = true; r -= f; g -= f; b -= f; a -= f; return *this; }
		inline Color &operator*=(const float f) { updateSDLColor = true; r *= f; g *= f; b *= f; a *= f; return *this; }
		inline Color &operator/=(const float f) { updateSDLColor = true; r /= f; g /= f; b /= f; a /= f; return *this; }
		inline Color operator*(const float f) const { return Color(r * f, g * f, b * f, a * f); }
		inline Color operator/(const float f) const { return Color(r / f, g / f, b / f, a / f); }
		inline Color operator+(const float f) const { return Color(r + f, g + f, b + f, a + f); }
		inline Color operator-(const float f) const { return Color(r - f, g - f, b - f, a - f); }

		// operators with ints (0 a 255)
		inline Color &operator+=(int i) { return operator+=(i / 255.0f); }
		inline Color &operator-=(int i) { return operator-=(i / 255.0f); }
		inline Color &operator*=(int i) { return operator*=(i / 255.0f); }
		inline Color &operator/=(int i) { return operator/=(i / 255.0f); }
		inline Color operator*(int i) const { return operator*(i / 255.0f); }
		inline Color operator/(int i) const { return operator/(i / 255.0f); }
		inline Color operator+(int i) const { return operator+(i / 255.0f); }
		inline Color operator-(int i) const { return operator-(i / 255.0f); }

		// equality operators
		inline bool operator==(const Color &c) const { return (r == c.a) && (g == c.g) && (b == c.b) && (a == c.a); }
		inline bool operator!=(const Color &c) const { return !operator==(c); }

		inline void set(float _r, float _g, float _b, float _a = 1.0) { updateSDLColor = true; r = _r; g = _g; b = _b; a = _a; }
		inline void set(int _r, int _g, int _b, int _a = 255)
		{
			updateSDLColor = false;
			r = ((m_color.r = _r) / 255.0f);
			g = ((m_color.g = _g) / 255.0f);
			b = ((m_color.b = _b) / 255.0f);
			a = ((m_color.a = _a) / 255.0f);
		}
		inline void set(const SDL_Color &c) { set(c.r, c.g, c.b, c.a); }
	};
	// Solid Red
	static Color ColorRed(1.0f, 0.0f, 0.0f, 1.0f);
	// Solid Green
	static Color ColorGreen(0.0f, 1.0f, 0.0f, 1.0f);
	// Solid Blue
	static Color ColorBlue(0.0f, 0.0f, 1.0f, 1.0f);
	// Solid Yellow
	static Color ColorYellow(1.0f, 0.0f, 1.0f, 1.0f);
	// Solid Magenta
	static Color ColorMagenta(1.0f, 0.0f, 0.0f, 1.0f);
	// Solid Cyan
	static Color ColorCyan(0.0f, 1.0f, 1.0f, 1.0f);
	// Solid White
	static Color ColorWhite(1.0f, 1.0f, 1.0f, 1.0f);
}
