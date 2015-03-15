#pragma once

#include <unordered_map>
#include <memory>
#include "SDL_ttf.h"

#include "common/string.h"
#include "common/logging.h"
#include "utils/Size.h"

namespace Ris
{
	class Font
	{
		TTF_Font *m_font;
	public:
		enum Style
		{
			NoStyle = TTF_STYLE_NORMAL,
			Bold = TTF_STYLE_BOLD,
			Italic = TTF_STYLE_ITALIC,
			Underline = TTF_STYLE_UNDERLINE,
			Strikethrough = TTF_STYLE_STRIKETHROUGH
		};
		enum Hinting
		{
			Normal = TTF_HINTING_NORMAL,
			Light = TTF_HINTING_LIGHT,
			Mono = TTF_HINTING_MONO,
			NoHint = TTF_HINTING_NONE
		};
		Font() : m_font(nullptr)
		{

		}
		~Font()
		{
			if (m_font != nullptr)
				TTF_CloseFont(m_font);
		}
		inline bool isValid() const { return m_font != nullptr; }
		inline bool load(const String &fname, int size);

		inline Style getStyle() const { return static_cast<Style>(TTF_GetFontStyle(m_font)); }
		inline void setStyle(const Style &s) { TTF_SetFontStyle(m_font, static_cast<int>(s)); }

		inline int getOutlineSize() const { return TTF_GetFontOutline(m_font); }
		inline void setOutlineSize(int s) { TTF_SetFontOutline(m_font, s); }

		inline Hinting getHinting() const { return static_cast<Hinting>(TTF_GetFontHinting(m_font)); }
		inline void setHinting(const Hinting &s) { TTF_SetFontHinting(m_font, static_cast<int>(s)); }

		inline int getHeight() const { return TTF_FontHeight(m_font); }

		inline int getAscent() const { return TTF_FontAscent(m_font); }

		inline int getDescent() const { return TTF_FontDescent(m_font); }

		inline int getLineSkip() const { return TTF_FontLineSkip(m_font); }

		inline int getKerning() const { return TTF_GetFontKerning(m_font); }
//		inline int getKerningSize() const { return TTF_GetFontKerningSize(m_font); }
		inline void setKerning(int s) { TTF_SetFontKerning(m_font, s); }

		inline int getFacesCount() const { return TTF_FontFaces(m_font); }

		inline bool isFixedWidth() const { return TTF_FontFaceIsFixedWidth(m_font) != 0; }
		inline String familyName() const { return TTF_FontFaceFamilyName(m_font); }
		inline String styleName() const { return TTF_FontFaceStyleName(m_font); }

		inline bool containsGilph(Uint16 ch) const { return TTF_GlyphIsProvided(m_font, ch) == SDL_TRUE; }
		inline int glyphMetrics(Uint16 ch,
			int *minx, int *maxx,
			int *miny, int *maxy, int *advance) const
		{
			return TTF_GlyphMetrics(m_font, ch, minx, maxx, miny, maxy, advance);
		}

		inline Size textSize(const String &text) const
		{
			int w;
			int h;
			TTF_SizeText(m_font, text.c_str(), &w, &h);
			return Size(w,h);
		}
		TTF_Font *getTTFFont() const { return m_font; }
		/*
		inline Sizei UTF8Size(const String &text) const
		{
			Sizei s;
			TTF_SizeUTF8(m_font, text.c_str(), &s.w, &s.h);
			return s;
		}
		inline Sizei unicodeSize(const String &text) const
		{
			Sizei s;
			TTF_SizeUNICODE(m_font, text.c_str(), &s.w, &s.h);
			return s;
		}
		*/
	};
	typedef std::shared_ptr<Font> FontShared;

	// ToDo: Must be singleton!
	class Fonts : std::unordered_map<std::string, FontShared>
	{
	public:
		Fonts()
		{
			if (TTF_Init() == -1)
				g_log.logErr("Cannot initialize fonts: " + String(TTF_GetError()));
		}
		~Fonts()
		{
			clear();
			TTF_Quit();
		}

		static String createFontID(const String &fname, int size);
		// Fonts are identified by filename and size.
		FontShared getFont(const String &fname, int size);
	};
	static Fonts g_Fonts;
}
