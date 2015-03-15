#include "fonts.h"

#include "common/string.h"
#include "common/logging.h"

using namespace Ris;

bool Font::load(const String &fname, int size)
{
	m_font = TTF_OpenFont(fname.c_str(), size);
	return isValid();
}

String Fonts::createFontID(const String &fname, int size)
{
	return fname + "#" + String(size);
}
FontShared Fonts::getFont(const String &fname, int size)
{
	String fontID = createFontID(fname, size);
	FontShared f = operator[](fontID);
	if (!f.get())
	{
		f = std::make_shared<Font>();
		if (!f->load(fname, size))
		{
			// Error, cannot be loaded :/
			g_log.logErr("Cannot load font file " + fname);
			erase(fontID);
		}
		else
			operator[](fontID) = f;
	}
	return f;
}
