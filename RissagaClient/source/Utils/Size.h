#pragma once

namespace Ris
{
	class Size
	{
		float w;
		float h;
		SDL_Point m_point;
		bool updateSDLSize;

	public:
		inline Size() : w(0.0f), h(0.0f)
		{ }
		template <typename T>
		inline Size(const T &_w, const T &_h) : w((float)_w), h((float)_h), updateSDLSize(true)
		{ }
		inline Size(const Size &s) : w(s.w), h(s.h), updateSDLSize(true)
		{ }
		inline Size(const SDL_Point &p) : w((float)p.x), h((float)p.y), updateSDLSize(false)
		{
			m_point.x = p.x;
			m_point.y = p.y;
		}
		inline Size(const SDL_Rect &r) : w((float)r.x), h((float)r.y), updateSDLSize(false)
		{
			m_point.x = r.w;
			m_point.y = r.h;
		}
		inline Size &set(float W, float H)
		{
			updateSDLSize = true;
			w = W;
			h = H;
			return *this;
		}
		inline Size &set(int W, int H)
		{
			updateSDLSize = false;
			w = (float)(m_point.x = W);
			h = (float)(m_point.y = H);
			return *this;
		}
		inline Size &set(const SDL_Point &p) { return set(p.x, p.y); }
		inline Size &set(const SDL_Rect &r) { return set(r.w, r.h); }
		inline float getWidth() const { return w; }
		inline float getHeight() const { return h; }
		inline float setWidth(float a) { updateSDLSize = true; w = a; }
		inline float setHeight(float a) { updateSDLSize = true; h = a; }
		inline float adjustWidth(float a) { updateSDLSize = true; w += a; }
		inline float adjustHeight(float a) { updateSDLSize = true; h += a; }

		inline const SDL_Point &getSDLPoint()
		{
			if (updateSDLSize)
			{
				m_point.x = (int)round(w);
				m_point.y = (int)round(h);
				updateSDLSize = false;
			}
			return m_point;
		}
	};
};