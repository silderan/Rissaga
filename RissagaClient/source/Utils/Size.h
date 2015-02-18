#pragma once

namespace Ris
{
	class Size
	{
		float w;
		float h;
		SDL_Point m_point;

	public:
		inline Size() : w(0.0f), h(0.0f)
		{ }
		template <typename T>
		inline Size(const T &_w, const T &_h) : w((float)_w), h((float)_h)
		{ }
		inline Size(const Size &s) : w(s.w), h(s.h)
		{ }
		inline Size(const SDL_Point &p) : w((float)p.x), h((float)p.y)
		{ }
		inline Size(const SDL_Rect &r) : w((float)r.x), h((float)r.y)
		{ }
		template <typename T>
		inline Size &set(T &W, T &H)
		{
			w = (float)W;
			h = (float)H;
			return *this;
		}
		inline Size &set(const SDL_Point &p) { return set(p.x, p.y); }
		inline Size &set(const SDL_Rect &r) { return set(r.w, r.h); }
		inline Size &set(const Size &s) { return set(s.w, s.h); }

		inline float getWidth() const { return w; }
		inline float getHeight() const { return h; }

		template <typename T>
		inline float setWidth(const T &a) { w = (float)a; }
		template <typename T>
		inline float setHeight(const T &a) { h = (float)a; }
		template <typename T>

		inline Size &adjust(const T &W, const T&H) { w += (float)W; h += (float)H; return *this; }
		inline Size &adjust(const Size &p) { w += (float)p.w; h += (float)p.h; return *this; }
		template <typename T>
		inline float adjustWidth(T a) { return (w += (float)a;) }
		template <typename T>
		inline float adjustHeight(T a) { return (h += (float)a;) }

		inline const SDL_Point &getSDLPoint()
		{
			m_point.x = (int)round(w);
			m_point.y = (int)round(h);

			return m_point;
		}
	};
};
