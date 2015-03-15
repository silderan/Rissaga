#pragma once

#include <SDL_rect.h>

#include "Point.h"
#include "Size.h"

namespace Ris
{
	class Rect
	{
		Point2D m_point;
		Size m_size;
		SDL_Rect m_rect;

	public:
		Rect() : m_point(), m_size()
		{ }
		template < typename T >
		Rect(T x, T y, T w, T h) : m_point(x, y), m_size(w, h)
		{ }
		template < typename P, typename S >
		Rect(const P &p, const S &s) : m_point(p), m_size(s)
		{ }
		Rect(const SDL_Rect &r) : m_point(r), m_size(r)
		{ }
		inline void set(float x, float y, float w, float h)
		{
			m_point.set(x, y);
			m_size.set(w, h);
		}
		inline void set(int x, int y, int w, int h)
		{
			m_point.set(x, y);
			m_size.set(w, h);
		}
		inline void set(const SDL_Rect &r)
		{
			m_point.set(r.x, r.y);
			m_size.set(r.w, r.h);
		}
		inline const SDL_Rect &getSDLRect()
		{
			m_rect.x = (int)round(m_point.getSDLRect().x);
			m_rect.y = (int)round(m_point.getSDLRect().y);
			m_rect.w = (int)round(m_size.getSDLPoint().x);
			m_rect.h = (int)round(m_size.getSDLPoint().y);

			return m_rect;
		}
		inline bool isEmpty() const { return SDL_RectEmpty((SDL_Rect*)this) == SDL_TRUE; }
		inline bool operator==(Rect &other) { return SDL_RectEquals(&other.getSDLRect(), &getSDLRect()) == SDL_TRUE; }
		inline bool intersects(Rect &other) { return SDL_HasIntersection(&other.getSDLRect(), &getSDLRect()) == SDL_TRUE; }

		inline bool intersect(Rect &other, Rect &result)
		{
			SDL_Rect r;
			if (SDL_IntersectRect(&other.getSDLRect(), &getSDLRect(), &r) == SDL_TRUE)
			{
				result.set(r);
				return true;
			}
			return false;
		}
		inline Rect intersect(Rect &other)
		{
			SDL_Rect r;
			SDL_IntersectRect(&other.getSDLRect(), &getSDLRect(), &r);
			return Rect(r);
		}

		inline void unionRect(Rect &other, Rect &result)
		{
			SDL_Rect r;
			SDL_UnionRect(&other.getSDLRect(), &getSDLRect(), &r);
			result.set(r);
		}
		Rect unionRect(Rect &other)
		{
			SDL_Rect r;
			SDL_UnionRect(&other.getSDLRect(), &getSDLRect(), &r);
			return Rect(r);
		}
		const Size &size() const { return m_size; }
		Size &size() { return m_size; }
		// Returns top-left point.
		const Point2D &origin() const { return m_point; }
		// Returns top-left point.
		Point2D &origin() { return m_point; }
		// TODO: Not wrapped... yet.
		//SDL_EnclosePoints
		//SDL_IntersectRectAndLine
	};
}
