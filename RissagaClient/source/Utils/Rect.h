#pragma once

#include "SDL.h"

#include "Point.h"
#include "Size.h"

namespace Ris
{
	class Rect : public SDL_Rect
	{
	public:
		Rect()
		{
			x = 0; y = 0; w = 0; h = 0;
		}
		template < typename T >
		Rect(T xx, T yy, T ww, T hh)
		{
			x = (int)xx;
			y = (int)yy;
			w = (int)ww;
			h = (int)hh;
		}
		template < typename P, typename S >
		Rect(P &p, S &s)
		{
			x = p.x;
			y = p.y;

			w = s.w;
			h = s.h;
		}

		inline bool isEmpty() const { return SDL_RectEmpty((SDL_Rect*)this) == SDL_TRUE; }
		inline bool operator==(const Rect &other) const { return SDL_RectEquals(&other, this) == SDL_TRUE; }
		inline bool intersects(const Rect &other) const { return SDL_HasIntersection(&other, this) == SDL_TRUE; }

		inline bool intersect(const Rect &other, Rect &result) const
		{
			return SDL_IntersectRect(&other, this, &result) == SDL_TRUE;
		}
		inline Rect intersect(const Rect &other) const
		{
			Rect r;
			// As not sure if r is changed even returning false, this ensures that rect is invalid.
			if (!SDL_IntersectRect(&other, this, &r))
			{
				r.w = r.h = 0;
			}
			return r;
		}

		inline void unionRect(const Rect &other, Rect &result)
		{
			SDL_UnionRect(&other, this, &result);
		}
		Rect unionRect(const Rect &other)
		{
			Rect r;
			SDL_UnionRect(&other, this, &r);
			return r;
		}
		// TODO: Not wrapped... yet.
		//SDL_EnclosePoints
		//SDL_IntersectRectAndLine
	};
}
