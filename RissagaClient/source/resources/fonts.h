#pragma once

#include <unordered_map>
#include <memory>
#include <SDL_ttf.h>

#include "../Utils/String.h"

namespace Ris
{
	class Font
	{
		TTF_Font *m_font;
	public:
		Font() : m_font(nullptr)
		{

		}
		inline bool isValid() { return m_font != nullptr; }
		inline bool load(const String fname, int size);
	};
	typedef std::shared_ptr<Font> FontShared;

	class Fonts : std::unordered_map<String, FontShared>
	{
		FontShared emptyFont;

	public:

		static String createFontID(const String &fname, int size);
		// Fonts are identified by filename and size.
		FontShared getFont(String fname, int size);
	};
}
