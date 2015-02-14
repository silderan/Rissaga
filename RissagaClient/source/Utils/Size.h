#pragma once

namespace Ris
{
	template <typename T>
	class _Size
	{
	public:
		T w;
		T h;

		inline _Size<T>() : w((T)0), h((T)0)
		{}
		inline _Size<T>(T _w, T _h) : w(_w), h(_h)
		{}
	};
	typedef _Size<int> Sizei;
	typedef _Size<float> Sizef;
};